#include "Item.h"
#include "PlayerCharacter.h"


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