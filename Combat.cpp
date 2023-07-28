#include "Combat.h"

void StartCombat()// Start combat
{

}
void EndCombat() // End combat
{

}
void PlayerAction() // Player action
{

}
void EnemyAction(int enemyIndex) // Enemy action
{

}
void AllyAction(int allyIndex) // Ally action
{

}
void HandleTurn() // Handle turn
{

}
void CheckVictory() // Check if the player has won
{

}
void CheckDefeat()// Check if the player has lost
{

}
//void CombatDisplay() // Display the combat - MIGHT implement later, very complicated
//{
//    _setmode(_fileno(stdout), _O_U16TEXT); // setmode for unicode output
//
//    HWND console = GetConsoleWindow(); // get console window
//    RECT ConsoleRect; // create a rectangle for the console window
//    GetWindowRect(console, &ConsoleRect); // get the console window rectangle
//    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 385, 900, TRUE); // set console window size
//    std::wstring enemyName = L"Goblin"; // enemy name
//    int enemyHealth = 80; // enemy health
//    int enemyMaxHealth = 100; // enemy max health
//
//    std::wstring playerName = L"Player"; // player name
//    int playerHealth = 95; // player health
//    int playerMaxHealth = 100; // player max health
//
//
//    std::wcout << L"╔══════════════════════════════════════════╗" << std::endl;
//    std::wcout << L"║            PREPARE FOR BATTLE            ║" << std::endl;
//    std::wcout << L"╟──────────────────────────────────────────╢" << std::endl;
//    std::wcout << L"║ Enemy: " << enemyName << L"                            ║" << std::endl;
//    std::wcout << L"║ Health: " << enemyHealth << L"/" << enemyMaxHealth << L"                           ║" << std::endl;
//    std::wcout << L"╟──────────────────────────────────────────╢" << std::endl;
//    std::wcout << L"║                                          ║" << std::endl;
//    std::wcout << L"║ Enemy: " << playerName << L"                            ║" << std::endl;
//    std::wcout << L"║ Health: " << playerHealth << L"/" << enemyMaxHealth << L"                           ║" << std::endl;
//    std::wcout << L"╟──────────────────────────────────────────╢" << std::endl;
//}

void Combat::CombatDisplay() {
    // print header
    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "|           PREPARE FOR COMBAT           |" << std::endl;
    std::cout << "+----------------------------------------+" << std::endl;

    // print player details
        std::cout << "Player details:" << std::endl;
        std::cout << "Name: " << Player->GetName() << std::endl;
        std::cout << "Health: " << Player->GetCurrentHealth() << "/" << Player->GetMaxHealth() << std::endl;
        std::cout << "=========================================" << std::endl;
    

    //// print enemy details
    //std::cout << "Enemy details:" << std::endl;
    //for (auto& enemy : enemies)
    //{
    //    std::cout << "Name: " << enemy->GetName() << std::endl;
    //    std::cout << "Health: " << enemy->GetHealth() << std::endl;
    //    std::cout << "=========================================" << std::endl;
    //}

    // print footer
    std::cout << "+----------------------------------------+" << std::endl;
 
}
