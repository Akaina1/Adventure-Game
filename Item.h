#pragma once
#include "Main.h"
#include "I_Print.h"
#include "PlayerCharacter.h"

class PlayerCharacter;

class Item
{
private:
	std::string name;
	std::string description;
	int id; 
	int price;
	int quantity;
	int type; // 0 - consumable, 1 - weapon, 2 - armor, 3 - event item 4 - junk item (sellable for gold)
	std::function<void(PlayerCharacter& player)> effect; // effect of the item (for consumables)
	

public:

	Item();	
	Item(std::string name, std::string descrription, int id, int price, int quantity, int type, std::function<void(PlayerCharacter& player)> effect);
	~Item();

//getters
	std::string GetName() const { return this->name; };
	std::string GetDescription() const { return this->description; };
	int GetId() { return this->id; };
	int GetPrice() { return this->price; };
	int GetQuantity() {return this->quantity;};
	int GetType() { return this->type; };
	std::function<void(PlayerCharacter& player)> GetEffect() { return this->effect; };

//setters
	void SetName(std::string name) { this->name = name; };
	void SetDescription(std::string description) { this->description = description; };
	void SetId(int id) { this->id = id; };
	void SetPrice(int price) { this->price = price; };
	void SetQuantity(int quantity) { this->quantity = quantity; };
	void SetType(int type) { this->type = type; };
	void SetEffect(std::function<void(PlayerCharacter& player)> effect) { this->effect = effect; };

	
//other functions
	void EquipItem(PlayerCharacter& player);
	void UnequipItem(PlayerCharacter& player);
	void SellItem(PlayerCharacter& player);
	void BuyItem(PlayerCharacter& player);

	void Print(Item& item);

//overloads

	bool operator==(const Item& other) const
	{
		return this->name == other.name;
	}

	bool operator<(const Item& other) const
	{
		return this->name < other.name;
	}
};

// example "ale" item for tavern
//Item ale("Ale", "A pint of ale", 001, 5, 1, 0); // item name = Ale, item description = A pint of ale, item id = 001, item price = 5 gold, item quantity = 1, item type = 0

// example health potion that increases player health attribute by 10

