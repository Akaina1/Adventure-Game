#include "Item.h"


Item::Item() // default constructor
{
}

Item::~Item() // destructor
{
}

Item::Item(std::string name, std::string description, int id, int price, ItemType type, std::function<void(std::shared_ptr<PlayerCharacter>)> effect)
	: name (name), description (description), id (id), price (price), itemType (type), effect (effect) {}// items with effects

Item::Item(std::string name, std::string descrription, int id, ItemType type) 
	: name (name), description(description), id(id), itemType (type) {} //event items

Item::Item(std::string name, std::string descrription, int id, int price, ItemType type) 
	: name(name), description(description), id(id), price(price), itemType(type) {}// items without effects

void Item::Print(Item& item) // print item info
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Price: " << price << std::endl;
}

void Item::EquipItem()
{

}

void Item::UnequipItem()
{

}

void Item::SellItem()
{

}

void Item::BuyItem()
{

}

