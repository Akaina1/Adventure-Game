#pragma once
#include "CharacterTemplate.h"
#include "StatusEffect.h"

class Enemy : public CharacterTemplate
{
public:
	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
	Enemy(); // default constructor
	Enemy(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level,
		std::map<std::string, int> statValues,
		std::vector<StatusEffect> afflictions);  // constructor with parameters
	Enemy(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level);
	virtual ~Enemy(); // destructor
};

