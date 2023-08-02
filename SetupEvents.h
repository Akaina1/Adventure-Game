#pragma once
#include "Main.h"
#include "Event.h"
#include "PlayerCharacter.h"

std::vector<std::shared_ptr<Event>> SetupEvents(std::shared_ptr<PlayerCharacter> player);