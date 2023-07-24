// defintion for the character template class that will be a base class for all other character classes
#pragma once
#include "I_Print.h"

class CharacterTemplate : public I_Print {
private:
	std::string Name = "Unnamed";
	int Health = 100;
	int Mana = 100;
	int Level = 1;
	int Experience = 0;
public:
	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
	CharacterTemplate(); // default constructor
	CharacterTemplate(std::string name, int health, int level, int experience); // constructor with parameters
	virtual ~CharacterTemplate(); // destructor
};

