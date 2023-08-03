#include "GameManager.h"

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
		return enemies[name];
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
			[](PlayerCharacter& player)  // effect
			{
				player.heal(20);
			}
	);

	std::shared_ptr<Item> healingPotion = std::make_shared<Item> // create healing potion
		(
			"Healing Potion",            // name
			"Restores 50 HP",            // description
			0002,                        // id
			80,							 // price in gold
			ItemType::CONSUMABLE,		 // type
			[](PlayerCharacter& player)  // effect
			{
				player.heal(50);
			}
	);

	std::shared_ptr<Item> mediumHealingPotion = std::make_shared<Item> // create super healing potion
		(
			"Medium Healing Potion",     // name
			"Restores 80 HP",            // description
			0003,                        // id
			100,					     // price in gold
			ItemType::CONSUMABLE,		 // type
			[](PlayerCharacter& player)  // effect
			{
				player.heal(80);
			}
	);

	std::shared_ptr<Item> largeHealingPotion = std::make_shared<Item> // create super healing potion
		(
			"Large Healing Potion",      // name
			"Restores 120 HP",           // description
			0004,                        // id
			150,						 // price in gold
			ItemType::CONSUMABLE,		 // type
			[](PlayerCharacter& player)  // effect
			{
				player.heal(120);
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

		std::shared_ptr<Item> item1 = getInstance()->GetItem(0001); // get item from item manager (id 0001)
		itemRanges[item1] = { 1, 3 }; // add item to droptable with a minimum of 1 and a maximum of 3

		std::shared_ptr<Item> item2 = getInstance()->GetItem(0002);
		itemRanges[item2] = { 1, 2 };

		auto dropTablePtr = std::make_shared<DropTable>(50, 100, 20, 50, itemRanges);
		// droptable with 50 minimum exp, 100 maximum exp, 20 minimum gold, 50 maximum gold, and the itemRanges

		std::vector<Skill> emptySkills;
		std::vector<EffectPtr> emptyAfflictions;
		std::map<std::string, int> statValues = { {"Strength", 5}, {"Dexterity", 5}, {"Wisdom", 5}, {"Charisma", 5} };

		std::shared_ptr<Enemy> goblin = std::make_shared<Enemy>// create goblin enemy
			(
				"Goblin",                // name
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

		enemies[goblin->GetName()] = goblin; // add to enemies map
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