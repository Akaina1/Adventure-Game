#pragma once

#include "CharacterTemplate.h"
#include "StatusEffect.h"

//class CharacterTemplate;

class NPC : public CharacterTemplate
{
	void Print(std::ostream& os) const override; // override the print function from the I_Print class
	NPC(); // default constructor
	NPC(std::string name, int maxhealth, int currenthealth, int maxmana,
		int currentmana, int level, int speed, int attack, int defense,
		bool isDefending, std::map<std::string, int> statValues, std::vector<StatusEffect> afflictions);  // constructor with parameters
	NPC(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level);
	virtual ~NPC(); // destructor
};

