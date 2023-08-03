#include "GameManager.h"
#include "Location.h"
#include "Room.h"
#include "Tavern.h"
#include "Dungeon.h"
#include "PlayerCharacter.h"
#include "SetupEvents.h"
#include "DropTable.h"

GameManager* GameManager::instance = nullptr;

std::shared_ptr<Item> GameManager::GetItem(int id)
{
	if (items.count(id) > 0)
	{
		return items[id];
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<Enemy> GameManager::GetEnemy(const std::string& name)
{
	if (enemies.count(name) > 0)
	{
		// Fetch the enemy from your storage into `originalEnemy`
		std::shared_ptr<Enemy> originalEnemy = enemies[name];
		// Create a new copy of the enemy
		return std::make_shared<Enemy>(*originalEnemy);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<NPC> GameManager::GetNPC(const std::string& name)
{
	if (npcs.count(name) > 0)
	{
		return npcs[name];
	}
	else
	{
		return nullptr;
	}
}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

GameManager::GameManager()
{
	items = SetupItems();

	enemies = SetupEnemies();

	npcs = SetupNPCs();
};

std::unordered_map<int, std::shared_ptr<Item>> GameManager::SetupItems()// create all items in game
{
	std::unordered_map<int, std::shared_ptr<Item>> items;

	std::shared_ptr<Item> miniHealingPotion = std::make_shared<Item> // create mini healing potion
		(
			"Mini Healing Potion",       // name
			"Restores 20 HP",            // description
			0001,                        // id
			50,							 // price in gold
			ItemType::CONSUMABLE,		 // type
			[](std::shared_ptr<PlayerCharacter> player)  // effect
			{
				player->heal(20);
			}
	);

	std::shared_ptr<Item> healingPotion = std::make_shared<Item> // create healing potion
		(
			"Healing Potion",            // name
			"Restores 50 HP",            // description
			0002,                        // id
			80,							 // price in gold
			ItemType::CONSUMABLE,		 // type
			[](std::shared_ptr<PlayerCharacter> player)  // effect
			{
				player->heal(50);
			}
	);

	std::shared_ptr<Item> mediumHealingPotion = std::make_shared<Item> // create super healing potion
		(
			"Medium Healing Potion",     // name
			"Restores 80 HP",            // description
			0003,                        // id
			100,					     // price in gold
			ItemType::CONSUMABLE,		 // type
			[](std::shared_ptr<PlayerCharacter> player)  // effect
			{
				player->heal(80);
			}
	);

	std::shared_ptr<Item> largeHealingPotion = std::make_shared<Item> // create super healing potion
		(
			"Large Healing Potion",      // name
			"Restores 120 HP",           // description
			0004,                        // id
			150,						 // price in gold
			ItemType::CONSUMABLE,		 // type
			[](std::shared_ptr<PlayerCharacter> player)  // effect
			{
				player->heal(120);
			}
	);

	// add items to map
	items[miniHealingPotion->GetId()] = miniHealingPotion;
	items[healingPotion->GetId()] = healingPotion;
	items[mediumHealingPotion->GetId()] = mediumHealingPotion;
	items[largeHealingPotion->GetId()] = largeHealingPotion;

	return items; //return the map
}

std::unordered_map<std::string, std::shared_ptr<Enemy>> GameManager::SetupEnemies()
{
	std::unordered_map<std::string, std::shared_ptr<Enemy>> enemies;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		std::unordered_map<std::shared_ptr<Item>, std::pair<int, int>> itemRanges;

		std::shared_ptr<Item> gob_drop_1 = GetItem(0001); // get item from item manager (id 0001)
		itemRanges[gob_drop_1] = { 1, 3 }; // add item to droptable with a minimum of 1 and a maximum of 3

		std::shared_ptr<Item> gob_drop_2 = GetItem(0002);
		itemRanges[gob_drop_2] = { 1, 2 };

		auto dropTablePtr = std::make_shared<DropTable>(50, 100, 20, 50, itemRanges);
		// droptable with 50 minimum exp, 100 maximum exp, 20 minimum gold, 50 maximum gold, and the itemRanges

		std::vector<Skill> emptySkills;
		std::vector<EffectPtr> emptyAfflictions;
		std::map<std::string, int> statValues = { {"Strength", 5}, {"Dexterity", 5}, {"Wisdom", 5}, {"Charisma", 5} };

		std::shared_ptr<Enemy> goblin1 = std::make_shared<Enemy>// create goblin enemy
			(
				"Goblin 1",                // name
				50,                      // maxhealth
				50,                      // currenthealth
				20,                      // maxmana
				20,                      // currentmana
				1,                       // level
				1,                       // speed
				1,                       // attackPwr
				1,                       // defensePwr
				false,                   // isDefending
				statValues,              // statValues
				AttackType::Melee,       // baseAttackType
				emptySkills,             // skills
				emptyAfflictions,        // afflictions
				dropTablePtr             // dropTable
			);

		enemies[goblin1->GetName()] = goblin1; // add to enemies map
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		std::unordered_map<std::shared_ptr<Item>, std::pair<int, int>> itemRanges;

		std::shared_ptr<Item> hydra_drop_1 = GetItem(0003); // get item from item manager (id 0001)
		itemRanges[hydra_drop_1] = { 1, 3 }; // add item to droptable with a minimum of 1 and a maximum of 3

		std::shared_ptr<Item> hydra_drop_2 = GetItem(0004);
		itemRanges[hydra_drop_2] = { 1, 2 };

		auto dropTablePtr = std::make_shared<DropTable>(50, 100, 20, 50, itemRanges);
		// droptable with 50 minimum exp, 100 maximum exp, 20 minimum gold, 50 maximum gold, and the itemRanges

		std::vector<Skill> emptySkills;				// add skills
		std::vector<EffectPtr> emptyAfflictions;	// add afflictions
		std::map<std::string, int> statValues = { {"Strength", 6}, {"Dexterity", 6}, {"Wisdom", 7}, {"Charisma", 3} }; // add stats

		std::shared_ptr<Enemy> hydra2 = std::make_shared<Enemy>// create goblin enemy
			(
				"Hydra 2",                // name
				80,                      // maxhealth
				80,                      // currenthealth
				50,                      // maxmana
				60,                      // currentmana
				2,                       // level
				2,                       // speed
				2,                       // attackPwr
				2,                       // defensePwr
				false,                   // isDefending
				statValues,              // statValues
				AttackType::Melee,       // baseAttackType
				emptySkills,             // skills
				emptyAfflictions,        // afflictions
				dropTablePtr             // dropTable
			);

		enemies[hydra2->GetName()] = hydra2; // add to enemies map
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	return enemies;
}

std::unordered_map<std::string, std::shared_ptr<NPC>> GameManager::SetupNPCs()
{
	std::unordered_map<std::string, std::shared_ptr<NPC>> npcs;

	// Here you would create your NPC objects and add them to the 'npcs' map.

	return npcs;
}

void GameManager::SetupGame(std::shared_ptr<PlayerCharacter> player)
{
	// Create Tavern
	auto theTavern = std::make_shared<Tavern>("The Tavern", "A Place to Rest, Relax, Drink and forget about the monsters below us...", player);

	// Create NPCs for Tavern Rooms
	std::shared_ptr<NPC> npc1 = GetNPC("NPC 1");
	std::shared_ptr<NPC> npc2 = GetNPC("NPC 2");

	// Create NPC Groups for Tavern Rooms
	std::deque<std::shared_ptr<CharacterTemplate>> NPCGroup1;
	NPCGroup1.push_back(npc1);
	NPCGroup1.push_back(npc2);

	//create enemies for Dungeon
	std::shared_ptr<Enemy> goblin1 = GetEnemy("Goblin 1");
	std::shared_ptr<Enemy> goblin2 = GetEnemy("Goblin 1");
	std::shared_ptr<Enemy> hydra2 = GetEnemy("Hydra 2");
	std::shared_ptr<Enemy> hydra3 = GetEnemy("Hydra 2");


	// Create Enemy Groups for Dungeon Rooms
	std::deque<std::shared_ptr<CharacterTemplate>> enemyGroup1;
	enemyGroup1.push_back(hydra2);
	enemyGroup1.push_back(goblin2);

	std::deque<std::shared_ptr<CharacterTemplate>> enemyGroup2;
	enemyGroup2.push_back(hydra3);
	enemyGroup2.push_back(goblin1);

	// Create Rooms for Tavern
	auto tavernRoom1 = std::make_shared<Room>("Tavern Room 1", "A cozy little room with a roaring fireplace.");
	auto tavernRoom2 = std::make_shared<Room>("Tavern Room 2", "A room filled with raucous laughter and song.");
	theTavern->ConnectRoom(tavernRoom1);
	theTavern->ConnectRoom(tavernRoom2);
	tavernRoom1->ConnectRoom(tavernRoom2);
	tavernRoom2->ConnectRoom(tavernRoom1);
	tavernRoom1->ConnectLocation(theTavern);
	tavernRoom2->ConnectLocation(theTavern);

	// Create Dungeon
	auto theDungeon = std::make_shared<Dungeon>("The Dungeon", "A dark, dreary dungeon teeming with dangerous creatures.", player);
	theTavern->ConnectLocation(theDungeon);
	theDungeon->ConnectLocation(theTavern);


	// Create Rooms for Dungeon
	auto dungeonRoom1 = std::make_shared<Room>("Dungeon Room 1", "A room echoing with the sounds of dripping water and skittering creatures.", enemyGroup1);
	auto dungeonRoom2 = std::make_shared<Room>("Dungeon Room 2", "A room filled with the stench of rot and decay.", enemyGroup2);
	theDungeon->ConnectRoom(dungeonRoom1);
	theDungeon->ConnectRoom(dungeonRoom2);
	dungeonRoom1->ConnectLocation(theDungeon);
	dungeonRoom2->ConnectLocation(theDungeon);

	// set starting location

	startLocation = theTavern;
}