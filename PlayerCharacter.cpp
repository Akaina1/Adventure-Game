// implementation file for PlayerCharacter class
#include "PlayerCharacter.h"
#include "MainMenu.h"
#include "Location.h"
#include "Tavern.h"
#include "Item.h"

Tavern TestTavern;

// override the print function from the I_Print class

void PlayerCharacter::Print(std::ostream& os) const
{
	std::cout << std::boolalpha;
	os << "Player Character: " << std::endl;
	os << "Location: "<< CurrentLocation << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Name: " << Name << std::endl;
	os << "Level: " << Level << std::endl;
	os << "Class: " << GetPlayerClassName(PlayerClass) << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Health: " << Health << std::endl;
	os << "Mana: " << Mana << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Experience: " << Experience << std::endl;
	os << "Gold: " << Gold << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Stats: " << std::endl;
	for (auto stat : StatValues)
	{
		os << stat.first << ": " << stat.second << std::endl;
	}
	os << "-------------------------------------------" << std::endl;
	os << "Inventory: " << std::endl;
	//need to loop through the map and print the item names and quantities
	for (auto item : Inventory)
	{
		os << item.first << ": " << item.second << std::endl;
	}	
	os << "-------------------------------------------" << std::endl;
	os << "Status Effects: " << std::endl;
	for (auto effect : StatusEffect)
	{
		if (effect.second == true)
		{
			os << effect.first << ": " << effect.second << std::endl;
			break;
		}
		else
		{
			os << "No Status Effects" << std::endl;
			break;
		}
		
	}
}


// default constructor
PlayerCharacter::PlayerCharacter()
	: Name{ "Default" }, Health{ 100 }, Mana{ 100 }, Level{ 1 }, Experience{ 0 }, Gold{ 0 }, PlayerClass{}, StatValues{ {"Strength", 0}, {"Dexterity", 0}, {"Wisdom", 0}, {"Charisma", 0} }, Inventory{}, StatusEffect{}, CurrentLocation { &TestTavern }
{
}

// constructor with parameters
PlayerCharacter::PlayerCharacter(std::string name, int health, int mana, int level, int experience, int gold, int pclass, std::map<std::string, int> statValues, std::map<Item, int> inventory, std::map<std::string, bool> statusEffect)
	: Name{ name }, Health{ health }, Mana{ mana }, Level{ level }, Experience{ experience }, Gold{ gold }, PlayerClass {pclass}, StatValues{statValues}, Inventory{inventory}, StatusEffect{statusEffect}, CurrentLocation { &TestTavern }
{
}

// destructor
PlayerCharacter::~PlayerCharacter()
{
}

// returns the name of the player class
std::string PlayerCharacter::GetPlayerClassName(int PlayerClass) const
{
	switch (PlayerClass)
	{
	case 1:
		return "Brawler";
		break;
	case 2:
		return "Scourge";
		break;
	case 3:
		return "Swindler";
		break;
	case 4:
		return "Jester";
		break;
	}
}

// prints the inventory of the player character
void PlayerCharacter::ShowInventory() const
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Inventory: " << std::endl;
	
	for (auto item : Inventory)
	{
		std::cout << item.first << ": " << item.second << std::endl;
	}
}

Location& PlayerCharacter::GetCurrentLocation(Location& CurrentLocation) const
{
	//return reference to current location
    return CurrentLocation;
}

void PlayerCharacter::MoveTo(Location& CurrentLocation, Location& NewLocation)
{
	//set current location to new location

	CurrentLocation = NewLocation;
}

int PlayerCharacter::GetPlayerGold(PlayerCharacter& Player) const
{
	//get player gold and return the value as an int
	return Player.Gold;
}

void PlayerCharacter::AddGold(PlayerCharacter& Player, int Gold)
{
	//add gold to player
	Player.Gold += Gold;
}

void PlayerCharacter::RemoveGold(PlayerCharacter& Player, int Gold)
{
	Player.Gold -= Gold;
}

void PlayerCharacter::AddItem(PlayerCharacter& Player, Item& item, int quantity)
{
	// add Item object into the inventory map
    Player.Inventory.insert(std::pair<Item, int>(item, quantity));
}

void PlayerCharacter::RemoveItem(PlayerCharacter& Player, Item& item, int quantity)
{
	// remove Item object from the inventory map
	Player.Inventory.erase(item);
}

