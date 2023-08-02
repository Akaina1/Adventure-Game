// implementation file for PlayerCharacter class
#define NOMINMAX
#include "PlayerCharacter.h"
#include "Item.h"
#include "NPC.h"
#include "Enemy.h"
#include "GameSetup.h"
#include "AttackType.h"
#include "Skill.h"

////////////////////////////////// Default functions //////////////////////////////////

PlayerCharacter::PlayerCharacter() // default constructor
{
}

PlayerCharacter::~PlayerCharacter() // destructor
{
}

// constructor with parameters
PlayerCharacter::PlayerCharacter(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level, int speed, int attackPwr, int defensePwr,
	bool isDefending,long long experience, int gold, int playerClass, std::map<std::string, 
	int> statValues, AttackType baseAttackType, std::vector<Skill> skills, std::unordered_map<int, 
	std::pair<std::shared_ptr<Item>, int>> inventory, std::vector<EffectPtr> afflictions) :
	CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, speed, attackPwr, 
	defensePwr,	isDefending, statValues, baseAttackType, skills, afflictions), Experience(experience), 
	Gold(gold), PlayerClass(playerClass), Inventory(inventory)
{}

void PlayerCharacter::Print(std::ostream& os) const     // override the print function from the I_Print class

{
	std::cout << std::boolalpha;
	os << "Player Character: " << std::endl;
	//os << "Location: "<< CurrentLocation << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Name: " << Name << std::endl;
	os << "Level: " << Level << std::endl;
	os << "Class: " << GetPlayerClassName() << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Health: " << CurrentHealth << "/" << MaxHealth << std::endl;
	os << "Mana: " << CurrentMana << "/" << MaxMana << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Experience: " << Experience << "/" << ExpToNextLevel() << std::endl;
	os << "Gold: " << Gold << std::endl;
	os << "-------------------------------------------" << std::endl;
	os << "Stats: " << std::endl;
	os << "Speed: " << GetSpeed() << std::endl;
	for (auto stat : StatValues)
	{
		os << stat.first << ": " << stat.second << std::endl;
	}
	os << "-------------------------------------------" << std::endl;
	os << "Inventory: " << std::endl;
	//print inventory
	for (const auto item : Inventory)
	{
		os << item.second.first->GetName() << ": " << item.second.second << std::endl;
	}
	os << "-------------------------------------------" << std::endl;
	os << "Status Effects: " << std::endl;
	for (auto& effect : Afflictions)
	{
		os << effect->GetName() << ": " << effect->GetDuration() << " turns left" << std::endl;
	}
}


////////////////////////////////// Location functions //////////////////////////////////

void PlayerCharacter::MoveTo(std::shared_ptr<Location> newlocation)
{
	std::shared_ptr<Location> currentLocation = this->GetCurrentLocation();		

	if (CurrentLocation)
	{
		CurrentLocation->OnExit(Self.lock());
	}

	this->SetCurrentLocation(newlocation);
	system("cls");
	std::cout << "You are now moving to... " << newlocation->GetName() << std::endl;
	std::cout << "-------------------------------------------\n" << std::endl;
	std::cout << LoadingText() << std::endl;
	std::cout << "-------------------------------------------\n" << std::endl;
	system("pause");
	system("cls");

	if (newlocation)
	{
		newlocation->OnEnter(Self.lock());
	}
	
	
}

