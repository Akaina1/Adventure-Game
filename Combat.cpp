﻿#include "Combat.h"

Combat::Combat(std::shared_ptr<PlayerCharacter> player, std::deque<std::shared_ptr<CharacterTemplate>> combatants)
    : Player{ player }, Combatants{combatants}, CurrentTurn{ 0 }, MaxTurns{ 999 } {}; // Default constructor

void Combat::CombatDisplay() {
    // print header
    system("cls");
    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "|           PREPARE FOR COMBAT           |" << std::endl;
    std::cout << "+----------------------------------------+" << std::endl;

    std::cout << "Number of combatants: " << Combatants.size() << std::endl;

    // print player details
    std::cout << "Player details:" << std::endl;
    for (auto& combatant : Combatants)
    {
        //std::cout << "Combatant type: " << typeid(*combatant).name() << std::endl;


        auto player = std::dynamic_pointer_cast<PlayerCharacter>(combatant);
        if (player != nullptr) {
            std::cout << "Name: " << player->GetName() << std::endl;
            std::cout << "Health: " << player->GetCurrentHealth() << "/" << player->GetMaxHealth() << std::endl;
            std::cout << "Mana: " << player->GetCurrentMana() << "/" << player->GetMaxMana() << std::endl;
            std::cout << "=========================================" << std::endl;
        }
        //else {
            //std::cout << "Failed to cast combatant to Enemy." << std::endl;
        //}
    }

    // print ally details
    std::cout << "Ally details:" << std::endl;
    for (auto& combatant : Combatants)
    {
        auto ally = std::dynamic_pointer_cast<NPC>(combatant);
        if (ally != nullptr) {
            std::cout << "Name: " << ally->GetName() << std::endl;
            std::cout << "Health: " << ally->GetCurrentHealth() << "/" << ally->GetMaxHealth() << std::endl;
            std::cout << "Mana: " << ally->GetCurrentMana() << "/" << ally->GetMaxMana() << std::endl;
            std::cout << "=========================================" << std::endl;
        }
        else
        {
            std::cout << "No Allies" << std::endl;
            std::cout << "=========================================" << std::endl;
            continue;
        }
    }

    //// print enemy details
    std::cout << "Enemy details:" << std::endl;
    for (auto& combatant : Combatants)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(combatant);
        if (enemy != nullptr) {
            std::cout << "Name: " << enemy->GetName() << std::endl;
            std::cout << "Health: " << enemy->GetCurrentHealth() << "/" << enemy->GetMaxHealth() << std::endl;
            std::cout << "Mana: " << enemy->GetCurrentMana() << "/" << enemy->GetMaxMana() << std::endl;
            std::cout << "=========================================" << std::endl;
        }
    }
    // print footer
    std::cout << "+----------------------------------------+" << std::endl;
}

void Combat::StartCombat() // Start combat
{
    // add room combatants to combatants vector
    CurrentTurn = 1;
  
    // Sort Combatants by speed
    std::sort(Combatants.begin(), Combatants.end(),
        [](const std::shared_ptr<CharacterTemplate>& a, const std::shared_ptr<CharacterTemplate>& b) {
            return a->GetSpeed() > b->GetSpeed();
        });

    // Call combat display
    CombatDisplay();

    // Main combat loop
    CurrentAction();

    // End combat
    EndCombat();
}

void Combat::CurrentAction()
{
    while (true) // loop until break
    {
       // sort combatants by speed
        std::sort(Combatants.begin(), Combatants.end(),
            [](const std::shared_ptr<CharacterTemplate>& a, const std::shared_ptr<CharacterTemplate>& b) {
				return a->GetSpeed() > b->GetSpeed();
			});
      
        // All combatants have their turn
        while (!Combatants.empty())
        {
            auto fastestCombatant = Combatants.front();
            Combatants.pop_front();

            // Skip this combatant if they are dead
            if (fastestCombatant->GetCurrentHealth() <= 0)
            {
                continue;
            }

            // Combatant takes their turn
            fastestCombatant->PerformAction(Combatants); // Perform action

            // If all allies or enemies are dead, end combat
            if (!AlliesAreAlive() || !EnemiesAreAlive())
            {
                return;
            }

            // Check and update effects duration for the character
            UpdateEffectsDuration(*fastestCombatant);

            // Push the combatant back into the Combatants vector
            Combatants.push_back(fastestCombatant);
  
        }

        CurrentTurn++;

        std::cout << "Turn: " << CurrentTurn << std::endl;
        std::cout << "+----------------------------------------+" << std::endl;
    }
}

void Combat::EndCombat() // End combat
{
    if (!EnemiesAreAlive())
    {
        std::cout << "+----------------------------------------+" << std::endl;
        std::cout << "Victory!\n";
        std::cout << "+----------------------------------------+" << std::endl;

        // Implement victory rewards, experience gain, etc. here

    }
    else if (!AlliesAreAlive() || Player->GetCurrentHealth() <= 0)
    {
        std::cout << "+----------------------------------------+" << std::endl;
        std::cout << "Defeat!\n";
        std::cout << "+----------------------------------------+" << std::endl;
        // Implement defeat penalties, game over screen, etc. here

    }
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
void Combat::UpdateEffectsDuration(CharacterTemplate& character) // Update effects duration
{
    for (auto it = character.GetAfflictions().begin(); it != character.GetAfflictions().end();)
    {
        if ((*it)->GetDuration() > 0)
        {
            (*it)->DecreaseDuration(1); // Decrement the effect's duration by 1
            if ((*it)->GetDuration() == 0)
            {
                // Remove the effect from the character's Afflictions vector
                it = character.GetAfflictions().erase(it);
            }
            else
            {
                ++it;
            }
        }
        else
        {
            ++it;
        }
    }
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