PlayerCharacter PlayerCharacter::PlayerCreator()
{
	//create new player character
	PlayerCharacter Player;

	int BaseStatPoints = 10;

	std::cin.ignore();
	TypeText(L"Enter your Character's Name: ", 10);
	std::getline(std::cin, Name);
	TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;

	// loop class selection to allow for re-selection

int Selection = 0;
std::map<std::string, int> ClassStatValues { {"Strength", 0}, { "Dexterity", 0 }, { "Wisdom", 0 }, { "Charisma", 0 }};


while (Selection < 1 || Selection > 4)
{
	TypeText(L"Select your Character's Class: ", 10); std::wcout << std::endl;
	TypeText(L"1. Brawler", 10); std::wcout << std::endl;
	TypeText(L"2. Scourge", 10); std::wcout << std::endl;
	TypeText(L"3. Swindler", 10); std::wcout << std::endl;
	TypeText(L"4. Jester", 10); std::wcout << std::endl;
	std::cin >> Selection;

	//std::map<std::string, int> ClassStatValues { {"Strength", 0}, { "Dexterity", 0 }, { "Wisdom", 0 }, { "Charisma", 0 }};

	switch (Selection)
	{
	case 1: //Brawler

		system("cls");

		//print a formated class description using TypeText function
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Brawler", 10); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Health: 500", 10); std::wcout << std::endl;
		TypeText(L"Mana: 30", 10); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Strength: 15", 10); std::wcout << std::endl;
		TypeText(L"Dexterity: 10", 10); std::wcout << std::endl;
		TypeText(L"Wisdom: 10", 10); std::wcout << std::endl;
		TypeText(L"Charisma: 10", 10); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Description: A brawler is a fighter who uses\ntheir fists to fight. They are strong and\ncan take a lot of damage, but they lack\nthe ability to use magic and have a weakness\nto magic.\n", 10); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;

		TypeText(L"Press 1 to confirm class, or 0 to\nselect a different class: ", 10);
		std::cin >> Selection;

		if (Selection == 0)
		{
			Selection = 0;
		}
		else if (Selection == 1)
		{ 
		PlayerClass = 1;
		Health = 500;
		Mana = 30;
		ClassStatValues = { {"Strength", 15}, { "Dexterity", 10 }, { "Wisdom", 10 }, { "Charisma", 10 } };
		continue;
		}

	case 2: //Scourge
		PlayerClass = 2;
		Health = 125;
		Mana = 200;
		ClassStatValues = { {"Strength", 10}, { "Dexterity", 10 }, { "Wisdom", 15 }, { "Charisma", 10 } };
		break;

	case 3://Swindler
		PlayerClass = 3;
		Health = 125;
		Mana = 20;
		ClassStatValues = { {"Strength", 10}, { "Dexterity", 15 }, { "Wisdom", 10 }, { "Charisma", 10 } };
		break;

	case 4://Jester
		PlayerClass = 4;
		Health = 150;
		Mana = 100;
		ClassStatValues = { {"Strength", 10}, { "Dexterity", 10 }, { "Wisdom", 10 }, { "Charisma", 15 } };
		break;
	}
}


	TypeText(L"Allocate your Stat Points: ", 1); std::wcout << std::endl;
	TypeText(L"You have " + std::to_wstring(BaseStatPoints) + L" points remaining.", 1); std::wcout << std::endl;
	int AddPoint;

	while (BaseStatPoints > 0)
	{
		if (BaseStatPoints >= 1)
		{
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Strength: ", 1); std::wcout << std::endl;
			std::cin >> AddPoint;
			if (AddPoint > BaseStatPoints)
			{
				std::cout << "nice try, but you don't have that many points left" << std::endl;
				continue;
			}
			StatValues["Strength"] = (ClassStatValues["Strength"] + AddPoint);
			BaseStatPoints -= AddPoint;
			TypeText(L"You have " + std::to_wstring(BaseStatPoints) + L" points remaining.", 1); std::wcout << std::endl;
		}

		if (BaseStatPoints >= 1)
		{
			TypeText(L"Dexterity: ", 1); std::wcout << std::endl;
			std::cin >> AddPoint;
			if (AddPoint > BaseStatPoints)
			{
				std::cout << "nice try, but you don't have that many points left" << std::endl;
				continue; 
			}
			StatValues["Dexterity"] = (ClassStatValues["Dexterity"] + AddPoint);
			BaseStatPoints -= AddPoint;
			TypeText(L"You have " + std::to_wstring(BaseStatPoints) + L" points remaining.", 1); std::wcout << std::endl;
		}

		if (BaseStatPoints >= 1)
		{
			TypeText(L"Wisdom: ", 1); std::wcout << std::endl;
			std::cin >> AddPoint;
			if (AddPoint > BaseStatPoints)
			{
				std::cout << "nice try, but you don't have that many points left" << std::endl;
				continue;
			}
			StatValues["Wisdom"] = (ClassStatValues["Wisdom"] + AddPoint);
			BaseStatPoints -= AddPoint;
			TypeText(L"You have " + std::to_wstring(BaseStatPoints) + L" points remaining.", 1); std::wcout << std::endl;
		}

		if (BaseStatPoints >= 1)
		{
			TypeText(L"Charisma: ", 1); std::wcout << std::endl;
			std::cin >> AddPoint;
			if (AddPoint > BaseStatPoints)
			{
				std::cout << "nice try, but you don't have that many points left" << std::endl;
				continue;
			}
			StatValues["Charisma"] = (ClassStatValues["Charisma"] + AddPoint);
			BaseStatPoints -= AddPoint;
			TypeText(L"You have " + std::to_wstring(BaseStatPoints) + L" points remaining.", 1); std::wcout << std::endl;
		}
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		if (BaseStatPoints == 0)

		{
			TypeText(L"You have no points remaining.", 10); std::wcout << std::endl;
		}
	}

    Inventory = { {"Health Potion", 5}, { "Mana Potion", 5 } };

	StatusEffect = 
	{ {"Poisoned", false}, { "Bleeding", false }, { "Burned", false }, { "Frozen", false }, { "Stunned", false }, 
	{ "Blinded", false }, { "Confused", false }, { "Charmed", false }, { "Enraged", false }, { "Blessed", false }, 
	{ "Cursed", false }, { "Invisible", false }, { "Silenced", false }, { "Sleeping", false }, { " ", false } };

	// show confirmation of character creation
	std::wcout << "Press Enter to start the game..." << std::endl;
	std::wcin.ignore();
	std::wcin.get();
	
	// return the newly created player character  
	return Player;
}