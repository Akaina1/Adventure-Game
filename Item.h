#pragma once
#include "Main.h"
#include "I_Print.h"
#include "PlayerCharacter.h"

class PlayerCharacter;
enum class ItemType
	{
		CONSUMABLE,
		WEAPON,
		ARMOR,
		EVENT_ITEM,
		JUNK_ITEM
	};

class Item
{
private:
	std::string name;
	std::string description;
	int id; 
	int price;
	//int type; // 0 - consumable, 1 - weapon, 2 - armor, 3 - event item 4 - junk item (sellable for gold)
	std::function<void(PlayerCharacter& player)> effect; // effect of the item (for consumables)
	ItemType itemType;

public:
	

	Item();	
	Item(std::string name, std::string descrription, int id, int price, ItemType type, std::function<void(PlayerCharacter& player)> effect); // for items with effects
	Item(std::string name, std::string descrription, int id, int price, ItemType type); // for items with no effects
	Item(std::string name, std::string descrription, int id, ItemType type); // for event items 
	~Item();

//getters
	std::string GetName() const { return name; };
	std::string GetDescription() const { return description; };
	int GetId() { return id; };
	int GetPrice() { return price; };
	ItemType GetType() { return itemType; };
	std::function<void(PlayerCharacter& player)> GetEffect() { return effect; };

//setters
	void SetName(std::string name) { name = name; };
	void SetDescription(std::string description) { description = description; };
	void SetId(int id) { id = id; };
	void SetPrice(int price) { price = price; };
	void SetType(int type) { type = type; };
	void SetEffect(std::function<void(PlayerCharacter& player)> effect) { effect = effect; };

	
//other functions
	void EquipItem();
	void UnequipItem();
	void SellItem();
	void BuyItem();

	void Print(Item& item);

//overloads

	bool operator==(const Item& other) const
	{
		return this->id == other.id;
	}

	bool operator<(const Item& other) const
	{
		return this->id < other.id;
	}
};

// example "ale" item for tavern
//Item ale("Ale", "A pint of ale", 001, 5, 1, 0); // item name = Ale, item description = A pint of ale, item id = 001, item price = 5 gold, item quantity = 1, item type = 0

// example health potion that increases player health attribute by 10

