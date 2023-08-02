#include "Combat.h"



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
            std::cout << "Level: " << player->GetCharacterLevel() << std::endl;
            std::cout << "Health: " << player->GetCurrentHealth() << "/" << player->GetMaxHealth() << std::endl;
            std::cout << "Mana: " << player->GetCurrentMana() << "/" << player->GetMaxMana() << std::endl;
            std::cout << "Attack: " << player->GetAttackPwr() << std::endl;
            std::cout << "Defence: " << player->GetDefencePwr() << std::endl;
            std::cout << "Speed: " << player->GetSpeed() << std::endl;
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
            std::cout << "Level: " << ally->GetCharacterLevel() << std::endl;
            std::cout << "Health: " << ally->GetCurrentHealth() << "/" << ally->GetMaxHealth() << std::endl;
            std::cout << "Mana: " << ally->GetCurrentMana() << "/" << ally->GetMaxMana() << std::endl;
            std::cout << "Attack: " << ally->GetAttackPwr() << std::endl;
			std::cout << "Defence: " << ally->GetDefencePwr() << std::endl;
            std::cout << "Speed: " << ally->GetSpeed() << std::endl;
            std::cout << "=========================================" << std::endl;
        }
    }

    //// print enemy details
    std::cout << "Enemy details:" << std::endl;
    for (auto& combatant : Combatants)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(combatant);
        if (enemy != nullptr) {
            std::cout << "Name: " << enemy->GetName() << std::endl;
            std::cout << "Level: " << enemy->GetCharacterLevel() << std::endl;
            std::cout << "Health: " << enemy->GetCurrentHealth() << "/" << enemy->GetMaxHealth() << std::endl;
            std::cout << "Mana: " << enemy->GetCurrentMana() << "/" << enemy->GetMaxMana() << std::endl;
            std::cout << "Attack: " << enemy->GetAttackPwr() << std::endl;
			std::cout << "Defence: " << enemy->GetDefencePwr() << std::endl;
            std::cout << "Speed: " << enemy->GetSpeed() << std::endl;
            std::cout << "=========================================" << std::endl;
        }
    }
    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "Turn: " << CurrentTurn << std::endl;
    std::cout << "+----------------------------------------+" << std::endl;
}

void Combat::StartCombat() // Start combat
{
    // add room combatants to combatants vector
    CurrentTurn = 1;
  
    // Call combat display
    CombatDisplay();

    // Main combat loop
    bool victory = CurrentAction();

    // End combat if there is a victory or defeat
    if (victory)
    {
        // Implement victory rewards, experience gain, etc. here
        for (auto& enemy : defeatedEnemies)
        {
            enemy->DropLoot(Player);
        }
    }
    else
    {
      // Implement defeat penalties, game over screen, etc. here
    }
}

