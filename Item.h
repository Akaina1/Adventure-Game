#pragma once
#include "Main.h"

class Item : public I_Print 
{
private:
	std::string name;
	std::string description;
	int id; 
	int price;
	int quantity;
	int type; // 0 - consumable, 1 - weapon, 2 - armor, 3 - event item 4 - junk item (sellable for gold)

public:

	Item(std::string name, std::string descrription, int id, int price, int quantity, int type);
	~Item();

	int GetId() { return this->id; };
	int GetPrice() { return this->price; };
	int GetQuantity() {return this->quantity;};

	void SetId(int id) { this->id = id; };
	void SetPrice(int price) { this->price = price; };
	void SetQuantity(int quantity) { this->quantity = quantity; };

	virtual void Print(std::ostream& os) const override;
};

// example "ale" item for tavern
Item ale("Ale", "A pint of ale", 001, 5, 1, 1); // item name = Ale, item description = A pint of ale, item id = 001, item price = 5 gold, item quantity = 1, item type = 1