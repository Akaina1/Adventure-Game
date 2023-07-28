#pragma once
#include "Location.h"
#include "Room.h"
#include "Tavern.h"
#include "Dungeon.h"
#include "Main.h"

std::shared_ptr<Location> SetupGame(std::shared_ptr<PlayerCharacter> player);
