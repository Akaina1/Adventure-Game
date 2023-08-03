#pragma once
#include "Main.h"
#include "Item.h"

class DropTable
{
private:
	int minExp;
	int maxExp;
	int minGold;
	int maxGold;
	std::unordered_map<std::shared_ptr<Item>, std::pair<int, int>> itemRanges; // Map from item ID to a pair containing the item and a pair representing the min and max quantity
public:

	DropTable() {};
	~DropTable() {};

	DropTable(int minExp, int maxExp, int minGold, int maxGold, std::unordered_map<std::shared_ptr<Item>, std::pair<int, int>> itemranges)
		: minExp(minExp), maxExp(maxExp), minGold(minGold), maxGold(maxGold), itemRanges(itemranges)
	{}
	
	std::unordered_map<std::shared_ptr<Item>, std::pair<int, int>> GetItemRanges() { return itemRanges; };
	int GetMinExp() const { return minExp; };
	int GetMaxExp() const { return maxExp; };
	int GetMinGold() const { return minGold; };
	int GetMaxGold() const { return maxGold; };

};

