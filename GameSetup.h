#pragma once
#include "Location.h"
#include "Room.h"
#include "Tavern.h"
#include "Dungeon.h"
#include "Main.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "MainMenu.h"

//std::shared_ptr<Location> SetupGame(std::shared_ptr<PlayerCharacter> player);

void PrintIntro();

void PrintNumbers();

void TitleScreen();

void PrintCode();

std::string LoadingText();
