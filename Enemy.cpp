#include "Enemy.h"
#include "AttackType.h"

void Enemy::Print(std::ostream& os) const     // override the print function from the I_Print class
{
	std::cout << std::boolalpha;
	os << "Enemy: " << std::endl;
	//os << "Location: "<< CurrentLocation << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Name: " <<  Name << std::endl;
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

Enemy::Enemy() // default constructor
{
}

Enemy::Enemy(std::string name, int maxhealth, int currenthealth, int maxmana,
	int currentmana, int level, int speed, int attackPwr, int defensePwr,
	bool isDefending,std::map<std::string, int> statValues, AttackType baseAttackType,
	std::vector<Skill> skills, std::vector<EffectPtr> afflictions)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, speed, attackPwr, defensePwr,
      isDefending, statValues, baseAttackType, skills, afflictions)
{
}

Enemy::~Enemy() // destructor
{
}

Enemy::Enemy(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level)
{
}

void Enemy::PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{

}
void Enemy::Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{

}
void Enemy::Defend()
{

}