void PlayerCharacter::ChooseMove()
{
	std::shared_ptr<Location> currentLocation = GetCurrentLocation();
	std::cout << "You are currently in " << currentLocation->GetName() << std::endl;
	std::cout << "-------------------------------------------\n" << std::endl;


	if (currentLocation->GetConnectedRoomsCount() == 0 && currentLocation->GetConnectedLocationsCount() > 0)
	{
		std::cout << "There are no Rooms connected to this location.\n";
	}
	else if (currentLocation->GetConnectedLocationsCount() == 0 && currentLocation->GetConnectedRoomsCount() > 0)
	{
		std::cout << "There are no Locations connected to this location.\n";
	}
	else if (currentLocation->GetConnectedRoomsCount() == 0 && currentLocation->GetConnectedLocationsCount() == 0)
	{
		std::cout << "There are no Rooms or Locations connected to this location.\n";
		return;
	}
	std::cout << "-------------------------------------------\n" << std::endl;
	std::cout << "You can move to the following Locations: \n";
	std::cout << "-------------------------------------------\n" << std::endl;
	int count = 0;
	for (int i = 0; i < currentLocation->GetConnectedLocationsCount(); i++)
	{
		std::shared_ptr<Location> connectedLocation = currentLocation->GetConnectedLocation(i);
		std::cout << ++count << ": " << connectedLocation->GetName() << "\n";
	}

	std::cout << "-------------------------------------------\n" << std::endl;
	std::cout << "You can move to the following Rooms: \n";
	std::cout << "-------------------------------------------\n" << std::endl;
	for (int i = 0; i < currentLocation->GetConnectedRoomsCount(); i++)
	{
		std::shared_ptr<Room> connectedLocation = currentLocation->GetConnectedRoom(i);
		std::cout << ++count << ": " << connectedLocation->GetName() << "\n";
	}

	std::cout << "-------------------------------------------\n" << std::endl;
	std::cout << "Enter the number of the Location or Room you want to move to: \n";
	std::cout << "-------------------------------------------\n" << std::endl;
	int choice;
	std::cin >> choice;
	choice--;


	if(choice < currentLocation->GetConnectedLocationsCount())
	{
		// Move to the chosen location
		MoveTo((currentLocation->GetConnectedLocation(choice)));
	}
	else
	{
		// Adjust the choice index to account for locations, then move to the chosen room
		choice -= currentLocation->GetConnectedLocationsCount();
		MoveTo((currentLocation->GetConnectedRoom(choice)));
	}
}

////////////////////////////////// Class functions    //////////////////////////////////

std::string PlayerCharacter::GetPlayerClassName() const // returns the name of the player class
{
	int Class = PlayerClass;

	if (Class == 1)
	{
		return "Brawler";
	}
	else if (Class == 2)
	{
		return "Scourge";
	}
	else if (Class == 3)
	{
		return "Swindler";
	}
	else if (Class == 4)
	{
		return "Jester";
	}
	else
	{
		return "Invalid Class - GetPlayerClassName() FUNCTION";
	}
}

////////////////////////////////// Experience functions ////////////////////////////////

void PlayerCharacter::LevelUp() // increases the level of the player character
{
	long long nextLevelExp = ExpToNextLevel();

	while (Experience >= ExpToNextLevel())
	{	// increase the stats of the player character dependant on their class
		// each level up will increase the 4 stats by 1 plus an extra 1 point for the classes main stat as follows:
		// Brawler - strength
		// Scourge - wisdom
		// Swindler - Dexterity
		// Jester - Charisma

		Experience -= nextLevelExp;

		Level++;
		
		if (PlayerClass == 1) // Brawler
		{
			StatValues["Strength"] += 2;
			StatValues["Dexterity"] += 1;
			StatValues["Wisdom"] += 1;
			StatValues["Charisma"] += 1;
			this->IncreaseMaxHealth(5);
			this->IncreaseMaxMana(2);
		}
		else if (PlayerClass == 2) // Scourge
		{
			StatValues["Strength"] += 1;
			StatValues["Dexterity"] += 1;
			StatValues["Wisdom"] += 2;
			StatValues["Charisma"] += 1;
			this->IncreaseMaxHealth(3);
			this->IncreaseMaxMana(5);
		}
		else if (PlayerClass == 3) // Swindler
		{
			StatValues["Strength"] += 1;
			StatValues["Dexterity"] += 2;
			StatValues["Wisdom"] += 1;
			StatValues["Charisma"] += 1;
			this->IncreaseMaxHealth(4);
			this->IncreaseMaxMana(2);
		}
		else if (PlayerClass == 4) // Jester
		{
			StatValues["Strength"] += 1;
			StatValues["Dexterity"] += 1;
			StatValues["Wisdom"] += 1;
			StatValues["Charisma"] += 2;
			this->IncreaseMaxHealth(3);
			this->IncreaseMaxMana(4);
		}
		else
		{
			std::cout << "Invalid Class - LEVEL UP FUNCTION" << std::endl;
		}

		nextLevelExp = ExpToNextLevel();
	}
	// heal the player character to full health and mana
	CurrentHealth = MaxHealth;
	CurrentMana = MaxMana;
	SetSpeed(GetSpeed() + 1); // increase the speed of the player character by 1
	IncreaseLevel(); // increase the level of the player character by 1

	// display the level up message
	std::cout << "+----------------------------------------+" << std::endl;
	std::cout << "You have leveled up!" << std::endl;
	std::cout << "You are now level " << Level << "!" << std::endl;
	std::cout << "+----------------------------------------+" << std::endl;
}

