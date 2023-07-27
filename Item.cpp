#include "Item.h"


Item::Item() // default constructor
{
}

Item::~Item() // destructor
{
}

Item::Item(std::string name, std::string description, int id, int price, int quantity, int type, std::function<void(PlayerCharacter& player)> effect) // constructor with parameters
{
	this->name = name;
	this->description = description;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
	this->type = type;
	this->effect = effect;
}

void Item::Print(Item& item) // print item info
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Quantity: " << quantity << std::endl;
	std::cout << "Type: " << type << std::endl;
}

void Item::EquipItem(PlayerCharacter& player)
{

}

void Item::UnequipItem(PlayerCharacter& player)
{

}

void Item::SellItem(PlayerCharacter& player)
{

}

void Item::BuyItem(PlayerCharacter& player)
{

}

