#include "Combat.h"

Combat::Combat(std::shared_ptr<PlayerCharacter> player, std::vector<std::shared_ptr<CharacterTemplate>> combatants)
    : Player{ player }, Combatants{}, CurrentTurn{ 0 }, MaxTurns{ 999 }
{
    SpeedQueue.push(Player);

    for (const auto& combatant : Combatants)
    {
        SpeedQueue.push(combatant);
    }
}; // Default constructor



void Combat::CombatDisplay() {
    // print header
    system("cls");
    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "|           PREPARE FOR COMBAT           |" << std::endl;
    std::cout << "+----------------------------------------+" << std::endl;

    // print player details
    std::cout << "Player details:" << std::endl;
    std::cout << "Name: " << Player->GetName() << std::endl;
    std::cout << "Health: " << Player->GetCurrentHealth() << "/" << Player->GetMaxHealth() << std::endl;
    std::cout << "=========================================" << std::endl;
    //// print enemy details
    std::cout << "Enemy details:" << std::endl;
    for (auto& enemy : Enemies)
    {
        std::cout << "Name: " << enemy->GetName() << std::endl;
        std::cout << "Health: " << enemy->GetCurrentHealth() << std::endl;
        std::cout << "=========================================" << std::endl;
    }
    // print footer
    std::cout << "+----------------------------------------+" << std::endl;
}

void Combat::StartCombat()// Start combat
{
    // Add player
    Combatants.push_back(Player);

    // Sort Combatants by speed
    std::sort(Combatants.begin(), Combatants.end(),
        [](const std::shared_ptr<CharacterTemplate>& a, const std::shared_ptr<CharacterTemplate>& b) {
            return a->GetSpeed() > b->GetSpeed();
        });

    while (Player->GetCurrentHealth() > 0 && EnemiesAreAlive())
    {
		CombatDisplay();
		
        CurrentAction();

        if (Player->GetCurrentHealth() <= 0)
        {
			std::cout << "You have died!" << std::endl;
			break;
            // implement load function here
		}		
	}
}

void Combat::EndCombat() // End combat
{

}

bool Combat::EnemiesAreAlive() // Check if enemies are alive
{
    for (const auto& combatant : Combatants)
    {
        // Check if the combatant is an enemy and if they're alive
        if (std::dynamic_pointer_cast<Enemy>(combatant) && combatant->GetCurrentHealth() > 0)
        {
            return true;
        }
    }

    return false;
}
bool Combat::AlliesAreAlive() // Check if allies are alive
{
    for (const auto& combatant : Combatants)
    {
        // Check if the combatant is an ally and if they're alive
        if (std::dynamic_pointer_cast<PlayerCharacter>(combatant) && combatant->GetCurrentHealth() > 0)
        {
            return true;
        }
    }

    return false;
}
void Combat::HandleTurn() // Handle turn
{

}
void Combat::CheckVictory() // Check if the player has won
{

}
void Combat::CheckDefeat()// Check if the player has lost
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