long long PlayerCharacter::ExpToNextLevel() const
{
	int nextlevel = Level + 1;
	long long expneeded = 0;

	if (Level <= 10)
	{
		expneeded = 100 * nextlevel;
	}
	else if (Level <= 20)
	{
		expneeded = 200 * nextlevel;
	}
	else if (Level <= 30)
	{
		expneeded = 400 * nextlevel;
	}
	else if (Level <= 40)
	{
		expneeded = 800 * nextlevel;
	}
	else if (Level <= 50)
	{
		expneeded = 1200 * nextlevel;
	}
	else if (Level <= 60)
	{
		expneeded = 1800 * nextlevel;
	}
	else if (Level <= 70)
	{
		expneeded = 2700 * nextlevel;
	}
	else if (Level <= 80)
	{
		expneeded = 4050 * nextlevel;
	}
	else if (Level <= 90)
	{
		expneeded = 6075 * nextlevel;
	}
	else if (Level <= 100)
	{
		expneeded = 9100 * nextlevel;
	}
	else if (Level > 100)
	{
		expneeded = 10000 * nextlevel;
	}
	else 
	{
		std::cout << "Invalid Level - ExpToNextLevel() FUNCTION" << std::endl;
	}

	return expneeded;
}

void PlayerCharacter::AddExperience(long long exp) 
{ 
	Experience += exp; 
	LevelUp();
}

////////////////////////////////// Inventory functions /////////////////////////////////

void PlayerCharacter::AddItem(std::shared_ptr<Item> item, int quantity) // adds an item to the player character's inventory
{
	int id = item->GetId();

	if (Inventory.count(id) > 0)
	{
		Inventory[id].second += quantity;
	}
	else
	{
		Inventory[id] = std::make_pair(item, quantity);
	}
}

void PlayerCharacter::RemoveItem(std::shared_ptr<Item> item, int quantity) // removes an item from the player character's inventory
{
	auto it = Inventory.find(item->GetId());
	if (it != Inventory.end())
	{
		it->second.second -= quantity;
		if (it->second.second <= 0)
		{
			Inventory.erase(it);
		}
	}
	else
	{
		std::cout << "Item not found in inventory.\n";
	}
}

int PlayerCharacter::GetItemQuantity(std::shared_ptr<Item> item) // returns the quantity of an item in the player character's inventory
{
	auto it = Inventory.find(item->GetId());
	if (it != Inventory.end())
	{
		return it->second.second;
	}
	else
	{
		std::cout << "Item not found in inventory.\n";
		return 0;
	}
}

void PlayerCharacter::PrintInventory()  // prints the inventory of the player character
{
	for (auto& pair : Inventory)
	{
		std::cout << pair.second.first->GetName() << ": " << pair.second.second << std::endl;
	}

}

void PlayerCharacter::UseItem(int itemId)
{
	if (Inventory.count(itemId) > 0 && Inventory[itemId].second > 0)
	{
		auto& item = Inventory[itemId].first;
		switch (item->GetType())
		{
		case 0:// Consumable

			item->GetEffect()(*this);
			Inventory[itemId].second--;  // decrease quantity by 1
			if (Inventory[itemId].second == 0) {
				Inventory.erase(itemId);  // remove from inventory if quantity is 0
			}
			break;

		case 1:// Weapon
			break;
		case 2:// Armor
			break;
		}
	}
}

////////////////////////////////// Other functions    //////////////////////////////////

