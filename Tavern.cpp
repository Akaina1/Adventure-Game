// Tavern class will be the main hub of the game. It will be the place where the player can buy items, rest, talk to NPCs,upgrade their equipment, and visit the dungeon.
// Players will start in the tavern after they create their character. They will be able to leave the tavern and go to the dungeon to fight monsters and gain experience.
// The player will be able to return to the tavern at any time to rest and buy items. The player will also be able to upgrade their equipment at the tavern.
// The player will be able to talk to NPCs in the tavern to gain information about the game world and the dungeon.
#include "Tavern.h"


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
    TypeText(L"Welcome to the Tavern!\n", 10);
    TypeText(L"Here you can rest to save your game...\n", 10);
    TypeText(L"Grab a drink from the bar...\n", 10);
    TypeText(L"Talk to various NPCs to purchase items and equipment...\n", 10);
    TypeText(L"And you can venture into the Dungeons as well... If you dare...\n", 10);
    TypeText(L"So what will it be stranger...?\n", 30);

    // print out the name of the location and description
    // do event checks
    
}

void Tavern::OnExit()
{
	std::cout << "Good luck...\n";
    // do event checks
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

    int choice = 0;
    TypeText(L"------------------------------------------\n", 10);
    TypeText(L"1. Rest\n", 10);
    TypeText(L"2. Drink\n", 10);
    TypeText(L"3. Talk to NPCs\n", 10);
    TypeText(L"4. Go to the Dungeon\n", 10);
    TypeText(L"5. Exit the game\n", 10);
    TypeText(L"------------------------------------------\n", 10);

    std::cin >> choice;

	switch (choice)
	{
	case 1:
		//Rest(Player, Player.GetGold());
		break;
	case 2:
		//Drink(Player, Player.GetGold());
		break;
	case 3:
		//ViewNpcs(NPCList);
		break;
	case 4:
		// go to the dungeon
		break;
	case 5:
		// exit the game
		break;
	default:
		break;
	}
}

void Tavern::Rest(PlayerCharacter& Player)
{
	// Rest will restore the player's health and mana to full
	// Rest will also save the game
    // Rest will cost gold
    // do event checks

	int choice = 0;
	int gold = Player.GetPlayerGold(Player);

	TypeText(L"------------------------------------------\n", 10);
	TypeText(L" 'Would you like to rest stranger...?' \n", 10);
	TypeText(L"------------------------------------------\n", 10);
	TypeText(L"1. Yes - 10 Gold\n", 10);
	TypeText(L"2. No\n", 10);

	while (choice != 2)
	{
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			// check if player has enough gold
			// if so, rest
			// if not, print out message

			if (gold >= 10)
			{
				Player.RemoveGold(Player, 10);
				Player.SetHealth(Player, Player.GetMaxHealth(Player));
				Player.SetMana(Player, Player.GetMaxMana(Player));
			}
			else
			{
				TypeText(L"------------------------------------------\n", 10);
				TypeText(L" 'You don't have enough gold stranger...'\n", 10);
				TypeText(L"------------------------------------------\n", 10);
			}
			break;
		case 2:
			// exit the rest menu
			break;
		default:
			break;
		}
	}
}

void Tavern::Drink(PlayerCharacter& Player)
{
	// Drink will allow the player to buy drinks
	// Drinks will restore health and mana
	// Drinks will cost gold
    // do event checks
    int choice = 0;
	int gold = Player.GetPlayerGold(Player);	
	Item ale("Ale", "A pint of ale", 001, 5, 1, 1, ([](PlayerCharacter& player) {player.SetHealth(player, 10);}) );
	Item mead("Mead", "A pint of mead", 002, 10, 1, 1, ([](PlayerCharacter& player) {player.SetHealth(player, 15);}) );
	Item wine("Wine", "A glass of wine", 003, 15, 1, 1, ([](PlayerCharacter& player) {player.SetHealth(player, 20);}) );
	Item water("Water", "A glass of water", 004, 5, 1, 1, ([](PlayerCharacter& player) {player.SetHealth(player, 5);}) );


    TypeText(L"------------------------------------------\n", 10);
    TypeText(L" 'What would you like to drink stranger...?' \n", 10);
    TypeText(L"------------------------------------------\n", 10);
    TypeText(L"1. Ale - 10 Gold\n", 10);
    TypeText(L"2. Mead - 15 Gold\n", 10);
    TypeText(L"3. Wine - 20 Gold\n", 10);
    TypeText(L"4. Water - 5 Gold\n", 10);
    TypeText(L"5. Leave\n", 10);
	

    while (choice != 5)
	{
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			// check if player has enough gold
			// if so, buy ale
			// if not, print out message

			if (gold >= ale.GetPrice())
			{
				Player.RemoveGold(Player, 5);
				Player.AddItem(ale,1,&Player);
			}
			else
			{
				TypeText(L"You don't have enough gold...\n", 10);
			}

			break;
		case 2:
			// buy mead

			if (gold >= mead.GetPrice())
			{
				Player.RemoveGold(Player, 10);
				Player.AddItem(mead, 1, &Player);
			}
			else
			{
				TypeText(L"You don't have enough gold...\n", 10);
			}

			break;
		case 3:
			// buy wine

			if (gold >= wine.GetPrice())
			{
				Player.RemoveGold(Player, 15);
				Player.AddItem(wine, 1, &Player);
			}
			else
			{
				TypeText(L"You don't have enough gold...\n", 10);
			}

			break;
		case 4:
			// buy water

			if (gold >= water.GetPrice())
			{
				Player.RemoveGold(Player, 5);
				Player.AddItem(water, 1, &Player);
			}
			else
			{
				TypeText(L"You don't have enough gold...\n", 10);
			}

			break;
		case 5:
			// leave
			TavernMenu(); // go back to the tavern menu
			break;
		default:
			break;
		}
	}


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
    // do event checks

}