#pragma once

#include "Main.h"
#include "Enemy.h"

static std::unordered_map<std::string, std::shared_ptr<Enemy>> SetupEnemies()
{
    std::unordered_map<std::string, std::shared_ptr<Enemy>> enemies;

    // Here you would create your Enemy objects and add them to the 'enemies' map.

    return enemies;
}