// Implementation for the character template class that will be a base class for all other character classes
#include "CharacterTemplate.h"
#include "Effect.h"
#include "StatusEffect.h"
#include "AttackType.h"
#include "Combat.h"
////////////////////////////////// Default functions //////////////////////////////////

void CharacterTemplate::Print(std::ostream& os) const
{
	os << "Name: " << Name << std::endl;
	os << "Health: " << CurrentHealth << "/" << MaxHealth << std::endl;
	os << "Mana: " << CurrentMana << "/" << MaxMana << std::endl;
	os << "Level: " << Level << std::endl;
}

// default constructor
CharacterTemplate::CharacterTemplate() 
{

}

CharacterTemplate::CharacterTemplate(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level, AttackType baseAttackType)
	: Name{ name }, MaxHealth{ 100 }, CurrentHealth{ 100 }, CurrentMana{100}, MaxMana{ 100 }, Level{ 1 }, BaseAttackType{ baseAttackType }
{
}

// constructor with parameters

CharacterTemplate::CharacterTemplate(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level, int speed, int attackPwr, int defensePwr,
	bool isDefending ,std::map<std::string, int> statValues, AttackType baseAttackType,
	std::vector<Skill> skills, std::vector<EffectPtr> afflictions) :
	Name(name), MaxHealth(maxhealth), CurrentHealth(currenthealth),
	MaxMana(maxmana), CurrentMana(currentmana), Level(level), Speed(speed), AttackPwr(attackPwr), DefensePwr(defensePwr),
	IsDefending(isDefending), StatValues(statValues), BaseAttackType (baseAttackType), Skills (skills), Afflictions(afflictions) {}

// destructor

CharacterTemplate::~CharacterTemplate()
{
}

int CharacterTemplate::CalculateBaseDamage(AttackType baseAttackType, std::shared_ptr<CharacterTemplate> target)
{
	int damage = 0;

	// Calculate damage based on attack type
	switch (baseAttackType) {
	case AttackType::Melee:
		damage = (this->AttackPwr + (this->StatValues["Strength"])    ) - target->DefensePwr;
		break;
	case AttackType::Ranged:
		damage = (this->AttackPwr + this->StatValues["Dexterity"]) - target->DefensePwr;
		break;
	case AttackType::Magic:
		damage = (this->AttackPwr + this->StatValues["Wisdom"]) - target->DefensePwr;
		break;
	}

	// If the damage calculation is less than 0, we set it to 0
	if (damage < 0) {
		damage = 0;
	}

	return damage;
}

////////////////////////////////// Health functions   //////////////////////////////////

void CharacterTemplate::heal(int health) // heals the player character
{
	CurrentHealth += health;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void CharacterTemplate::TakeDamage(int damage) // damages the player character
{
	if (IsDefending)
	{
		// apply defense modifier
		damage = static_cast<int>(damage * 0.75); // assuming defense reduces damage by 25%
		IsDefending = false; // reset defense status
	}

	CurrentHealth -= damage;

	// handle case where player's health drops below 0
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}

bool CharacterTemplate::IsDead() // checks if the player character is dead
{
	return CurrentHealth <= 0;
}

////////////////////////////////// Mana functions     //////////////////////////////////

void CharacterTemplate::RestoreMana(int mana) // restores mana to the player character
{
	CurrentMana += mana;

	if (CurrentMana > MaxMana)
	{
		CurrentMana = MaxMana;
	}
}

void CharacterTemplate::UseMana(int cost) // uses mana from the player character
{
	CurrentMana -= cost;

	if (CurrentMana < 0)
	{
		CurrentMana = 0;
	}
}

////////////////////////////////// Effect functions   //////////////////////////////////

void CharacterTemplate::ApplyEffect(EffectPtr  effect) // applies a status effect to the player character
{
	effect->ApplyEffect(*this);
	std::cout << "EFFECT ADDED TO CHARACTER" << std::endl;
	Afflictions.push_back(effect);
};

void CharacterTemplate::RemoveEffect(const std::string& effectName)
{
	for (auto it = Afflictions.begin(); it != Afflictions.end();)
	{
		if ((*it)->GetName() == effectName)
		{
			// Call the RemoveEffect function to undo the effect
			(*it)->RemoveEffect(*this);

			// Erase the effect from the vector and get the next valid iterator
			it = Afflictions.erase(it);

			std::cout << "EFFECT REMOVED FROM CHARACTER" << std::endl;
			return;
		}
		else
		{
			++it;
		}
	}
}

////////////////////////////// Skill Effect functions //////////////////////////////////

bool CharacterTemplate::CanUseSkills() const
{
	for (const auto& effect : Afflictions)
	{
		if (effect->GetName() == "Silenced")
		{
			return false;
		}
	}

	return true;
}

////////////////////////////////// Stat functions    //////////////////////////////////

std::map<std::string, int> CharacterTemplate::GetCharacterStats() const
{
	return StatValues;
}

void CharacterTemplate::SetCharacterStats(std::map<std::string, int> newstats)
{
	StatValues = newstats;
}

void CharacterTemplate::AddStat(const std::string statName, int value)
{
	auto it = StatValues.find(statName);
	if (it != StatValues.end()) 
	{
		it->second += value;
	}
	else
	{
		std::cout << "Stat not found" << std::endl;
	}
}

void CharacterTemplate::RemoveStat(std::string statName, int value)
{
	auto it = StatValues.find(statName);
	if (it != StatValues.end())
	{
		it->second = (std::max)(it->second - value, 0);
	}
	else
	{
		std::cout << "Stat not found" << std::endl;
	}
}

void CharacterTemplate::Defend()
{
	if (auto combat_ptr = combat.lock())
	{
		// access CurrentTurn
		int currentTurn = combat_ptr->GetCurrentTurn();
		// increase defense by 25%
		DefensePwr *= 1.25;
		// indicate that character is defending
		IsDefending = true;

		// Defend until next turn
		DefendUntilTurn = currentTurn + 1;

		std::cout << GetName() << " braces for incoming attacks, increasing their defense!" << std::endl;
	}
}

void CharacterTemplate::ResetDefence()
{
	if (auto combat_ptr = combat.lock())
	{
		int currentTurn = combat_ptr->GetCurrentTurn();

		if (IsDefending && currentTurn >= DefendUntilTurn)
		{
			// reset defence to base value
			DefensePwr /= 1.25;
			IsDefending = false;
			std::cout << GetName() << " is no longer defending!" << std::endl;
		}
	}
}
