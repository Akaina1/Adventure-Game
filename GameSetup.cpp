#include "GameSetup.h"

std::shared_ptr<Location> SetupGame(std::shared_ptr<PlayerCharacter> player) {
    // Create Tavern
    auto theTavern = std::make_shared<Tavern>("The Tavern", "A Place to Rest, Relax, Drink and forget about the monsters below us...", player);

    // Create Rooms for Tavern
    auto tavernRoom1 = std::make_shared<Room>("Tavern Room 1", "A cozy little room with a roaring fireplace.");
    auto tavernRoom2 = std::make_shared<Room>("Tavern Room 2", "A room filled with raucous laughter and song.");
    theTavern->ConnectRoom(tavernRoom1);
    theTavern->ConnectRoom(tavernRoom2);

    //create enemies for Dungeon
    std::shared_ptr<Enemy> goblin1 = std::make_shared<Enemy>("Goblin 1", 90, 100, 100, 100, 2);
    std::shared_ptr<Enemy> goblin2 = std::make_shared<Enemy>("Goblin 2", 70, 110, 110, 110, 3);
    std::vector<std::shared_ptr<Enemy>> EnemiesGroup1;
    EnemiesGroup1.push_back(goblin1);
    EnemiesGroup1.push_back(goblin2);

    std::shared_ptr<Enemy> hydra1 = std::make_shared<Enemy>("Hydra 1", 90, 100, 100, 100, 2);
    std::shared_ptr<Enemy> hydra2 = std::make_shared<Enemy>("Hydra 2", 70, 110, 110, 110, 3);
    std::vector<std::shared_ptr<Enemy>> EnemiesGroup2;
    EnemiesGroup1.push_back(hydra1);
    EnemiesGroup1.push_back(hydra2);


    // Create Dungeon
    auto theDungeon = std::make_shared<Dungeon>("The Dungeon", "A dark, dreary dungeon teeming with dangerous creatures.");
    theTavern->ConnectLocation(theDungeon);

    // Create Rooms for Dungeon
    auto dungeonRoom1 = std::make_shared<Room>("Dungeon Room 1", "A room echoing with the sounds of dripping water and skittering creatures.", EnemiesGroup1);
    auto dungeonRoom2 = std::make_shared<Room>("Dungeon Room 2", "A room filled with the stench of rot and decay.", EnemiesGroup2);
    theDungeon->ConnectRoom(dungeonRoom1);
    theDungeon->ConnectRoom(dungeonRoom2);

    // Return the starting location for the game
    return theTavern;
}