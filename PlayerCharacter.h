// definition for the PlayerCharacter class
#pragma once
#include "CharacterTemplate.h"
#include "Location.h"
#include "Main.h"
#include "Item.h"
#include "MainMenu.h"
#include "Location.h"
#include "Room.h"
#include "NPC.h"
#include "Event.h"
#include "StatusEffect.h"
//#include "Tavern.h"

class Item;
class StatusEffect;

class PlayerCharacter : public CharacterTemplate {
private:
	std::string Name = "Unnammed";
	int MaxHealth = 100;
	int CurrentHealth = MaxHealth;
	int MaxMana = 100;
	int CurrentMana = MaxMana;
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

	std::map<Item, int> Inventory;  //using a map to hold the inventory of Item objects as well as their quantity

	std::vector<StatusEffect> Afflictions; // using a map to hold the status effects of the character and whether they are active or not
	Location* CurrentLocation; // pointer to the current location of the character


public:
	PlayerCharacter(); // default constructor
	virtual ~PlayerCharacter(); // destructor
	PlayerCharacter(std::string name, int maxhealth,int currenthealth, int maxmana, int currentmana, int level, int experience, int gold, int PlayerClass, std::map<std::string, int> statValues, std::map<Item, int> inventory, std::vector<StatusEffect> afflictions); // constructor with parameters

	virtual void Print(std::ostream& os) const override; // override the print function from the I_Print class
//getters
	std::string GetPlayerClassName() const;// returns the name of the player class
	Location& GetCurrentLocation(Location& CurrentLocation) const; // returns the current location of the player character
	int GetPlayerGold(PlayerCharacter& Player) const; // returns player gold value

//setters
	void AddGold(PlayerCharacter& Player, int Gold); // adds gold to the player character
	//void SetExperience(PlayerCharacter& Player, int Experience); // adds experience to the player character
	void RemoveGold(PlayerCharacter& Player, int Gold); // removes gold from the player character

//other functions
	void MoveTo(Location& CurrentLocation, Location& NewLocation); // move the player character to a new location)

	PlayerCharacter PlayerCreator(); // create a new custom player character

//inventory functions
	void AddItem(Item &item, int quantity, PlayerCharacter* player); // adds an item to the player character's inventory
	void RemoveItem(Item &item, int quantity, PlayerCharacter* player); // removes an item from the player character's inventory
	int GetItemQuantity(Item &item, PlayerCharacter& player); // returns the quantity of an item in the player character's inventory
	void PrintInventory(); // prints the inventory of the player character

// health functions
	int GetCurrentHealth(PlayerCharacter& player) const { return CurrentHealth; }; // returns the current health of the player character
	int GetMaxHealth(PlayerCharacter& player) const { return MaxHealth; }; // returns the max health of the player character
	void IncreaseMaxHealth(int health, PlayerCharacter* player);// increase the max health of the player character
	void DecreaseMaxHealth(int health, PlayerCharacter* player);// decrease the max health of the player character
	void heal(int health, PlayerCharacter* player ); // heals the player character
	void TakeDamage(int damage, PlayerCharacter* player); // damages the player character
	bool IsDead(PlayerCharacter& player); // checks if the player character is dead

// mana functions
	int GetCurrentMana(PlayerCharacter& player) const { return CurrentMana; }; // returns the current mana of the player character
	int GetMaxMana(PlayerCharacter& player) const { return MaxMana; }; // returns the max mana of the player character
	void SetMaxMana(int mana, PlayerCharacter* player); // sets the max mana of the player character
	void RestoreMana(int mana, PlayerCharacter* player); // restores mana to the player character
	void UseMana(int mana, PlayerCharacter* player); // uses mana from the player character

// testing effect function rework 
	void ApplyEffect(StatusEffect& effect, PlayerCharacter* player); // applies a status effect to the player character
	void UpdateEffects(StatusEffect& effect,PlayerCharacter* player); // updates the status effects of the player character

};

