// definition for the PlayerCharacter class
#pragma once
#include "Main.h"
#include "MainMenu.h"
#include "Location.h"
#include "Room.h"
#include "NPC.h"
#include "Event.h"
#include "StatusEffect.h"
#include "Tavern.h"
#include "CharacterTemplate.h"

class Item;

class PlayerCharacter : public CharacterTemplate {
private:
	long long Experience = 0;
	int Gold = 0;
	int PlayerClass = 0;                     // 0 = Brawler, 1 = Scourge, 2 = Swindler, 3 = Jester
	
	std::unordered_map<int, std::pair<std::shared_ptr<Item>, int>> Inventory;           //using a map to hold the inventory of Item objects as well as their quantity and id
	std::shared_ptr<Location> CurrentLocation;                // pointer to the current location of the character
	std::weak_ptr<PlayerCharacter> Self;                       // pointer to itself

public:
//default functions
	PlayerCharacter();          // default constructor
	~PlayerCharacter(); // destructor

	PlayerCharacter(std::string name, int maxhealth, int currenthealth,
		int maxmana, int currentmana, int level, int speed, int attack, int defense,
		bool isDefending, long long experience,
		int gold, int playerClass, std::map<std::string, int> statValues,
		std::unordered_map<int, std::pair<std::shared_ptr<Item>, int>> inventory,
		std::vector<StatusEffect> afflictions);  // constructor with parameters

	virtual void Print(std::ostream& os) const;                                    // override the print function from the I_Print class

//location functions
	std::shared_ptr<Location> GetCurrentLocation() const {return CurrentLocation;}                                            // returns the current location of the player character
	void SetCurrentLocation(std::shared_ptr<Location> location) { CurrentLocation = location; }    // sets the current location of the player character
	void MoveTo(std::shared_ptr<Location> newlocation);                                                                           // move the player character to a new location)

	void ChooseMove();
//combat functions
	virtual void PerformAction(std::vector<std::shared_ptr<CharacterTemplate>>& Combatants) override; // override the PerformAction function from the CharacterTemplate class
	void Attack(std::vector<std::shared_ptr<CharacterTemplate>>& Combatants); // attack a target
	void Defend(); // defend against an attack
	void CheckInventory(); // check the player character's inventory to use items

//class functions
	std::string GetPlayerClassName() const;                    // returns the name of the player class
	int GetPlayerClass() const { return PlayerClass; };        // returns the player class of the player character
	void SetPlayerClass(int Class) {PlayerClass = Class;};     // sets the player class of the player character

//gold functions
	void AddGold(int gold) { Gold += gold;};       // adds gold to the player character
	void RemoveGold(int gold) { Gold -= gold; };   // removes gold from the player character
	int GetPlayerGold() const { return Gold; };    // returns player gold value


//Experience functions
	void AddExperience(long long exp);                            // adds experience to the player character
	void RemoveExperience(long long exp) { Experience -= exp; };  // removes experience from the player character
	long long GetExperience() const { return Experience; }        // returns the experience of the player character
	void LevelUp();                                         // levels up the player character
	long long ExpToNextLevel() const;								// returns the amount of experience needed to level up

//other functions
	void CharacterCreator();     //character creator
	void SetSelf(std::shared_ptr<PlayerCharacter> selfShared) { Self = selfShared; };  // sets the self pointer to itself)

//inventory functions
	void AddItem(std::shared_ptr<Item> item, int quantity);      // adds an item to the player character's inventory
	void RemoveItem(std::shared_ptr<Item> item, int quantity);   // removes an item from the player character's inventory
	int GetItemQuantity(std::shared_ptr<Item> item);             // returns the quantity of an item in the player character's inventory
	void PrintInventory();                       // prints the inventory of the player character
	void UseItem(int itemId);                    // uses an item from the player character's inventory
};

