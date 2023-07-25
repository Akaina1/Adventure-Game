// Tavern class will be the main hub of the game. It will be the place where the player can buy items, rest, talk to NPCs,upgrade their equipment, and visit the dungeon.
// Players will start in the tavern after they create their character. They will be able to leave the tavern and go to the dungeon to fight monsters and gain experience.
// The player will be able to return to the tavern at any time to rest and buy items. The player will also be able to upgrade their equipment at the tavern.
// The player will be able to talk to NPCs in the tavern to gain information about the game world and the dungeon.
#include "Tavern.h"
#include "PlayerCharacter.h"
#include "MainMenu.h"
#include "Location.h"
#include "Main.h"

std::string Tavern::GetName() const
{
    return "Tavern";
}

std::string Tavern::GetDescription() const
{
    return "The tavern is a place where you can rest, buy items, and upgrade your equipment.  From here you can venture into the Dungeons as well.";
}

void Tavern::OnEnter()
{
    
	// print out formatted text
    // print out the name of the location and description
    
}

void Tavern::OnExit()
{
	std::cout << "Good luck...\n";
}

void Visit(PlayerCharacter& Player) // Visit function is used to Move the player to the Tavern
{
     // Visit updates player CurrentLocation to Tavern
	 // Visit then calls the OnEnter function which prints the information for the Tavern
     // Visit then calls the TavernMenu function which allows the player to choose what they want to do in the Tavern
}

void Tavern::TavernMenu()
{
    // TavernMenu will print out the options for the player to choose from
    // players can do the following:
    // 1. Rest (should be a prompt to save the game when resting)
    // 2. Drink
    // 3. Talk to NPCs (this will be a sub menu where the player can choose which NPC to talk to)
    // 4. Go to the Dungeon
    // 5. Exit the game
}

void Tavern::Rest(PlayerCharacter& Player, int PlayerGold)
{
	// Rest will restore the player's health and mana to full
	// Rest will also save the game
    // Rest will cost gold
}

void Tavern::Drink(PlayerCharacter& Player, int PlayerGold)
{
	// Drink will allow the player to buy drinks
	// Drinks will restore health and mana
	// Drinks will cost gold
}

void Tavern::ViewNpcs(std::vector<NPC> NPCList)
{
	// TalkToNPCs will print out the NPCs in the tavern
	// TalkToNPCs will allow the player to choose which NPC to talk to
	// TalkToNPCs will call the TalkToNPC function
}

void Tavern::TalkToNpc(NPC& npc)
{
    // TalkToNPC will print out the NPC's name and description
    // TalkToNPC will print out the NPC's dialogue
    // TalkToNPC will print out the NPC's options
    // TalkToNPC will allow the player to choose which option to choose
	// TalkToNPC will call the NPC's function based on the player's choice

}