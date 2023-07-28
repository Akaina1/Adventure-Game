// Implementation for the character template class that will be a base class for all other character classes
#include "CharacterTemplate.h"

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
	: Name{ "Default" }, MaxHealth{ 100 }, MaxMana{ 100 }, Level{1}
{
}

// constructor with parameters

CharacterTemplate::CharacterTemplate(std::string name, int maxHealth, int currentHealth, int maxMana, int currentMana, int level, std::map<std::string, int> stats, std::vector<StatusEffect> Afflictions)
	: Name{ name }, MaxHealth{ maxHealth }, CurrentHealth{ currentHealth }, MaxMana{ maxMana }, CurrentMana { currentMana }, Level{ level }
{
}

// destructor

CharacterTemplate::~CharacterTemplate()
{
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
	CurrentHealth -= damage;

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

void CharacterTemplate::ApplyEffect(StatusEffect effect) // applies a status effect to the player character
{

	effect.state = StatusEffect::State::Active;

	effect.StatusEffect::GetAddEffect()(*this);

	std::cout << "EFFECT ADDED TO CHARACTER" << std::endl;

	Afflictions.push_back(effect);

};

void CharacterTemplate::RemoveEffect(const std::string& effectName) // removes a status effect from the player character
{
	for (auto it = Afflictions.begin(); it != Afflictions.end(); ++it)
	{
		// If the effect is the one we want to remove
		if (it->GetName() == effectName)
		{
			// Call the removeEffect function to undo the effect
			it->GetRemoveEffect()(*this);

			// Remove the effect from the vector
			Afflictions.erase(it);

			std::cout << "EFFECT REMOVED FROM CHARACTER" << std::endl;
			return;
		}
	}
}

void CharacterTemplate::UpdateEffects(StatusEffect& effect) // takes in an effect to update, and a pointer to a character to access their Afflictions vector
{
	// check if the effect is in the vector
	for (auto& affliction : Afflictions)
	{
		if (affliction.GetId() == effect.GetId())
		{
			// if the effect is in the vector check if the effect is active or not
			if (affliction.state == StatusEffect::State::Active)
			{
				RemoveEffect(affliction.GetName());
			}
			else if (affliction.state == StatusEffect::State::Inactive)
			{
				ApplyEffect(affliction);
			}
			else if (affliction.state == StatusEffect::State::Blocked)
			{
				std::cout << "CAN'T UPDATE BLOCKED EFFECT" << std::endl;
			}
			return;

		}
		

	}

	if (effect.state == StatusEffect::State::Active)
	{
			ApplyEffect(effect);
	}
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

