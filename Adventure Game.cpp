// A text based adventure/RPG game
// main file for the game

#include "PlayerCharacter.h"
#include "Main.h"
#include "I_Print.h"
#include "MainMenu.h"
#include "Tavern.h"
#include "Item.h"
#include "Location.h"
#include "StatusEffect.h"
#include "Dungeon.h"
#include "Room.h"
#include "GameSetup.h"
#include "Combat.h"
#include "CharacterTemplate.h"

//todays goals:
// 1. create combat system
// 2. integrate turn ststem into features that are time-dependent


   









// Testing functions currently
int main()
{
    /*std::shared_ptr<PlayerCharacter> player = std::make_shared<PlayerCharacter>();
    std::shared_ptr<Enemy> monster1 = std::make_shared<Enemy>("Monster1", 90, 100, 100, 100, 2);
    std::shared_ptr<Enemy> monster2 = std::make_shared<Enemy>("Monster2", 70, 110, 110, 110, 3);
    std::vector<std::shared_ptr<Enemy>> Enemies;

    Enemies.push_back(monster1);
    Enemies.push_back(monster2);

    player->CharacterCreator();


    Combat combat(player, Enemies);
    

    combat.CombatDisplay();
    system("pause");*/

    std::shared_ptr<PlayerCharacter> player = std::make_shared<PlayerCharacter>();
    player->CharacterCreator();
    

    std::shared_ptr<Location> startingLocation = SetupGame(player);

    player->MoveTo(startingLocation);
    
    
   
    
    
    
    
    
    
    
    
    
    
    //PlayerCharacter Player;
    //Tavern TheTavern;*/
    
    //call MainMenu function Test - PASS
    //int Selection = MainMenu(); 
    //
    //switch (Selection)
    //{
    //case 1:
    //{
    //    // reset mode to text for cin/cout 
    //    system("cls");
    //    _setmode(_fileno(stdout), _O_TEXT);
    //    TypeText(L"Starting Character Creation...\n", 20);
    //    system("pause");

    //    Player.CharacterCreator(); // works as intended

    //    system("cls");
    //    std::cout<<"--------START GAME--------" << std::endl;
    //   
    //    Player.MoveTo(TheTavern); // works as intended - includes a pause
    //}
    //break;

    //case 2:
    //    _setmode(_fileno(stdout), _O_TEXT);
    //    std::wcout << "You have selected Load Game" << std::endl;
    //    break;

    //case 3:
    //    _setmode(_fileno(stdout), _O_TEXT);
    //    std::wcout << "You have selected Quit Game" << std::endl;
    //    exit;
    //}

    //std::cout <<"OUTSIDE SWITCH CASE 1 - PLAYER DATA:" << std::endl; // data outside of switch case 1 is still good
    //std::cout << "-------------------------------------------" << std::endl;
    //std::cout << Player << std::endl;
    //std::cout << "-------------------------------------------" << std::endl;

    //return 0;


  




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










//leveling and experience functions test - PASS
//
//
//PlayerCharacter Player(" Xander ", 100, 50, 100, 50, 1, 0, 1000, 2, { {"Strength", 10}, {"Dexterity", 10}, {"Wisdom", 20}, {"Charisma", 10} }, { }, { });
//std::cout << "------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "------------------------------------------" << std::endl;
//
////Player.AddExperience(968500); - level 50
////Player.AddExperience(20023525); - level 100
////Player.AddExperience(2147483647); - level 659 (max int size)
////Player.AddExperience(102036854775806); - Level 142,853 - after this calculation slows down
////Player.AddExperience(202036854775806); - Level 201,015 - after this calculation slows down exponentially
//std::cout << "------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "------------------------------------------" << std::endl;






//testing Location initiation - PASS
//
//std::vector<std::shared_ptr<Location>> allLocations;
//
//std::shared_ptr<Tavern> tavern = std::make_shared<Tavern>("Tavern", "A cozy tavern filled with friendly folks.");
//std::shared_ptr<Dungeon> dungeon = std::make_shared<Dungeon>("Dungeon", "A dark and dreary dungeon.");
//
//
//allLocations.push_back(tavern);
//allLocations.push_back(dungeon);
//
//std::cout << "------------------------------------------" << std::endl;
//std::cout << allLocations [0]->GetName() << std::endl;
//std::cout << allLocations [0]->GetDescription() << std::endl;
//std::cout << "------------------------------------------" << std::endl;
//std::cout << allLocations [1]->GetName() << std::endl;
//std::cout << allLocations [1]->GetDescription() << std::endl;
//std::cout << "------------------------------------------" << std::endl;









// testing game setup - PASS!!!
//
//PlayerCharacter MainCharacter;
//std::shared_ptr<Location> startingLocation = SetupGame();
//
//TypeText(L"Starting a game...\n", 50);
//TypeText(L"...\n", 200);
//TypeText(L"Yes... I said...A...game\n", 50);
//TypeText(L"...\n", 200);
//TypeText(L"...\n", 200);
//TypeText(L"...\n", 200);
//TypeText(L"Seriously...don't expect much...\n", 50);
//TypeText(L"...\n", 200);
//TypeText(L"Anyways...Let's start I guess...\n", 50);
//TypeText(L"------------------------------------------\n", 50);
//system("pause");
//system("cls");
//
//int Selection = MainMenu();
//
//switch (Selection)
//{
//case 1:
//{
//    // reset mode to text for cin/cout 
//    system("cls");
//    _setmode(_fileno(stdout), _O_TEXT);
//    TypeText(L"Starting Character Creation...\n", 20);
//    system("pause");
//
//    Player.CharacterCreator(); // works as intended
//
//    system("cls");
//    std::cout << "--------START GAME--------" << std::endl;
//
//    Player.MoveTo(startingLocation); // works as intended - includes a pause
//}
//break;
//
//case 2:
//    _setmode(_fileno(stdout), _O_TEXT);
//    std::wcout << "You have selected Load Game" << std::endl;
//    break;
//
//case 3:
//    _setmode(_fileno(stdout), _O_TEXT);
//    std::wcout << "You have selected Quit Game" << std::endl;
//    exit;
//}
//
//std::cout << "OUTSIDE SWITCH CASE 1 - PLAYER DATA:" << std::endl; // data outside of switch case 1 is still good
//std::cout << "-------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "-------------------------------------------" << std::endl;
//
//return 0;
   














// item + status effect test - PASS
//
//std::shared_ptr<Item> potion =  std::make_shared<Item> ("Health Potion", "Heals 10 HP and grants temporary strength boost.", 1591 , 50, 1, 0, [&](PlayerCharacter& player) { // need to use make_shared with shared pointers
//    // Heal the player
//    player.heal(25);
//    // Apply the status effect
//    StatusEffect boost = StatusEffect("Boost", "Temporary strength increase.", 123,
//        [&](PlayerCharacter& affectedPlayer) {
//            
//            player.AddStat("Strength", 10);
//        },
//        [&](PlayerCharacter& affectedPlayer) {
//           
//            player.RemoveStat("Strength", 10);
//
//        }, StatusEffect::State::Active);
//
//    player.ApplyEffect(boost);
//
//    StatusEffect haste = StatusEffect("Haste", "Temporary Dexterity increase.", 114,
//        [&](PlayerCharacter& affectedPlayer) {
//
//            player.AddStat("Dexterity", 10);
//        },
//        [&](PlayerCharacter& affectedPlayer) {
//
//            player.RemoveStat("Dexterity", 10);
//
//        }, StatusEffect::State::Active);
//
//    player.ApplyEffect(haste);
//
//    });
//
//Player.TakeDamage(50);
//
//std::cout << "------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "------------------------------------------" << std::endl;
//
//Player.AddItem(potion, 1);
//
//Player.UseItem(potion->GetId());
//
//std::cout << "------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "------------------------------------------" << std::endl;
//
//Player.RemoveEffect("Haste");
//
//std::cout << "------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "------------------------------------------" << std::endl;
//
//
//Player.RemoveEffect("Boost");
//
//std::cout << "------------------------------------------" << std::endl;
//std::cout << Player << std::endl;
//std::cout << "------------------------------------------" << std::endl;














// Combat Display Test
//
//



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
