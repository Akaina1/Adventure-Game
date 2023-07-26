// A text based adventure/RPG game
// main file for the game

#include <iostream>
#include "CharacterTemplate.h"
#include "PlayerCharacter.h"
#include "Main.h"
#include "I_Print.h"
#include "MainMenu.h"
#include "Tavern.h"
#include "Event.h"
#include "NPC.h"
#include "Room.h"
#include "Item.h"


int main()
{
  
    //call MainMenu function Test
 
    //MainMenu(); 

    //return 0;

    PlayerCharacter player("Player", 120, 100, 1, 0, 1000, 0, { {"Strength", 0}, {"Dexterity", 0}, {"Wisdom", 0}, {"Charisma", 0} }, {});

    Item HealthPotion("Health Potion", "A potion that increases your health by 10", 002, 10, 1, 0, ([](PlayerCharacter& player) {player.SetHealth(player, 10); }) );

    HealthPotion.Print(HealthPotion);

    //HealthPotion.AddEffect([](PlayerCharacter &player) {player.SetHealth(player, 10); });

    HealthPotion.UseItem(&player, HealthPotion); 

    std::cout << player << std::endl;
    

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
