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

void Item::Print(std::ostream& os) const
{
	os << "Name: " << name << std::endl;
	os << "Description: " << description << std::endl;
	os << "ID: " << id << std::endl;
	os << "Price: " << price << std::endl;
	os << "Quantity: " << quantity << std::endl;
	os << "Type: " << type << std::endl;
}
