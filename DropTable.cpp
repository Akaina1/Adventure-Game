#include "DropTable.h"

DropTable::DropTable(int minExp, int maxExp, int minGold, int maxGold, const std::unordered_map<int, std::pair<std::shared_ptr<Item>, std::pair<int, int>>>& itemRanges)
: minExp(minExp), maxExp(maxExp), minGold(minGold), maxGold(maxGold), itemRanges(itemRanges) 
{}

