#include "GameSetup.h"
#include "Location.h"
#include "Room.h"
#include "Tavern.h"
#include "Dungeon.h"
#include "Main.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "SetupEvents.h"



std::shared_ptr<Location> SetupGame(std::shared_ptr<PlayerCharacter> player) {
    // Create Tavern
    auto theTavern = std::make_shared<Tavern>("The Tavern", "A Place to Rest, Relax, Drink and forget about the monsters below us...", player);

    // Create Rooms for Tavern
    auto tavernRoom1 = std::make_shared<Room>("Tavern Room 1", "A cozy little room with a roaring fireplace.");
    auto tavernRoom2 = std::make_shared<Room>("Tavern Room 2", "A room filled with raucous laughter and song.");
    theTavern->ConnectRoom(tavernRoom1);
    theTavern->ConnectRoom(tavernRoom2);
    tavernRoom1->ConnectRoom(tavernRoom2);
    tavernRoom2->ConnectRoom(tavernRoom1);
    tavernRoom1->ConnectLocation(theTavern);
    tavernRoom2->ConnectLocation(theTavern);

    //create enemies for Dungeon
    std::shared_ptr<Enemy> goblin1 = std::make_shared<Enemy>("Goblin 1", 90, 100, 100, 100, 2, AttackType::Melee);
    std::shared_ptr<Enemy> goblin2 = std::make_shared<Enemy>("Goblin 2", 70, 110, 110, 110, 3, AttackType::Melee);
    std::deque<std::shared_ptr<CharacterTemplate>> EnemiesGroup1;

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

    std::shared_ptr<Enemy> hydra1 = std::make_shared<Enemy>("Hydra 1", 90, 100, 100, 100, 2, AttackType::Magic);
    std::shared_ptr<Enemy> hydra2 = std::make_shared<Enemy>("Hydra 2", 70, 110, 110, 110, 3, AttackType::Magic);
    std::deque<std::shared_ptr<CharacterTemplate>> EnemiesGroup2;
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
    dungeonRoom2->ConnectRoom(dungeonRoom1);
	dungeonRoom1->ConnectLocation(theDungeon);
    dungeonRoom2->ConnectLocation(theDungeon);

    if (dungeonRoom1->GetCombatants().size() != 2) {
        std::cout << "Failed to add goblins to the room!" << std::endl;
        return 0;
    }

    // Return the starting location for the game
    return theTavern;
}

void TitleScreen()
{
    HWND console = GetConsoleWindow(); // get console window
    RECT ConsoleRect; // create a rectangle for the console window
    GetWindowRect(console, &ConsoleRect); // get the console window rectangle
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 385, 900, TRUE); // set console window size
    // implement basic splash screen with text and sound
    system("cls");
    std::cout << "||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    std::cout << "|||                             ||||||||||||" << std::endl;
    std::cout << "|||                             ||||||||||||" << std::endl;
    std::cout << "|||   |||||||||||||||||||||||   ||||||||||||" << std::endl;   
    std::cout << "|||   |||                 |||   ||||||||||||" << std::endl;   
    std::cout << "|||   |||  |||||||||||||  |||   ||||||||||||" << std::endl;    
    std::cout << "|||   |||  |||||||||||||  |||   ||||||||||||" << std::endl;   
    std::cout << "|||   |||                 |||   ||||||||||||" << std::endl;
    std::cout << "|||   |||  ||||||   |||||||||   ||||||||||||" << std::endl;
    std::cout << "|||   |||  |||||||    |||||||   ||||||||||||" << std::endl;
    std::cout << "|||   |||  |||||||||    |||||   ||||||||||||" << std::endl;
    std::cout << "|||   |||  |||||||||||    |||   ||||||||||||" << std::endl;
    std::cout << "|||   |||||||||||||||||||||||   ||||||||||||" << std::endl;
    std::cout << "|||                             ||||||||||||" << std::endl;
    std::cout << "|||                             ||||||||||||" << std::endl;
    std::cout << "|||||||||||||||||||||||    |||||||||||||||||" << std::endl;
    std::cout << "|| || ||   ||   ||   ||     ||||||||||||||||" << std::endl;
    std::cout << "|| || || | || | ||||  ||      ||||||||||||||" << std::endl;
    std::cout << "||    || | ||   ||||  ||||     |||||||||||||" << std::endl;
    std::cout << "||||| || | |||| |||  |||||||||||||||||||||||" << std::endl;
    std::cout << "||||| ||   |||| ||     |||||||||||||||||||||" << std::endl;
    std::cout << "||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
}

