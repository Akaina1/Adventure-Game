// Tavern class will be the main hub of the game. It will be the place where the player can buy items, rest, talk to NPCs,upgrade their equipment, and visit the dungeon.
// Players will start in the tavern after they create their character. They will be able to leave the tavern and go to the dungeon to fight monsters and gain experience.
// The player will be able to return to the tavern at any time to rest and buy items. The player will also be able to upgrade their equipment at the tavern.
// The player will be able to talk to NPCs in the tavern to gain information about the game world and the dungeon.
#include "Tavern.h"
#include "GameManager.h"

void Tavern::OnEnter(std::shared_ptr<PlayerCharacter> Player) //called when the player enters the Tavern (overloaded for each location)
{
    //1. event check
	// to implement later
	//2. print out intro text
	TypeText(L"Welcome to the Tavern!\n", 5);
	TypeText(L"+-----------------------------------------+\n", 5);
	TypeText(L"Here you can rest to save your game...\n\n", 5);
	TypeText(L"Grab a drink from the bar...\n\n", 5);
	TypeText(L"Talk to various NPCs to purchase items\nand equipment...\n\n", 5);
	TypeText(L"If you have a death wish you can\nventure into the Dungeon as well\n\n...If you dare...\n", 5);
	//3. print out menu
	TavernMenu();
}

void Tavern::OnExit(std::shared_ptr<PlayerCharacter> Player) //called when the player exits the Tavern (overloaded for each location)
{
	//1. do event checks
	// to implement later
	//2. print out exit text
	std::cout << "Good luck...\n"; 
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
    TypeText(L"+-----------------------------------------+\n", 10);
    TypeText(L"1. Rest\n", 10);
    TypeText(L"2. Drink\n", 10);
    TypeText(L"3. Talk to NPCs\n", 10);
    TypeText(L"4. Go to the Dungeon\n", 10);
	TypeText(L"5. Check Inventory\n", 10);
    TypeText(L"6. Exit the game\n", 10);
    TypeText(L"+-----------------------------------------+\n", 10);

    std::cin >> choice;
	system("cls");

	switch (choice)
	{
	case 1:
		
		this->Rest();

		break;
	case 2:
		
		this->Drink();

		break;
	case 3:
		//ViewNpcs(NPCList);
		break;
	case 4:
		// //move to dungeon
		Player->ChooseMove();

		break;
	case 5:
		// check inventory
		Player->CheckInventory();
		break;
	case 6:
		// exit the game
		break;
	default:
		break;
	}
}

