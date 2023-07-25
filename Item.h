#pragma once
#include "Main.h"

class Item
{
private:
	std::string name;
	std::string description;
	int id; 
	int price;
	int quantity;
	int type;

public:

	Item(std::string name, std::string descrription, int id, int price, int quantity, int type);
	~Item();

	int getId() { return this->id; };
	int getPrice() { return this->price; };
	int getQuantity() {return this->quantity;};

	void setId(int id) { this->id = id; };
	void setPrice(int price) { this->price = price; };
	void setQuantity(int quantity) { this->quantity = quantity; };

	void printItem();
};

