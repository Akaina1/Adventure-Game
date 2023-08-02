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
	std::unordered_map<int, std::pair<std::shared_ptr<Item>, std::pair<int, int>>> itemRanges; // Map from item ID to a pair containing the item and a pair representing the min and max quantity
public:
	DropTable();
	DropTable(int minExp, int maxExp, int minGold, int maxGold, const std::unordered_map<int, std::pair<std::shared_ptr<Item>, std::pair<int, int>>>& itemRanges);
	std::unordered_map<int, std::pair<std::shared_ptr<Item>, std::pair<int, int>>> GetItemRanges() const { return itemRanges; };
	int GetMinExp() const { return minExp; };
	int GetMaxExp() const { return maxExp; };
	int GetMinGold() const { return minGold; };
	int GetMaxGold() const { return maxGold; };

};

