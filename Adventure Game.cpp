// A text based adventure/RPG game
// main file for the game

#include <iostream>
#include "Main.h"
#include "CharacterTemplate.h"
#include "I_Print.h"
#include "MainMenu.h"
#include "PlayerCharacter.h"


int main()
{
    PlayerCharacter Player;
    //call MainMenu function Test
    MainMenu();
    
    //create new player character

    //PlayerCharacter playertest("Frank", 100, 100, 1, 0, 1000, 3, { {"Strength", 10}, {"Dexterity", 10}, {"Wisdom", 10}, {"Charisma", 10} }, { {"Health Potion", 5}, {"Mana Potion", 5} }, { {"Poisoned", false}, {"Bleeding", true}, {"Burned", false} });
    // print player character

   
    //std::cout << playertest << std::endl;

    //playertest.ShowInventory();
   
    

    return 0;
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