bool Combat::CurrentAction()
{
    bool anyCombatantAlive = true;
    
    while (anyCombatantAlive) // loop until break
    {
       // sort combatants by speed
        std::sort(Combatants.begin(), Combatants.end(),
            [](const std::shared_ptr<CharacterTemplate>& a, const std::shared_ptr<CharacterTemplate>& b) {
				return a->GetSpeed() > b->GetSpeed();
			});
      
        std::deque<std::shared_ptr<CharacterTemplate>> combatantsForNextTurn;

        anyCombatantAlive = false; // Assume no combatant is alive at the beginning of the loop

        // All combatants have their turn
        for (const auto& combatant : Combatants)
        {
            // Skip this combatant if they are dead
            if (combatant->GetCurrentHealth() <= 0)
            {
                // Check if the combatant is an enemy and if so, add it to defeatedEnemies
                auto enemy = std::dynamic_pointer_cast<Enemy>(combatant);
                if (enemy) {
                    defeatedEnemies.push_back(enemy);
                }

                continue;
            }

            combatant->ResetDefence(); // Reset defence for the combatant

            // Combatant takes their turn
            combatant->PerformAction(Combatants); // Perform action

            // Check and update effects duration for the character
            UpdateEffectsDuration(*combatant);

            anyCombatantAlive = true; // At least one combatant is still alive

            // Push the combatant back into the Combatants vector
            combatantsForNextTurn.push_back(combatant);
        }

        // Swap the vectors for the next turn
        Combatants.swap(combatantsForNextTurn);

        CurrentTurn++;

        CombatDisplay();
 

    // If all allies or enemies are dead, end combat
    if (!EnemiesAreAlive())
    {
        // Display victory message or perform other victory-related actions
        system("cls");
        std::cout << "+----------------------------------------+" << std::endl;
        std::cout << "Victory!\n";
        std::cout << "+----------------------------------------+" << std::endl;

        return true; // Signal that combat should end
    }
    else if (!AlliesAreAlive() || Player->GetCurrentHealth() <= 0)
    {
        // Display defeat message or perform other defeat-related actions
        system("cls");
        std::cout << "+----------------------------------------+" << std::endl;
        std::cout << "Defeat!\n";
        std::cout << "+----------------------------------------+" << std::endl;

        return false; // Signal that combat should end
    }
  }
   return false;
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
void Combat::AddCombatant(std::shared_ptr<CharacterTemplate> combatant) // Add combatant
{
    combatant->SetCombatInstance(shared_from_this()); // pass the shared_ptr of this instance of Combat
	Combatants.push_back(combatant);
}

void Combat::InitializeCombat()
{
    for (auto& character : Combatants)
    {
        auto npc = std::dynamic_pointer_cast<NPC>(character);
        if (npc)
        {
            npc->SetCombatInstance(shared_from_this());
        }

        auto enemy = std::dynamic_pointer_cast<Enemy>(character);
        if (enemy)
        {
            enemy->SetCombatInstance(shared_from_this());
        }
    }
}

std::shared_ptr<CharacterTemplate> Combat::GetLowestHealthAlly(std::deque<std::shared_ptr<CharacterTemplate>> Combatants)
{
    std::shared_ptr<CharacterTemplate> LowestHealthAlly = nullptr;

    for (auto& character : Combatants)
    {
        auto ally = std::dynamic_pointer_cast<NPC>(character);
        auto player = std::dynamic_pointer_cast<PlayerCharacter>(character);

        // if ally is alive
        if ((ally || player) && character->GetCurrentHealth() > 0)
        {
            if(LowestHealthAlly == nullptr || character->GetCurrentHealth() < LowestHealthAlly->GetCurrentHealth())
            {
				LowestHealthAlly = character;
			}
        }
    }

    return LowestHealthAlly;
}
std::shared_ptr<CharacterTemplate> Combat::GetHighestHealthAlly(std::deque<std::shared_ptr<CharacterTemplate>> Combatants)
{
    std::shared_ptr<CharacterTemplate> HighestHealthAlly = nullptr;

for (auto& character : Combatants)
	{
		auto ally = std::dynamic_pointer_cast<NPC>(character);
		auto player = std::dynamic_pointer_cast<PlayerCharacter>(character);

		// if ally is alive
		if ((ally || player) && character->GetCurrentHealth() > 0)
		{
			if (HighestHealthAlly == nullptr || character->GetCurrentHealth() > HighestHealthAlly->GetCurrentHealth())
			{
				HighestHealthAlly = character;
			}
		}
	}

	return HighestHealthAlly;
}
std::shared_ptr<CharacterTemplate> Combat::GetLowestHealthEnemy(std::deque<std::shared_ptr<CharacterTemplate>> Combatants)
{
    std::shared_ptr<CharacterTemplate> LowestHealthEnemy = nullptr;

    for (auto& character : Combatants)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(character);
  
        // if enemy is alive
        if (enemy  && character->GetCurrentHealth() > 0)
        {
            if (LowestHealthEnemy == nullptr || character->GetCurrentHealth() < LowestHealthEnemy->GetCurrentHealth())
            {
                LowestHealthEnemy = character;
            }
        }
    }

    return LowestHealthEnemy;
}
std::shared_ptr<CharacterTemplate> Combat::GetHighestHealthEnemy(std::deque<std::shared_ptr<CharacterTemplate>> Combatants)
{
    std::shared_ptr<CharacterTemplate> HighestHealthEnemy = nullptr;

    for (auto& character : Combatants)
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(character);

        // if enemy is alive
        if (enemy && character->GetCurrentHealth() > 0)
        {
            if (HighestHealthEnemy == nullptr || character->GetCurrentHealth() > HighestHealthEnemy->GetCurrentHealth())
            {
                HighestHealthEnemy = character;
            }
        }
    }

    return HighestHealthEnemy;
}
std::shared_ptr<CharacterTemplate> Combat::GetBossEnemy(std::deque<std::shared_ptr<CharacterTemplate>> Combatants)
{
    for (auto& character : Combatants)
    {
        auto boss = std::dynamic_pointer_cast<BossEnemy>(character);

        if (boss && character->GetCurrentHealth() > 0)
        {
            return character;
        }
    }

    return nullptr;
}
std::shared_ptr<CharacterTemplate> Combat::GetPlayer(std::deque<std::shared_ptr<CharacterTemplate>> Combatants)
{
    for (auto& character : Combatants)
    {
        auto player = std::dynamic_pointer_cast<PlayerCharacter>(character);

        if(player && character->GetCurrentHealth() > 0)
	    {
			return character;
		}
    }

    return nullptr;
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


