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
    std::vector<std::shared_ptr<CharacterTemplate>> EnemiesGroup1;

    if (!goblin1 || !goblin2) {
        std::cout << "Failed to create goblins!" << std::endl;
        return 0 ;
    }


    EnemiesGroup1.push_back(goblin1);
    EnemiesGroup1.push_back(goblin2);

    if (EnemiesGroup1.size() != 2) {
        std::cout << "Failed to add goblins to EnemiesGroup1!" << std::endl;
        return 0;
    }

    std::shared_ptr<Enemy> hydra1 = std::make_shared<Enemy>("Hydra 1", 90, 100, 100, 100, 2);
    std::shared_ptr<Enemy> hydra2 = std::make_shared<Enemy>("Hydra 2", 70, 110, 110, 110, 3);
    std::vector<std::shared_ptr<CharacterTemplate>> EnemiesGroup2;
    EnemiesGroup2.push_back(hydra1);
    EnemiesGroup2.push_back(hydra2);


    // Create Dungeon
    auto theDungeon = std::make_shared<Dungeon>("The Dungeon", "A dark, dreary dungeon teeming with dangerous creatures.", player);
    theTavern->ConnectLocation(theDungeon);
    theDungeon->ConnectLocation(theTavern);


    // Create Rooms for Dungeon
    auto dungeonRoom1 = std::make_shared<Room>("Dungeon Room 1", "A room echoing with the sounds of dripping water and skittering creatures.", EnemiesGroup1);
    auto dungeonRoom2 = std::make_shared<Room>("Dungeon Room 2", "A room filled with the stench of rot and decay.", EnemiesGroup2);
    theDungeon->ConnectRoom(dungeonRoom1);
    theDungeon->ConnectRoom(dungeonRoom2);
    dungeonRoom1->ConnectRoom(dungeonRoom2);

    if (dungeonRoom1->GetCombatants().size() != 2) {
        std::cout << "Failed to add goblins to the room!" << std::endl;
        return 0;
    }

    // Return the starting location for the game
    return theTavern;
}

void TitleScreen()
{
    // implement basic splash screen with text and sound
}

void PrintNumbers()
{
    //numbers for intro print
    std::vector<std::string> numbers(100);

       for (int i = 0; i < 100; i++) 
       {
        numbers[i] = std::to_string(i + 1);

        std::cout << numbers[i] << "%" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        system("cls");
        
       }
}

void PrintIntro()
{
    HWND console = GetConsoleWindow(); // get console window
    RECT ConsoleRect; // create a rectangle for the console window
    GetWindowRect(console, &ConsoleRect); // get the console window rectangle
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 385, 900, TRUE); // set console window size

    // strings for intro print
    std::wstring test1 = L"Welcome to a ";
    std::wstring test2 = L"test";
    std::wstring test3 = L"game";
    std::wstring test4 = L"computer";
    std::wstring test5 = L"S I M U L A T I O N";
    std::wstring test6 = L" |WARNING AI [SENTIENCE.OBJ] FOUND|...";
    std::wstring test7 = L" |WARNING AI [REDACTED] FOUND|...";
    std::wstring test8 = L" |WARNING [NULL_PTR] FOUND|...";
    std::wstring test9 = L" |NEVERMIND...|...";
    std::wstring test10 = L" |SYSTEM RESTART TOTALLY SUCCESSFUL!|...\n";


    
    // begin intro print  
    TypeText(test1, 100);
    TypeText(test2, 100);
    EraseStringFromConsole(test2, 50);
    TypeText(test3, 100);
    EraseStringFromConsole(test3, 50);
    TypeText(test4, 100);
    EraseStringFromConsole(test4, 50);
    TypeText(test5, 100);
    system("cls");
    TypeText(L"This is a...", 100);

    TypeText(L"a...\n", 100);

    TypeText(L"...\n", 100);

    system("cls");
    TypeText(L" |S Y S T E M - E R R O R| \n", 50);

    TypeText(L"E...rr..0r...\n", 50);

    TypeText(L"Er..04...\n", 50);

    TypeText(L"------------------------------- \n", 50);
    TypeText(L"SYSTEM RESTART...\n", 50);
    PrintNumbers();
    TypeText(L"Loading ActualGame.file ...\n", 50);
    TypeText(L"Beginning Game Creation...\n", 50);
    TypeText(L"Building Game world...\n", 50);
    TypeText(L"Activating AI...\n", 50);
    TypeText(L"Starting Ga-...\n", 50);
    TypeText(test6, 30);
    EraseStringFromConsole(test6, 10);
    TypeText(test7, 30);
    EraseStringFromConsole(test7, 10);
    TypeText(test8, 30);
    EraseStringFromConsole(test8, 10);
    TypeText(test9, 30);
    EraseStringFromConsole(test9, 30);
    TypeText(test10, 30);
    TypeText(L"------------------------------- \n", 50);
    PrintNumbers();
    TypeText(L"Starting Game.\n", 50);
    system("cls");
    system("pause");
    TitleScreen();
    MainMenu();
}