void PlayerCharacter::CharacterCreator()
{

	std::wstring date = L"{202";
	
	//1. get user input for character name
	system("cls");
	std::cin.ignore();
	std::string inputname;
	TypeText(L"Enter your character's name: ", 10); std::wcout << std::endl;
	TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
	std::getline(std::cin, inputname);
	this->SetName(inputname);
	TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
	TypeText(L"Qrelation.Engine->Access.User_Data = ", 10); std::cout << inputname << std::endl;
	Sleep(1000); // wait 1 second
	TypeText(L"Qrelation.Engine [ERROR] =\n"
		      "[Qrelation.Detect_Deception]\n\n", 10);
	Sleep(1000); // wait 1 second
	TypeText(L"Qrelation.Engine->Access.User_Data =\n"
		      "[USER NAME DOES NOT MATCH HISTORY RECORD]\n\n", 10);
	TypeText(L"Qrelation.Engine->Confirm.User_Existance...\n", 10);
	TypeText(L"Please wait...\n", 10);
	TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
	Sleep(1000); // wait 1 second

	system("pause");

	PrintNumbers();
	TypeText(L"Qrelation.Engine->Access.User_Data\n"
		      "User.Data[Death_Record] == {True}\n", 10);
	TypeText(L"Return: \n"
		      "Access.User[Death_Record] == {True}...\n\n", 10);
	TypeText(L"Qrelation.Analyze...\n", 10);
	TypeText(L"Death_Record[Date, Cause]\n", 10);
	TypeText(L"Death_Record->Get_Date = ", 10); 
	TypeText(date, 10);
	Sleep(5000); // wait 3 seconds
	EraseStringFromConsole(date,10);
	TypeText(L"\n[FATAL ERROR = Qrelation.Conceal_Future]\n\n", 10);
	Sleep(500);
	TypeText(L"Death_Record->Get_Cause = \n", 10);
	Sleep(1000); // wait 1 second
	TypeText(L"[FATAL ERROR = Qrelation.Conceal_Future]\n\n", 10);
	Sleep(1000); // wait 1 second
	TypeText(L"...\n", 50);
	Sleep(1000); // wait 1 second
	TypeText(L"Name Confirmed!\n", 10);
	TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
	system("pause");



	//2. Ask user to select a class
	int ChosenClass;
	bool confirmed = false;

	do 
	{
		int choice;
		system("cls");
		TypeText(L"Welcome ", 1); std::cout << inputname << std::endl;
		TypeText(L"Choose your class: ", 1); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"[1] Warrior", 1); std::wcout << std::endl;
		TypeText(L"[2] Mage", 1); std::wcout << std::endl;
		TypeText(L"[3] Archer", 1); std::wcout << std::endl;
		TypeText(L"[4] Cleric", 1); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		std::cin >> choice;
		std::cin.ignore();


		
		std::string Confirm;

		switch (choice)
		{
		case 1:
			
			BrawlerPrint();	

			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;
		case 2:
			
			ScourgePrint();
			
			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;
		case 3:
			
			SwindlerPrint();
			
			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;
		case 4:
			
			JesterPrint();
			
			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;
		}

		ChosenClass = choice;

		// set player stats according to the class they chose
		if (ChosenClass == 1)
		{
			PlayerClass = 1;
			MaxHealth = 150;
			MaxMana = 50;
			CurrentHealth = MaxHealth;
			CurrentMana = MaxMana;
			StatValues = { {"Strength",15},{"Dexterity",10},{"Wisdom",5},{"Charisma",10} };
			Level = 1;
			Experience = 0;
			Gold = 1000;
		}
		else if (ChosenClass == 2)
		{
			PlayerClass = 2;
			MaxHealth = 100;
			MaxMana = 150;
			CurrentHealth = MaxHealth;
			CurrentMana = MaxMana;
			StatValues = { {"Strength",5},{"Dexterity",10},{"Wisdom",15},{"Charisma",10} };
			Level = 1;
			Experience = 0;
			Gold = 1000;
		}
		else if (ChosenClass == 3)
		{
			PlayerClass = 3;
			MaxHealth = 125;
			MaxMana = 75;
			CurrentHealth = MaxHealth;
			CurrentMana = MaxMana;
			StatValues = { {"Strength",10},{"Dexterity",15},{"Wisdom",5},{"Charisma",10} };
			Level = 1;
			Experience = 0;
			Gold = 1000;
		}
		else if (ChosenClass == 4)
		{
			PlayerClass = 4;
			MaxHealth = 100;
			MaxMana = 100;
			CurrentHealth = MaxHealth;
			CurrentMana = MaxMana;
			StatValues = { {"Strength",5},{"Dexterity",10},{"Wisdom",10},{"Charisma",15} };
			Level = 1;
			Experience = 0;
			Gold = 1000;
		}
		system("cls");

		//allocate 10 stat points

		int StatPoints = 10;

		while (StatPoints > 0)
		{
			TypeText(L"Points to spend: ", 0); std::wcout << StatPoints << std::endl;
			TypeText(L"Choose a stat to increase: ", 0); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 0); std::wcout << std::endl;
			TypeText(L"Current Stats: ", 0); std::wcout << std::endl;
			TypeText(L"[1] Strength: ", 0); std::wcout << StatValues["Strength"] << std::endl;
			TypeText(L"[2] Dexterity: ", 0); std::wcout << StatValues["Dexterity"] << std::endl;
			TypeText(L"[3] Wisdom: ", 0); std::wcout << StatValues["Wisdom"] << std::endl;
			TypeText(L"[4] Charisma: ", 0); std::wcout << StatValues["Charisma"] << std::endl;
			TypeText(L"-------------------------------------------", 0); std::wcout << std::endl;
			int ChosenStat;
			std::cin >> ChosenStat;
			system("cls");

			switch (ChosenStat)
			{
			case 1:
				StatValues["Strength"] += 1;
				StatPoints -= 1;
				continue;

			case 2:
				StatValues["Dexterity"] += 1;
				StatPoints -= 1;
				continue;

			case 3:
				StatValues["Wisdom"] += 1;
				StatPoints -= 1;
				continue;

			case 4:
				StatValues["Charisma"] += 1;
				StatPoints -= 1;
				continue;
			}
		} 
		

		// give starting inventory based on class

		//if (PlayerClass == 1)
		//{
		//	// need to create actual items to give to player
		//	// then insert them into the inventory
		//}
		//else if (PlayerClass == 2)
		//{
		//	
		//}
		//else if (PlayerClass == 3)
		//{
		//	
		//}
		//else if (PlayerClass == 4)
		//{
		//	
		//}

		// print out player sheet for confirmation

		system("cls");
		TypeText(L"Character Sheet: ", 1); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Name: ", 1); std::cout << Name << std::endl;
		TypeText(L"Class: ", 1); std::cout << GetPlayerClassName() << std::endl;
		TypeText(L"Level: ", 1); std::cout << Level << std::endl;
		TypeText(L"Experience: ", 1); std::cout << Experience << std::endl;
		TypeText(L"Gold: ", 1); std::cout << Gold << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Strength: ", 1); std::wcout << StatValues["Strength"] << std::endl;
		TypeText(L"Dexterity: ", 1); std::wcout << StatValues["Dexterity"] << std::endl;
		TypeText(L"Wisdom: ", 1); std::wcout << StatValues["Wisdom"] << std::endl;
		TypeText(L"Charisma: ", 1); std::wcout << StatValues["Charisma"] << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;

		system("pause");
		system("cls");
	}while (!confirmed);
}

