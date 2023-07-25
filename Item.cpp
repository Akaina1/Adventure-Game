#include "Item.h"


Item::Item()
{
}

Item::~Item()
{
}

Item::Item(std::string name, std::string description, int id, int price, int quantity, int type)
{
	this->name = name;
	this->description = description;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
	this->type = type;
}

void Item::Print(Item& item)
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Quantity: " << quantity << std::endl;
	std::cout << "Type: " << type << std::endl;
}

void Item::AddEffect(std::function<void(PlayerCharacter& player)> effect)
{
}

void Item::UseItem(PlayerCharacter* player, Item& item)
{
	// add item effect to player
	// decrease quantity by 1 if consumable
	// remove item from inventory if quantity is 0

	if (item.GetType() == 0)
	{
		//add item effect to player
		
		for (auto& effect : item.effects)
		{
			effect(*player);
		}
		std::cout << "Item effect added to player" << std::endl;
	}
}

void Item::EquipItem(PlayerCharacter& player, Item& item)
{

}

void Item::UnequipItem(PlayerCharacter& player, Item& item)
{

}

void Item::SellItem(PlayerCharacter& player, Item& item)
{

}

void Item::BuyItem(PlayerCharacter& player, Item& item)
{

}

