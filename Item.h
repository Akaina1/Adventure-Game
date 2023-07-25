#pragma once
#include "Main.h"
#include "I_Print.h"
#include "PlayerCharacter.h"

class Item
{
private:
	std::string name;
	std::string description;
	int id; 
	int price;
	int quantity;
	int type; // 0 - consumable, 1 - weapon, 2 - armor, 3 - event item 4 - junk item (sellable for gold)
	std::vector<std::function<void(PlayerCharacter& player)>> effects; // vector of effects for consumables
	

public:

	Item();	
	Item(std::string name, std::string descrription, int id, int price, int quantity, int type);
	~Item();

	int GetId() { return this->id; };
	int GetPrice() { return this->price; };
	int GetQuantity() {return this->quantity;};
	int GetType() { return this->type; };

	void SetId(int id) { this->id = id; };
	void SetPrice(int price) { this->price = price; };
	void SetQuantity(int quantity) { this->quantity = quantity; };
	void SetType(int type) { this->type = type; };

	void AddEffect(std::function<void(PlayerCharacter& player)> effect); // add effect to item (for consumables))

	void UseItem(PlayerCharacter* player, Item &item);
	void EquipItem(PlayerCharacter& player, Item& item);
	void UnequipItem(PlayerCharacter& player, Item& item);
	void SellItem(PlayerCharacter& player, Item& item);
	void BuyItem(PlayerCharacter& player, Item& item);

	void Print(Item& item);
};

// example "ale" item for tavern
//Item ale("Ale", "A pint of ale", 001, 5, 1, 0); // item name = Ale, item description = A pint of ale, item id = 001, item price = 5 gold, item quantity = 1, item type = 0

// example health potion that increases player health attribute by 10

