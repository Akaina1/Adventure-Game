#pragma once

#include "Main.h"
#include "Item.h"
#include "Enemy.h"
#include "NPC.h"

class GameManager
{
private:
	static GameManager* instance;
	std::unordered_map<int, std::shared_ptr<Item>> items;
	std::unordered_map<std::string, std::shared_ptr<Enemy>> enemies;
	std::unordered_map<std::string, std::shared_ptr<NPC>> npcs;

	std::unordered_map<int, std::shared_ptr<Item>> SetupItems(); // create all items in game
	std::unordered_map<std::string, std::shared_ptr<Enemy>> SetupEnemies();
	std::unordered_map<std::string, std::shared_ptr<NPC>> SetupNPCs();

	GameManager();

public:
	
	static GameManager* getInstance();
	std::shared_ptr<Item> GetItem (int id);
	std::shared_ptr<Enemy> GetEnemy(const std::string& name);
	std::shared_ptr<NPC> GetNPC(const std::string& name);
};