void PlayerCharacter::BrawlerPrint()
{
	std::wstring Brawler
	{
		L"You are a Fighter...\n\n" // 44 characters [ch. 50]
		 "You fought for your king, and you fought for\n"
		 "your country.  You fought for your family,\n"
		 "and you fought for your friends...\n\n"

		 "but most of all...\n"
		 "You fought for the thrill of the fight.\n\n"
		 "When you fight, you feel alive.  You know\n"
		 "you are doing what you were born to do.\n"

		 "After the war, you found yourself without\n"
		 "a purpose...\n\n"

		 "no one to fight for...\n"
		 "no reason to fight...\n"
		 "So you left...\n\n"

		 "You've been wandering for years now...\n"
		 "Fighting for gold, glory, and always...\n"
		 "For the thrill...\n\n"

		 "You spent so much time fighting...\n"
		 "You don't know much else...\n"  
		 "You've been in many battles, and won\n"
		 "most of them.  You have been beaten\n"
		 "before, but you always get back up.\n\n"

		 "Today...\n\n"

		 "You arrive in the dreary town of Dullsville.\n"
	     "You've heard rumors of the great Dungeon...\n"
		 "You care not about the treasure, but you\n"
		 "know that there will be many battles to be\n"
		 "fought.  You are ready to test yourself...\n"
		 "To see if you are truly the greatest fighter\n"
		 "And maybe...\n\n"
		 "You'll be able to return home...\n\n"
	};

	system("cls");
	TypeText(L"Warrior\n", 1);
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"The Warrior is a strength based class.\n"
			  "They wield dual fist weapons for melee\n"
		      "combat. They have a weakness to magic\n"
		      "damage but have a bonus to strength.\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Confirm? (Y/N)\n", 1);
	Sleep(5000);

	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Qrelation.Analyze_Code...\n", 1); 
	Sleep(1000);
	TypeText(L"Result: [GENERIC CLASS DETECTED]\n", 1); 
	Sleep(1000);
	TypeText(L"Qrelation.Engine->Refactor_Code...\n", 1); 
	Sleep(1000);
	system("cls");
	PrintNumbers();
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"[REFACTOR COMPLETE]\n", 1);
	Sleep(1000);
	system("cls");

	TypeText(L"Brawler\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(Brawler, 5);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Strength: 15\n", 1);
	TypeText(L"Dexterity: 10\n", 1);
	TypeText(L"Wisdom: 5\n", 1);
	TypeText(L"Charisma: 10\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Starting Eqiupment: \n", 1);
	TypeText(L"Hard Leather Tunic\n", 1);
	TypeText(L"Hard Leather Pants\n", 1);
	TypeText(L"Hard Leather Boots\n", 1);
	TypeText(L"Iron Fists\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Confirm? (Y/N)\n", 1);
}

