#include "Enemy.h"

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
		if (effect.state == StatusEffect::State::Active)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;

		}
		else if (effect.state == StatusEffect::State::Inactive)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;

		}
		else if (effect.state == StatusEffect::State::Blocked)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;

		}
	}
}

Enemy::Enemy() // default constructor
{
}

Enemy::Enemy(std::string name, int maxhealth, int currenthealth, int maxmana,
	int currentmana, int level,std::map<std::string, int> statValues,std::vector<StatusEffect> afflictions)
	: CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, statValues, afflictions)
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