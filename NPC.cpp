#include "NPC.h"
#include "AttackType.h"
#include "Effect.h"
#include "Enemy.h"

void NPC::Print(std::ostream& os) const     // override the print function from the I_Print class
{
	std::cout << std::boolalpha;
	os << "Enemy: " << std::endl;
	//os << "Location: "<< CurrentLocation << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Name: " << Name << std::endl;
	os << "Level: " << Level << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Health: " << CurrentHealth << "/" << MaxHealth << std::endl;
	os << "Mana: " << CurrentMana << "/" << MaxMana << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Stats: " << std::endl;
	for (auto stat : StatValues)
	{
		os << stat.first << ": " << stat.second << std::endl;
	}
	os << "-------------------------------------------" << std::endl;
	os << "Status Effects: " << std::endl;
	for (auto& effect : Afflictions)
	{
		os << effect->GetName() << ": " << effect->GetDuration() << " turns left" << std::endl;
	}
}

NPC::NPC() // default constructor
{
}

NPC::NPC(std::string name, int maxhealth, int currenthealth, int maxmana,
	int currentmana, int level, int speed, int attackPwr, int defensePwr,
	bool isDefending, std::map<std::string, int> statValues, AttackType baseAttackType,
	std::vector<Skill> skills, std::vector<EffectPtr> afflictions)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, speed, attackPwr, defensePwr,
		isDefending, statValues, baseAttackType, skills , afflictions)
{
}

NPC::~NPC() // destructor
{
}

NPC::NPC(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level)
{
}

void NPC::PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	int choice = 0;

	switch (choice)
	{
	case 1:
		Attack(Combatants);
		break;
	case 2:
		Defend();
		break;
	}
}

void NPC::Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	// Determine the target to attack based on the NPC's AI logic.
		// For example, you can choose a random target like before or implement more sophisticated decision-making.

	if (!Combatants.empty())
	{
		// Randomly choose an enemy to attack (similar to previous implementation).
		int targetIndex = std::rand() % Combatants.size();
		auto target = Combatants[targetIndex];

		// Check if the target is an enemy and not already defeated.
		auto enemyTarget = std::dynamic_pointer_cast<Enemy>(target);
		if (enemyTarget != nullptr && enemyTarget->GetCurrentHealth() > 0)
		{
			// Determine the attack type based on the NPC's abilities or preferences.
			// For now, let's assume the NPC always uses a melee attack (AttackType::Melee).
			AttackType attackType = AttackType::Melee;

			int damage = CalculateBaseDamage(attackType, enemyTarget);
			enemyTarget->TakeDamage(damage);

			std::cout << GetName() << " attacks " << enemyTarget->GetName() << " for " << damage << " damage!" << std::endl;
		}
		else
		{
			// The randomly chosen target is not a valid enemy, so reattempt the attack.
			Attack(Combatants);
		}
	}
}
void NPC::Defend() 
{

}