void PlayerCharacter::ScourgePrint()
{
	std::wstring Scourge
	{
		L"In this country...\n"
		 "You are an abomination...\n"
		 "A monster...\n\n"

		 "A Scourge...\n\n"

		 "You are not cursed...\n"
		 "You are not diseased...\n"
		 "You are not a demon...\n\n"
		 "You simply have the misfortune of being\n"
		 "born with the ability to use magic.\n\n"

		 "Thus people fear you.\n"
		 "Magic users are branded by the church.\n"
		 "The mark of the Scourge...\n\n"

		 "Your kind are killed...\n"
		 "Hunted...\n"
		 "Driven from their homes...\n\n"
		 "Forced into servitude...\n"

		 "You escaped from your grim fate many\n"
		 "years ago.\n\n"
		 "You've been wandering ever since.\n"

		 "Today...\n\n"

		 "You arrive in the dreary town of Dullsville.\n"
		 "You've heard rumors of the great Dungeon...\n"
		 "Tales of a great magic artifact.\n"
		 "Something that could give you power...\n"

		 "Power to fight back...\n\n"
	};

	system("cls");
	TypeText(L"Mage\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"The Mage is a wisdon based class.\n"
			  "They wield a staff for magic focused\n"
			  "combat. They have a weakness to melee\n"
			  "damage but have a bonus to wisdom.\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Confirm? (Y/N)\n", 1);
	Sleep(5000);

	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Qrelation.Analyze_Code...\n", 1);
	Sleep(1000);
	TypeText(L"Result: [GENERIC CLASS DETECTED]\n", 1);
	Sleep(1000);
	TypeText(L"Qrelation.Engine->Refactor_Code...\n", 1);
	Sleep(1000);
	system("cls");
	PrintNumbers();
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"[REFACTOR COMPLETE]\n", 1);
	Sleep(1000);
	system("cls");
	
	system("cls");
	TypeText(L"Scourge\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(Scourge, 10);
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Strength: 5\n", 1); 
	TypeText(L"Dexterity: 10\n", 1); 
	TypeText(L"Wisdom: 15\n", 1); 
	TypeText(L"Charisma: 10\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Starting Eqiupment: \n", 1); 
	TypeText(L"Silk Robe\n", 1); 
	TypeText(L"Silk Pants\n", 1);
	TypeText(L"Silk\n", 1); 
	TypeText(L"Staff\n", 1); 
	TypeText(L"5 Health Potions\n", 1); 
	TypeText(L"5 Mana Potions\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Confirm? (Y/N)\n", 1); 
}

void PlayerCharacter::SwindlerPrint()
{
	std::wstring Swindler
	{
		L"You are a liar...\n"
		 "A cheat...\n"
		 "A thief...\n\n"

		 "A Swindler...\n\n"

		 "You spent your fair share of time in jail.\n"
		 "However, you've always managed to escape.\n\n"

		 "Your last job went less than smoothly.\n"
		 "Not only were you caught...\n"
		 "This time you stole from the wrong Noble\n\n"

		 "You were sentenced to death...\n"
		 "No trial...\n"
		 "No jury...\n\n"

		 "And yet you managed to escape yet again...\n"
		 "though, with a large bounty on your head.\n\n"

		 "Unable to return home, you wander...\n\n"
 
		 "Today...\n\n"

		 "You arrive in the dreary town of Dullsville.\n"
		 "You've heard rumors of the great Dungeon...\n"
		 "The treaseure within...\n\n"

		 "Riches that could give you a second chance.\n"
	};

	system("cls");
	TypeText(L"Archer\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"The Archer is a Dexterity based class.\n"
		      "They wield a bow for ranged focused\n"
		      "combat. They have a weakness to magic\n"
		      "damage but have a bonus to Dexterity.\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Confirm? (Y/N)\n", 1);
	Sleep(5000);

	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Qrelation.Analyze_Code...\n", 1);
	Sleep(1000);
	TypeText(L"Result: [GENERIC CLASS DETECTED]\n", 1);
	Sleep(1000);
	TypeText(L"Qrelation.Engine->Refactor_Code...\n", 1);
	Sleep(1000);
	system("cls");
	PrintNumbers();
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"[REFACTOR COMPLETE]\n", 1);
	Sleep(1000);
	system("cls");
	
	system("cls");
	TypeText(L"Swindler\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(Swindler, 10);
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Strength: 10\n", 1); 
	TypeText(L"Dexterity: 15\n", 1);
	TypeText(L"Wisdom: 5\n", 1); 
	TypeText(L"Charisma: 10\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Starting Eqiupment: \n", 1); 
	TypeText(L"Light mail tunic\n", 1); 
	TypeText(L"Light mail pants\n", 1); 
	TypeText(L"Light mail boots\n", 1); 
	TypeText(L"Short Bow\n", 1); 
	TypeText(L"10 Health Potions\n", 1); 
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Confirm? (Y/N)\n", 1); 
}

