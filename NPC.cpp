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
	// Note: NPC and PlayerCharacter classes are considered "Allies", Enemy class is considered an "Enemy"
	// NPC AI will perform actions based on the following specifications:
	// 1. The AI will always prioritize UseSkill() over Attack() if the AI has (CurrentMana > (MaxMana * 0.2))
	// 2. The AI will always prioritize healing allies over attacking enemies if an ally is below 50% health
		// 2.b. The AI will always prioritize healing the ally with the lowest health if multiple allies are below 50% health
	// 3. The AI will always prioritize attacking enemies over healing allies if all allies are above 50% health
		//3.a. The AI will always prioritize attacking the enemy with the lowest health
		//3.b. The AI will always prioritize a (class)BossEnemy type enemy over an (class)Enemy type enemy
		//3.c. The AI will use Attack() if the AI has (CurrentMana < (MaxMana * 0.2))
	// 4. The AI will defend if the AI has (CurrentHealth < (MaxHealth * 0.2))
}

void NPC::Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	//AI chooses attack 
    


}


void NPC::Defend() 
{

}

void NPC::UseSkill(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{

}