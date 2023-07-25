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


