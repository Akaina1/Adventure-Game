#include "GameSetup.h"

std::shared_ptr<Location> SetupGame(std::shared_ptr<PlayerCharacter> player) {
    // Create Tavern
    auto theTavern = std::make_shared<Tavern>("The Tavern", "A Place to Rest, Relax, Drink and forget about the monsters below us...", player);

    // Create Rooms for Tavern
    auto tavernRoom1 = std::make_shared<Room>("Tavern Room 1", "A cozy little room with a roaring fireplace.");
    auto tavernRoom2 = std::make_shared<Room>("Tavern Room 2", "A room filled with raucous laughter and song.");
    theTavern->ConnectRoom(tavernRoom1);
    theTavern->ConnectRoom(tavernRoom2);

    // Create Dungeon
    auto theDungeon = std::make_shared<Dungeon>("The Dungeon", "A dark, dreary dungeon teeming with dangerous creatures.");
    theTavern->ConnectLocation(theDungeon);

    // Create Rooms for Dungeon
    auto dungeonRoom1 = std::make_shared<Room>("Dungeon Room 1", "A room echoing with the sounds of dripping water and skittering creatures.");
    auto dungeonRoom2 = std::make_shared<Room>("Dungeon Room 2", "A room filled with the stench of rot and decay.");
    theDungeon->ConnectRoom(dungeonRoom1);
    theDungeon->ConnectRoom(dungeonRoom2);

    // Return the starting location for the game
    return theTavern;
}