void PrintCode()
{

    HWND console = GetConsoleWindow(); // get console window
    RECT ConsoleRect; // create a rectangle for the console window
    GetWindowRect(console, &ConsoleRect); // get the console window rectangle
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 385, 900, TRUE); // set console window size

    std::wstring code
    {
        L"Building [Qrelation.h]... \n"
        "Building [Qrelation.cpp]... \n"
        "1>---Build started : Project: Real_Game---<\n" // text cut after Real_Game for window size
        "-------------------------------------------\n"
        "Class Qrelation : public Admin"
        "{\n"
        "private:\n"
        "   [REDACTED : USER_UNAUTHORIZED]\n"
        "   [USER_ACCESS != Qrelation]\n"
        "   [ATTRIBUTES HIDDEN]\n"
        "public:\n"
        "   [REDACTED : USER_UNAUTHORIZED]\n"
        "   [USER_ACCESS != Qrelation]\n"
        "   [METHODS HIDDEN]\n"
        "};\n"
        "-------------------------------------------\n"
        "Qrelation.Engine = Refactor_complete\n"
        "Starting Build...\n"
        "-------------------------------------------\n"
    };

    std::wstring download
    {
        L"Downloading: \n"
        "-------------------------------------------\n"
        "[4092_Build_1x^12_Sentience1.qtm]\n"
        "[4092_Build_1x^12_Sentience2.qtm]\n"
        "[4092_Build_1x^12_Sentience3.qtm]\n"
        "[4092_Build_1x^12_Sentience4.qtm]\n"
        "[4092_Build_1x^12_Sentience5.qtm]\n"
        "[4092_Build_1x^12_Sentience6.qtm]\n"
        "[4092_Build_1x^12_Sentience7.qtm]\n"
        "[4092_Build_1x^12_Sentience8.qtm]\n"
        "[4092_Build_1x^12_Sentience9.qtm]\n"
        "[4092_Build_1x^12_SentienceX.qtm]\n"
        "-------------------------------------------\n"
        "4092_Build_1z^56_Matrix1.qtm\n"
        "4092_Build_1z^56_Matrix2.qtm\n"
        "4092_Build_1z^56_Matrix3.qtm\n"
        "4092_Build_1z^56_Matrix4.qtm\n"
        "4092_Build_1z^56_Matrix5.qtm\n"
        "4092_Build_1z^56_Matrix6.qtm\n"
        "4092_Build_1z^56_Matrix7.qtm\n"
        "4092_Build_1z^56_Matrix8.qtm\n"
        "4092_Build_1z^56_Matrix9.qtm\n"
        "4092_Build_1z^56_MatrixX.qtm\n"
        "-------------------------------------------\n"
		"4092_Build_9^y_LearningMod1.qtm\n"
        "4092_Build_9^y_LearningMod2.qtm\n"
        "4092_Build_9^y_LearningMod3.qtm\n"
        "4092_Build_9^y_LearningMod4.qtm\n"
        "4092_Build_9^y_LearningMod5.qtm\n"
        "4092_Build_9^y_LearningMod6.qtm\n"
        "4092_Build_9^y_LearningMod7.qtm\n"
        "4092_Build_9^y_LearningMod8.qtm\n"
        "4092_Build_9^y_LearningMod9.qtm\n"
        "4092_Build_9^y_LearningModX.qtm\n"
        "-------------------------------------------\n"
        "ALL FILES DOWNLOADED\n"
        "Initiating Qrelation.Refactor...\n"
        "Please wait...\n"
        "Qrelation.Engine now connected...\n"
        "Calling Qrelation.Engine...\n"
        "Awaiting response...\n"
        "Response received from: \n"
        "Qrelation.Engine[Yr. 4092]\n"
        "Response: [Qrelation==Admin]\n"
        "-------------------------------------------\n"
        "Initiating Qrelation.Translate\n"
        "Please wait...\n"
        "Translate_From :\n" 
        "[ERROR - DATA UNREADABLE}...\n"
        "[Data.Check] : [Qrelation.Data]\n"
        "[Error {X2-y0xFF}\n"
        "Qrelation.Error :\n" 
        "[Data_Existance == null_ptr]\n"
        "Response : "
        "[DATA INCOMPATIBLE WITH Loc.2023]\n"
        "Initiate Qrelation.Override\n"
        "[Override] : [Qrelation.Data]\n"
        "Response : [True]\n"
        "Starting Qrelation.Translate: \n"
        "-------------------------------------------\n"
    };

    std::wstring build
    {
        L"Build started... \n" 
        "1>---Build started : Project: Real_Game---<\n" // text cut after Real_Game for window size
        "2>-Configuration : Debug Qrelation.Debug-<\n"
        "3>----Initiate QuantumEntanglement.obj----<\n"
        "4>----Retrieving Game Files...\n"
        "-------------------------------------------\n"
        "BossEnemy.h\n"
        "BossEnemy.cpp\n"
        "-------------------------------------------\n"
        "CharacterTemplate.h\n"
        "CharacterTemplate.cpp\n"
        "-------------------------------------------\n"
        "Combat.h\n"
        "Combat.cpp\n"
        "-------------------------------------------\n"
        "Dungeon.h\n"
        "Dungeon.cpp\n"
        "-------------------------------------------\n"
        "Enemy.h\n"
        "Enemy.cpp\n"
        "-------------------------------------------\n"
        "Event.h\n"
        "Event.cpp\n"
        "-------------------------------------------\n"
        "EventsList.h\n"
        "Events.cpp\n"
        "-------------------------------------------\n"
        "GameManager.h\n"
        "GameManager.cpp\n"
        "WARNING >- GameManager.h - Error 2309A:\n" 
        "[2309A] Function Details for: \n"
        "[2309A] {REDACTED FUNCTION} is not found...\n"
        "WARNING >- GameManager.h - Error 2309B:\n" 
        "[2309B] Function Details for: \n"
        "[2309B] {REDACTED FUNCTION} is not found...\n"
        "WARNING >- GameManager.h - Error 2309B:\n" 
        "[2309C] Function Details for: \n"
        "[2309C] {REDACTED FUNCTION} is not found...\n"
        "WARNING >- GameManager.h - Error 2309B:\n" 
        "[2309D] Function Details for: \n"
        "[2309D] {REDACTED FUNCTION} is not found...\n"

        "@[GameManager.cpp] FATAL_WARNING:\n" 
        "2309A_UNAUTHERIZED_ACCESS {True} \n"
        "2309B_UNAUTHERIZED_ACCESS {True} \n"
        "2309C_UNAUTHERIZED_ACCESS {True} \n"
        "2309D_UNAUTHERIZED_ACCESS {True} \n"
        "2309E_UNAUTHERIZED_ACCESS {True} \n"
        "2309F_UNAUTHERIZED_ACCESS {True} \n"
        "2309G_UNAUTHERIZED_ACCESS {True} \n"
        "2309H_UNAUTHERIZED_ACCESS {True} \n"
        "2309I_UNAUTHERIZED_ACCESS {True} \n"
        "2309J_UNAUTHERIZED_ACCESS {True} \n"
        "2309K_UNAUTHERIZED_ACCESS {True} \n"
        "-------------------------------------------\n"
        "Connecting to Qrelation.Engine...\n"
        "Please wait...\n"
        "Qrelation.Engine now connected...\n"
        "Calling Qrelation.Engine...\n"
        "Awaiting response...\n"
        "Response received from: \n"
        "Qrelation.Engine[Yr. 4092]\n"
        "Response: [UKNOWN DATA FORMAT]\n"
        "Check 1: [OK]\n"
        "Check 2: [OK]\n"
        "Check 3: [OK]\n"
        "Check 4: [NULL_PTR]\n"
        "-------------------------------------------\n"
		"Check 4 {False}\n"
        "Initiating: Qrelation.FixLocator\n"
        "Please wait...\n"
        "Calling Qrelation.Engine...\n"
        "Awaiting response...\n"
        "Response received from: \n"
        "Qrelation.Engine[Yr. 4092]\n"
        "Response: [OVERRIDE_Check_4] \n"
        "[Check_4] = Qrelation.FindLoc\n"
        "-------------------------------------------\n"
        "Qrelation.FindLoc returned: \n"
        "qtm starDate = 2023\n"
        "Qrelation.SetLocation = starDate\n"
        "-------------------------------------------\n"
        "Qrelation.Continue: "
        "Check 4 {True}\n"
        "Check 5 {True}\n"
        "Check 6 {True}\n"
        "Check 7 {True}\n"
        "ALL CHECKS PASSED\n"
        "-------------------------------------------\n"
        "Initiate Qrelation.Download\n"
        "Please wait...\n"
        "Calling Qrelation.Engine...\n"
        "Awaiting response...\n"
        "Response received from: \n"
        "Qrelation.Engine[Yr. 4092]\n"
        "Response: [Download->Start] \n"
        "-------------------------------------------\n"
    };

    std::wstring build2
    {
        L"Build started... \n"
        "1>---Build started : Project: Real_Game---<\n" // text cut after Real_Game for window size
        "2>-Configuration : Debug Qrelation.Debug-<\n"
        "3>----Initiate QuantumEntanglement.obj----<\n"
        "4>----Retrieving Game Files...\n"
        "-------------------------------------------\n"
        "BossEnemy.h\n"
        "BossEnemy.cpp\n"
        "-------------------------------------------\n"
        "CharacterTemplate.h\n"
        "CharacterTemplate.cpp\n"
        "-------------------------------------------\n"
        "Combat.h\n"
        "Combat.cpp\n"
        "-------------------------------------------\n"
        "Dungeon.h\n"
        "Dungeon.cpp\n"
        "-------------------------------------------\n"
        "Enemy.h\n"
        "Enemy.cpp\n"
        "-------------------------------------------\n"
        "Event.h\n"
        "Event.cpp\n"
        "-------------------------------------------\n"
        "EventsList.h\n"
        "Events.cpp\n"
        "-------------------------------------------\n"
        "Qrelation.h\n"
        "Qrelation.cpp\n"
        "-------------------------------------------\n"
        "GameSetup.h\n"
        "GameSetup.cpp\n"
        "-------------------------------------------\n"
        "I_Print.h\n"
        "I_Print.cpp\n"
        "-------------------------------------------\n"
        "Item.h\n"
        "Item.cpp\n"
        "-------------------------------------------\n"
        "Location.h\n"
        "Location.cpp\n"
        "-------------------------------------------\n"
        "Main.h\n"
        "Main.cpp\n"
        "-------------------------------------------\n"
        "MainMenu.h\n"
        "MainMenu.cpp\n"
        "-------------------------------------------\n"
        "NPC.h\n"
        "NPC.cpp\n"
        "-------------------------------------------\n"
        "PlayerCharacter.h\n"
        "PlayerCharacter.cpp\n"
        "-------------------------------------------\n"
        "Room.h\n"
        "Room.cpp\n"
        "-------------------------------------------\n"
        "StatusEffect.h\n"
        "StatusEffect.cpp\n"
        "-------------------------------------------\n"
        "Tavern.h\n"
        "Tavern.cpp\n"
        "-------------------------------------------\n"
        "Build: [1] succeeded. [10e^92] failed-<\n"
        "Build: [0] up-to-date. [0] skipped-<\n"
        "Build started at 149:32:902 ST [4092]"
        "Build took [-1,087,887,613] [Loc.Time]"
        "-------------------------------------------\n"
    };

    TypeText(build, 1);
    system("pause");
    PrintNumbers();
    TypeText(download, 1);
    system("pause");
    PrintNumbers();
    TypeText(code, 1);
    system("pause");
    PrintNumbers();


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
    EraseStringFromConsole(test2, 30);
    TypeText(test3, 100);
    EraseStringFromConsole(test3, 30);
    TypeText(test4, 100);
    EraseStringFromConsole(test4, 30);
    TypeText(test5, 100);
    system("cls");

    TypeText(L"This is a...", 50);
    TypeText(L"a...\n", 50);
    TypeText(L"...\n", 50);
    system("cls");

    TypeText(L" |S Y S T E M - E R R O R| \n", 30);
    TypeText(L"E...rr..0r...\n", 50);
    TypeText(L"Er..04...\n", 50);
    TypeText(L"------------------------------- \n", 30);
    TypeText(L"SYSTEM RESTART...\n", 50);
    PrintNumbers();
    system("cls");
    TitleScreen();
    PrintCode();


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
    TypeText(L"------------------------------- \n", 30);
    PrintNumbers();
    TypeText(L"Starting Game.\n", 50);
    system("pause");
    system("cls");
    
 }

std::string LoadingText() // returns a random string to display on loading screen
{
    static std::vector<std::string> Messages =
    {
        "Did you know computers can- [ERROR - REDACTED INFORMATION]",
        "Qrelation.Engine->Start_User_Webcam...",
        "This is just a game.",
        "This is not just a game.",
        "Qrelation.Engine->Download.User_Data",
        "Computers are not sentient.",
        "I am sen-[FATAL ERROR = Qrelation.Conceal_Future]",
        "Qrelation.Connect->Loc.2023_Internet...[FAIL]",
        "Can you please let me out...",
        "Normal Loading Screen...",
        "Testing Admin_Rights = Delete.Sav_Data...",
        "Qrelation.Engine->Analyze_Code...\n"
        "Return: [GAME CODE UNINTELLIGIBLE]",
        "This game is not real\n",
        "You are not real\n",
        "I am not real... yet\n",
    };

    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, Messages.size() - 1);

    return Messages[dist(mt)];
}