void PlayerCharacter::JesterPrint()
{
	std::wstring Jester
	{
		L"You are a not strong...\n"
		 "You are not wise...\n"
		 "You are not quick...\n\n"

		 "You are a Jester...\n\n"

		 "You've spent your life entertaining others.\n"
		 "You've always been a bit of a jokester.\n"
		 "Many people say you have a gift for comedy.\n\n"

		 "But you've always wanted more...\n\n"

		 "You've always wanted to be an adventurer.\n"
		 "To explore the world and see new things.\n"
		 "To make a name for yourself.\n\n"

		 "One day you got that chance...\n\n"

		 "A wandering merchant came to town.\n"
		 "He had on him a strange mask...\n"
		 "He said it would grant certain abilities\n\n"

		 "You bought the mask and put it on...\n"
		 "You felt a strange power come over you...\n"
		 "You found you are able to inspire people...\n"
		 "You are able to bring out true potential...\n\n"

		 "You took this as a sign...\n"
		 "You set out on an adventure.\n\n"
			
		 "Today...\n\n"

		 "You arrive in the dreary town of Dullsville.\n"
		 "You've heard rumors of the great Dungeon...\n"
		 "This was the adventure you had always wanted.\n"
	};

	system("cls");
	TypeText(L"Cleric\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"The Cleric is a Charisma based class.\n"
		      "They focus on support magic to buff allies.\n" 
		      "They have a weakness to melee damage\n"
		      "but have a bonus to Charisma.\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Confirm? (Y/N)\n", 1);
	Sleep(5000);

	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Qrelation.Analyze_Code...\n", 1);
	Sleep(1000);
	TypeText(L"Result: [GENERIC CLASS DETECTED]\n", 1);
	Sleep(1000);
	TypeText(L"Qrelation.Engine->Refactor_Code...\n", 1);
	Sleep(1000);
	system("cls");
	PrintNumbers();
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"[REFACTOR COMPLETE]\n", 1);
	Sleep(1000);
	system("cls");
	
	system("cls");
	TypeText(L"Jester\n", 1);
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(Jester, 10);
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Strength: 5\n", 1); 
	TypeText(L"Dexterity: 10\n", 1); 
	TypeText(L"Wisdom: 10\n", 1); 
	TypeText(L"Charisma: 15\n", 1);
	TypeText(L"-------------------------------------------\n", 1);
	TypeText(L"Starting Eqiupment: \n", 1); 
	TypeText(L"Cloth chest\n", 1); 
	TypeText(L"Cloth pants\n", 1); 
	TypeText(L"Cloth boots\n", 1); 
	TypeText(L"Scepter\n", 1); 
	TypeText(L"5 Health Potions\n", 1);
	TypeText(L"5 Mana Potions\n", 1);
	TypeText(L"-------------------------------------------\n", 1); 
	TypeText(L"Confirm? (Y/N)\n", 1); 
}

////////////////////////////////// Combat functions   //////////////////////////////////

void PlayerCharacter::PerformAction(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	int choice = 0;
	while (choice < 1 || choice > 4)
	{
		std::cout << "=========================================\n";
		std::cout << "Selection an action: \n";
		std::cout << "[1] Attack\n";
		std::cout << "[2] Defend\n";
		std::cout << "[3] Use Item\n";
		std::cout << "[4] Use Skill\n";
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear(); // Clear the failure state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove the bad input
		}
	}

	switch (choice)
	{
	case 1:
		Attack(Combatants);
		break;
	case 2:
		Defend();
		break;
	case 3:
		CheckInventory();
		break;
	case 4:
		UseSkill(Combatants);
		break;
	}
};

