// Implementation for the character template class that will be a base class for all other character classes
#include "CharacterTemplate.h"

// override the print function from the I_Print class

void CharacterTemplate::Print(std::ostream& os) const
{
	os << "Name: " << Name << std::endl;
	os << "Health: " << Health << std::endl;
	os << "Level: " << Level << std::endl;
	os << "Experience: " << Experience << std::endl;
}

// default constructor

CharacterTemplate::CharacterTemplate()
	: Name{ "Default" }, Health{ 100 }, Level{ 1 }, Experience{ 0 }
{
}

// constructor with parameters

CharacterTemplate::CharacterTemplate(std::string name, int health, int level, int experience)
	: Name{ name }, Health{ health }, Level{ level }, Experience{ experience }
{
}

// destructor

CharacterTemplate::~CharacterTemplate()
{
}
