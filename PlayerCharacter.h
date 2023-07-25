// definition for the PlayerCharacter class
#pragma once
#include "CharacterTemplate.h"
#include "Location.h"

class PlayerCharacter : public CharacterTemplate {
private:
	std::string Name = "Unnammed";
	int Health = 100;
	int Mana = 100;
	int Level = 1;
	int Experience = 0;
	int Gold = 0;
	int PlayerClass = 0; // 0 = Brawler, 1 = Scourge, 2 = Swindler, 3 = Jester
	std::map<std::string, int> StatValues { // using a map to hold the stats of the character
		{"Strength", 0},
		{ "Dexterity", 0 },
		{ "Wisdom", 0 },
		{ "Charisma", 0 }
	};
	std::map<std::string, int> Inventory;  //using a map to hold the inventory of Item objects as well as their quantity
	std::map<std::string, bool> StatusEffect; // using a map to hold the status effects of the character and whether they are active or not
	Location* CurrentLocation; // pointer to the current location of the character
public:
	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
	PlayerCharacter(); // default constructor
	PlayerCharacter(std::string name, int health,int mana, int level, int experience, int gold, int PlayerClass, std::map<std::string, int> statValues, std::map<std::string, int> inventory, std::map<std::string, bool> statusEffect); // constructor with parameters
	virtual ~PlayerCharacter(); // destructor
	std::string GetPlayerClassName(int PlayerClass) const;// returns the name of the player class
	void ShowInventory() const; // prints the inventory of the player character
	PlayerCharacter PlayerCreator(); // create a new custom player character
	void MoveTo(Location& CurrentLocation, Location& NewLocation); // move the player character to a new location)
	Location& GetCurrentLocation(Location& CurrentLocation) const; // returns the current location of the player character
};