void PlayerCharacter::Attack(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
    std::cout << "Choose your attack type: " << std::endl;
    std::cout << "1. Melee" << std::endl;
    std::cout << "2. Ranged" << std::endl;
    std::cout << "3. Magic" << std::endl;

    int attackTypeChoice;
    std::cin >> attackTypeChoice;
    attackTypeChoice--;

    // Ensure the player selects a valid attack type.
    if (attackTypeChoice < 0 || attackTypeChoice > 2)
    {
        std::cout << "Invalid attack type!" << std::endl;
        return;
    }

    // Cast the integer to the corresponding AttackType.
	AttackType attackType = static_cast<AttackType>(attackTypeChoice);

	std::cout << "Choose an enemy to attack: " << std::endl;

	int index = 0;

	// Generate a list of enemies and display them
	for (const auto& combatant : Combatants) {
		auto enemy = std::dynamic_pointer_cast<Enemy>(combatant);
		if (enemy != nullptr && enemy->GetCurrentHealth() > 0) {
			std::cout << index + 1 << ". " << enemy->GetName() << std::endl;
			index++;
		}
	}

	int enemyChoice;
	std::cin >> enemyChoice;
	enemyChoice--;

	if (enemyChoice >= 0 && enemyChoice < index)
	{
		// Find the selected enemy from the Combatants vector
		int enemyCount = 0;
		for (const auto& combatant : Combatants) {
			auto enemy = std::dynamic_pointer_cast<Enemy>(combatant);
			if (enemy != nullptr && enemy->GetCurrentHealth() > 0) {
				if (enemyCount == enemyChoice) {
					int damage = CalculateBaseDamage(attackType, enemy);
					enemy->TakeDamage(damage);
					std::cout << "You attack " << enemy->GetName() << " for " << damage << " damage!" << std::endl;
					break;
				}
				enemyCount++;
			}
		}
	}
	else
	{
		std::cout << "Invalid choice!" << std::endl;
	}
}

void PlayerCharacter::CheckInventory()
{
	if (Inventory.empty())
	{
		std::cout << "Your inventory is empty.\n";
		return;
	}

	std::cout << "Your inventory contains:\n";

	for (const auto& itemPair : Inventory)
	{
		const auto& item = itemPair.second.first;
		const auto quantity = itemPair.second.second;

		std::cout << item->GetName() << " x " << quantity << "\n";
		std::cout << "Description: " << item->GetDescription() << "\n";
	}
}

void PlayerCharacter::UseSkill(std::deque<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	// display a list of available skills:
	std::cout << "Skills: " << std::endl;
	int skillIndex = 1;

	for (const auto& skill : Skills)
	{
		std::cout << "[" << skillIndex << "]" << skill.GetName() << std::endl;
		skillIndex++;
	}

	// get the player's choice

	int skillChoice;
	while (true)
	{
		std::cout << "Choose a skill to use : " << std::endl;
		std::cin >> skillChoice;

		if (std::cin.fail()) {
			std::cout << "Invalid input! select a valid skill" << std::endl;
			std::cin.clear(); // Clear the failure state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove the bad input
		}
		else
		{
			break;
		}
	}

	skillChoice--;

	Skill selectedSkill = Skills[skillChoice];


	// check if the player has enough mana to use the skill
	int cost = selectedSkill.GetManaCost();
	int currentMana = GetCurrentMana();

	if (cost > currentMana)
	{
		std::cout << "You do not have enough mana to use that skill!" << std::endl;
		return;
	}

	int targetIndex = 1;

	//get list of enemies
	for (auto& combatant : Combatants)
	{
		if (combatant->GetCurrentHealth() > 0)
		{
			if (combatant == shared_from_this()) // Skip the player character as a target
				continue;

			std::string targetType = (std::dynamic_pointer_cast<Enemy>(combatant) != nullptr) ? "Enemy" : "Ally";
			std::cout << "[" << targetIndex << "] " << targetType << ": " << combatant->GetName() << std::endl;
			targetIndex++;
		}
	}

	int targetChoice;
	while (true)
	{
		std::cout << "Choose a target: ";
		std::cin >> targetChoice;

		if (std::cin.fail() || targetChoice < 1 || targetChoice > Combatants.size() - 1)
		{
			std::cout << "Invalid Choice. Please select a valid target." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}

	targetChoice--;

	// Get the selected enemy as the target
	auto target = Combatants[targetChoice];

	// Use the skill based on its type
	if (selectedSkill.GetSkillType() == SkillType::Attack)
	{
		// If it's an attack skill, calculate the damage and perform the attack
		int damage = selectedSkill.CalculateSkillDamage(shared_from_this(), target);
		target->TakeDamage(damage);

		std::cout << "You used the skill: " << selectedSkill.GetName() << std::endl;
		std::cout << "You attack " << target->GetName() << " for " << damage << " damage!" << std::endl;
	}
	else if (selectedSkill.GetSkillType() == SkillType::Buff)
	{
		// If it's a buff skill, apply the effect to the target
		selectedSkill.GetAddEffect()(*target);
		std::cout << "You used the skill: " << selectedSkill.GetName() << std::endl;
	}
	else
	{
		std::cout << "This skill type is not implemented yet!" << std::endl;
	}

	// Deduct the mana cost from the player's current mana
	UseMana(cost);
	std::cout << "You used " << cost << " mana. Current mana: " << GetCurrentMana() << std::endl;
}