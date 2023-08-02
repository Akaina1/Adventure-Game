#pragma once
#include "Main.h"
#include "Item.h"
#include "SetupItems.h"



class GameManager
{
private:
	std::unordered_map<int, std::shared_ptr<Item>> items;
	std::unordered_map<int, std::shared_ptr<Enemy>> enemies;
	std::unordered_map<int, std::shared_ptr<NPC>> npcs;
public:
	GameManager() 
	{ 
		items = SetupItems(); 
		enemies = SetupEnemies();
		npcs = SetupNPCs();
	};

	std::shared_ptr<Item> GetItem (int id);
	std::shared_ptr<Enemy> GetEnemy(std::string name);
	std::shared_ptr<NPC> GetNPC(std::string name);

};

