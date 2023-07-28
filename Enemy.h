#pragma once
#include "CharacterTemplate.h"
class Enemy : public CharacterTemplate
{
private:
	std::string Name = "Unnamed";
	int Health = 100;
	int Mana = 100;
	int Level = 1;
	int Experience = 0;
public:
	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
	Enemy(); // default constructor
	Enemy(std::string name, int health, int level, int experience) : Name{ name }, ; // constructor with parameters
	virtual ~Enemy(); // destructor
};

