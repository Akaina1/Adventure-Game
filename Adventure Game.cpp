// A text based adventure/RPG game
// main file for the game
#include "CharacterTemplate.h"
#include "PlayerCharacter.h"
#include "Main.h"
#include "I_Print.h"
#include "MainMenu.h"
#include "Tavern.h"
#include "Item.h"
#include "Location.h"
// goals for today:

// 2. expand on the Room class 
// 3. begin working on Dungeon class
// 4. include experience system for player character







// Testing functions currently
int main()
{
    PlayerCharacter Player;
    Tavern TheTavern;
    
    //call MainMenu function Test - PASS
    int Selection = MainMenu(); 
    
    switch (Selection)
    {
    case 1:
    {
        // reset mode to text for cin/cout 
        system("cls");
        _setmode(_fileno(stdout), _O_TEXT);
        TypeText(L"Starting Character Creation...\n", 20);
        system("pause");

        Player.CharacterCreator(); // works as intended

        system("cls");
        std::cout<<"--------START GAME--------" << std::endl;
       
        Player.MoveTo(TheTavern); // works as intended - includes a pause
    }
    break;

    case 2:
        _setmode(_fileno(stdout), _O_TEXT);
        std::wcout << "You have selected Load Game" << std::endl;
        break;

    case 3:
        _setmode(_fileno(stdout), _O_TEXT);
        std::wcout << "You have selected Quit Game" << std::endl;
        exit;
    }

    std::cout <<"OUTSIDE SWITCH CASE 1 - PLAYER DATA:" << std::endl; // data outside of switch case 1 is still good
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << Player << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    return 0;


  




    //player character & effects test - PASS
    //
    ///PlayerCharacter player("Player", 120, 100, 1, 0, 1000, 0, { {"Strength", 0}, {"Dexterity", 0}, {"Wisdom", 0}, {"Charisma", 0} }, {});
    //Item HealthPotion("Health Potion", "A potion that increases your health by 10", 002, 10, 1, 0, ([](PlayerCharacter& player) {player.SetHealth(player, 10); }) );
    //HealthPotion.Print(HealthPotion);
    //HealthPotion.UseItem(&player, HealthPotion); 
    //std::cout << player << std::endl;







    //player inventory test - PASS
    //
    /*Item HealthPotion("Health Potion", "A potion that increases your health by 10", 002, 10, 1, 0, ([](PlayerCharacter& player) {player.SetHealth(player, 10); }));
    PlayerCharacter player("Slayer", 200, 100, 1, 0, 1000, 2, { {"Strength", 0}, {"Dexterity", 0}, {"Wisdom", 0}, {"Charisma", 0} }, { { HealthPotion,5 } }, {});
    std::cout << player << std::endl;*/











    //Tavern Test - PASS
    //
    // create a player character that has 50/100 health
   /* PlayerCharacter Player(" Xander ", 100, 50, 100, 50, 1, 0, 1000, 2, { {"Strength", 10}, {"Dexterity", 10}, {"Wisdom", 20}, {"Charisma", 10} }, { }, { });
    Tavern tavern;
    std::cout << Player << std::endl;
    tavern.OnEnter(&Player);
    std::cout << Player << std::endl;*/















    //StatusEffect test - PASS
    //
    //create a status effect that increases the players max health by 50 with a default state set to inactive
 //   StatusEffect MaxHealthUp (
 //       "Full Belly", 
 //       "You ate a good meal and gained 50 max health temporarily", 
 //       001, 
 //       [](PlayerCharacter& player) {player.IncreaseMaxHealth(50, &player); }, 
 //       [](PlayerCharacter& player) {player.DecreaseMaxHealth(50, &player); }, 
 //       StatusEffect::State::Inactive 
 //   );
 //   //create a status effect that increases the players max mana by 50 with a default state set to inactive
 //   StatusEffect MaxManaUp(
	//	"Mana Drop",
	//	"Tastes like a gumdrop... yum",
	//	002,
	//	[](PlayerCharacter& player) {player.IncreaseMaxMana(50, &player); },
	//	[](PlayerCharacter& player) {player.DecreaseMaxMana(50, &player); },
	//	StatusEffect::State::Inactive
	//);
 //   PlayerCharacter Player(" Xander ", 100, 50, 100, 50, 1, 0, 1000, 2, { {"Strength", 10}, {"Dexterity", 10}, {"Wisdom", 20}, {"Charisma", 10} }, { }, { } );
 //   std::cout << "------------------------------------------" << std::endl;
 //   std::cout << Player << std::endl;
 //   std::cout << "------------------------------------------" << std::endl;
 //   //call the status effect function to activate the effect
 //   Player.UpdateEffects(MaxHealthUp, &Player);
 //   std::cout << "------------------------------------------" << std::endl;
 //   std::cout << Player << std::endl;
 //   std::cout << "------------------------------------------" << std::endl;
 //   //call the status effect function to add another effect
 //   Player.UpdateEffects(MaxManaUp, &Player);
 //   std::cout << "------------------------------------------" << std::endl;
 //   std::cout << Player << std::endl;
 //   std::cout << "------------------------------------------" << std::endl;
 //   //call the status effect function to remove the effect
 //   Player.UpdateEffects(MaxHealthUp, &Player);
 //   Player.UpdateEffects(MaxManaUp, &Player);
 //   std::cout << "------------------------------------------" << std::endl;
 //   std::cout << Player << std::endl;
 //   std::cout << "------------------------------------------" << std::endl;














// test new character creator function - PASS
//
//
//PlayerCharacter player;
//
//player.CharacterCreator();
//
//std::cout << "------------------------------------------" << std::endl;
//std::cout << player << std::endl;
//std::cout << "------------------------------------------" << std::endl;
//
//return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