void Tavern::Rest()
{
	// Rest will restore the player's health and mana to full
	// Rest will also save the game
    // Rest will cost gold
    // do event checks

	int choice = 0;
	int gold = Player->GetPlayerGold();

	system("cls");
	TypeText(L"------------------------------------------\n", 10);
	TypeText(L" 'Would you like to rest stranger...?' \n", 10);
	TypeText(L"------------------------------------------\n", 10);
	TypeText(L"1. Yes - 10 Gold\n", 10);
	TypeText(L"2. No\n", 10);

	while (choice != 2)
	{
		int Selection = 0;
		std::cin >> Selection;

		switch (Selection)
		{
		case 1:
			// check if player has enough gold
			// if so, rest
			// if not, print out message

			if (gold >= 10)
			{
				Player->RemoveGold(10);
				Player->heal(Player->GetMaxHealth()); // heal player to full health
				Player->RestoreMana(Player->GetMaxMana()); // restore player's mana to full
				choice = 2;
				std::cout << "YOU HAVE RESTED\n";
				system("pause");
				system("cls");
				TavernMenu();
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
			system("cls");
			TavernMenu();
			break;
		default:
			break;
		}
	}
}

void Tavern::Drink()
{
	// Drink will allow the player to buy drinks
	// Drinks will restore health and mana
	// Drinks will cost gold
    // do event checks
    int choice = 0;
	int gold = Player->GetPlayerGold();	
	std::shared_ptr<Item> Ale = std::make_shared<Item>("Ale", "A pint of ale", 1001, 5, ItemType::CONSUMABLE, [](std::shared_ptr<PlayerCharacter> player) {player->heal(10); });
	std::shared_ptr<Item> Mead = std::make_shared<Item>("Mead", "A pint of mead", 1002, 10, ItemType::CONSUMABLE, [](std::shared_ptr<PlayerCharacter> player) {player->heal(15); });
	std::shared_ptr<Item> Wine = std::make_shared<Item>("Wine", "A glass of wine", 1003, 15, ItemType::CONSUMABLE, [](std::shared_ptr<PlayerCharacter> player) {player->heal(20); });
	std::shared_ptr<Item> Water = std::make_shared<Item>("Water", "A glass of water", 1004, 5, ItemType::CONSUMABLE, [](std::shared_ptr<PlayerCharacter> player) {player->heal(5); });
	

	if (Ale->GetEffect())
	{
		std::cout << "Ale has an effect!" << std::endl;
	}
	
	if (Mead->GetEffect())
	{
		std::cout << "Mead has an effect!" << std::endl;
	}

if (Wine->GetEffect())
	{
		std::cout << "Wine has an effect!" << std::endl;
	}

if (Water->GetEffect())
	{
		std::cout << "Water has an effect!" << std::endl;
	}


	system("pause");

	system("cls");
    TypeText(L"+-----------------------------------------+\n", 10);
    TypeText(L" 'What would you like to drink stranger...?'\n", 10);
    TypeText(L"+-----------------------------------------+\n", 10);
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

			if (gold >= Ale->GetPrice())
			{
				Player->RemoveGold(5);
				Player->AddItem(Ale,1);

				std::cout << "YOU BOUGHT ALE\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}
			else
			{
				TypeText(L"You don't have enough gold...\n", 10);
			}

			break;
		case 2:
			// buy mead

			if (gold >= Mead->GetPrice())
			{
				Player->RemoveGold(10);
				Player->AddItem(Mead, 1);

				std::cout << "YOU BOUGHT MEAD\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}
			else
			{
				std::cout << "You don't have enough Gold...\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}

			break;
		case 3:
			// buy wine

			if (gold >= Wine->GetPrice())
			{
				Player->RemoveGold(15);
				Player->AddItem(Wine, 1);

				std::cout << "YOU BOUGHT WINE\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}
			else
			{
				std::cout << "You don't have enough Gold...\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}

			break;
		case 4:
			// buy water

			if (gold >= Water->GetPrice())
			{
				Player->RemoveGold(5);
				Player->AddItem(Water, 1);

				std::cout << "YOU BOUGHT WATER\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}
			else
			{
				std::cout << "You don't have enough Gold...\n";
				std::cout << "Gold: " << Player->GetPlayerGold() << std::endl;
			}

			break;
		case 5:
			// leave
			system("cls");
			TavernMenu(); // go back to the tavern menu
			break;
		default:
			break;
		}
	}
}

//void Tavern::ViewNpcs(std::vector<NPC> NPCList)
//{
//	// TalkToNPCs will print out the NPCs in the tavern
//	// TalkToNPCs will allow the player to choose which NPC to talk to
//	// TalkToNPCs will call the TalkToNPC function
//}
//
//void Tavern::TalkToNpc(NPC& npc)
//{
//    // TalkToNPC will print out the NPC's name and description
//    // TalkToNPC will print out the NPC's dialogue
//    // TalkToNPC will print out the NPC's options
//    // TalkToNPC will allow the player to choose which option to choose
//	// TalkToNPC will call the NPC's function based on the player's choice
//    // do event checks
//
//}

std::shared_ptr<Room> Tavern::GetConnectedRoom(int index) const
{
	if (index < 0 || index >= connectedRooms.size())
	{
		throw std::out_of_range("ERROR - Room::GetConnectedRoom() - INDEX IS OUT OF RANGE");
	}

	return connectedRooms[index];
}

std::shared_ptr<Location> Tavern::GetConnectedLocation(int index) const
{
	if (index < 0 || index >= connectedLocations.size())
	{
		throw std::out_of_range("ERROR - Room::GetConnectedLocation() - INDEX IS OUT OF RANGE");
	}

	return connectedLocations[index];
}