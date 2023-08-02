#pragma once

#include "Main.h"
#include "Item.h"

static std::unordered_map<int, std::shared_ptr<Item>> SetupItems()// create all items in game
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