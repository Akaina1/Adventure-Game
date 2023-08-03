#pragma once

#include "Main.h"
#include "Enemy.h"
#include "GameManager.h"

static std::unordered_map<std::string, std::shared_ptr<Enemy>> SetupEnemies()
{
    std::unordered_map<std::string, std::shared_ptr<Enemy>> enemies;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    std::unordered_map<std::shared_ptr<Item>, std::pair<int, int>> itemRanges;

    std::shared_ptr<Item> item1 = GameManager::getInstance()->GetItem(0001); // get item from item manager (id 0001)
    itemRanges[item1] = { 1, 3 }; // add item to droptable with a minimum of 1 and a maximum of 3

    std::shared_ptr<Item> item2 = GameManager::getInstance()->GetItem(0002);
    itemRanges[item2] = { 1, 2 };

    DropTable dropTable(50, 100, 20, 50, itemRanges); // droptable with 50 minimum exp, 100 maximum exp, 20 minimum gold, 50 maximum gold, and the itemRanges


    std::shared_ptr<Enemy> goblin = std::make_shared<Enemy> // create goblin enemy
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
            {                        // statValues
                {"Strength", 5},
                {"Dexterity", 5},
                {"Wisdom", 5},
                {"Charisma", 5}
            },
            AttackType::Melee,       // baseAttackType
            {},                      // skills
            {},                      // afflictions
            dropTable
        );
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    return enemies;
}