// implementation file for PlayerCharacter class
#define NOMINMAX
#include "PlayerCharacter.h"
#include "Item.h"
#include "NPC.h"
#include "Enemy.h"
#include "GameSetup.h"
////////////////////////////////// Default functions //////////////////////////////////

PlayerCharacter::PlayerCharacter() // default constructor
{
}

PlayerCharacter::~PlayerCharacter() // destructor
{
}

// constructor with parameters
PlayerCharacter::PlayerCharacter(std::string name, int maxhealth, int currenthealth,
	int maxmana, int currentmana, int level, int speed, int attack, int defense,
	bool isDefending,long long experience,
	int gold, int playerClass, std::map<std::string, int> statValues,
	std::unordered_map<int, std::pair<std::shared_ptr<Item>, int>> inventory,
	std::vector<StatusEffect> afflictions) :
	CharacterTemplate(name, maxhealth, currenthealth, maxmana, currentmana, level, speed, attack, defense,
	isDefending, statValues, afflictions), Experience(experience), Gold(gold), PlayerClass(playerClass), Inventory(inventory)
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
		if (effect.state == StatusEffect::State::Active)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;

		}
		else if (effect.state == StatusEffect::State::Inactive)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;

		}
		else if (effect.state == StatusEffect::State::Blocked)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;

		}
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

	std::cout << "You can move to the following Locations: \n";
	int count = 0;
	for (int i = 0; i < currentLocation->GetConnectedLocationsCount(); i++)
	{
		std::shared_ptr<Location> connectedLocation = currentLocation->GetConnectedLocation(i);
		std::cout << ++count << ": " << connectedLocation->GetName() << "\n";
	}

	std::cout << "You can move to the following Rooms: \n";
	for (int i = 0; i < currentLocation->GetConnectedRoomsCount(); i++)
	{
		std::shared_ptr<Room> connectedLocation = currentLocation->GetConnectedRoom(i);
		std::cout << ++count << ": " << connectedLocation->GetName() << "\n";
	}

	std::cout << "Enter the number of the Location or Room you want to move to: ";
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
		return "Ranger";
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

	// display the level up message
	std::cout << "You have leveled up!" << std::endl;
	std::cout << "You are now level " << Level << "!" << std::endl;
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
	//1. get user input for character name
	system("cls");
	std::cin.ignore();
	std::string inputname;
	TypeText(L"Enter your character's name: ", 10); std::wcout << std::endl;
	TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
	std::getline(std::cin, inputname);
	this->SetName(inputname);

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
		TypeText(L"1. Brawler", 1); std::wcout << std::endl;
		TypeText(L"2. Scourge", 1); std::wcout << std::endl;
		TypeText(L"3. Swindler", 1); std::wcout << std::endl;
		TypeText(L"4. Jester", 1); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		std::cin >> choice;
		std::cin.ignore();


		
		std::string Confirm;

		switch (choice)
		{
		case 1:
			system("cls");
			TypeText(L"Brawler", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"The Brawler is a strength based class.\n"
				      "Focused on melee it comes with bonus\n" 
				      "to strength but a weakness to magic.\n", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Strength: 15", 1); std::wcout << std::endl;
			TypeText(L"Dexterity: 10", 1); std::wcout << std::endl;
			TypeText(L"Wisdom: 5", 1); std::wcout << std::endl;
			TypeText(L"Charisma: 10", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Starting Eqiupment: ", 1); std::wcout << std::endl;
			TypeText(L"Hard Leather Tunic", 1); std::wcout << std::endl;
			TypeText(L"Hard Leather Pants", 1); std::wcout << std::endl;
			TypeText(L"Hard Leather Boots", 1); std::wcout << std::endl;
			TypeText(L"Iron Fists", 1); std::wcout << std::endl;
			TypeText(L"10 Health Potions", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Confirm? (Y/N)", 1); std::wcout << std::endl;

			
			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;

		case 2:
			system("cls");
			TypeText(L"Scourge", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"The Scourge is a Mage type class.\n" 
				      "Focused on magic it comes with a\n" 
				      "bonus to wisdom but a weakness to melee.\n", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Strength: 5", 1); std::wcout << std::endl;
			TypeText(L"Dexterity: 10", 1); std::wcout << std::endl;
			TypeText(L"Wisdom: 15", 1); std::wcout << std::endl;
			TypeText(L"Charisma: 10", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Starting Eqiupment: ", 1); std::wcout << std::endl;
			TypeText(L"Silk Robe", 1); std::wcout << std::endl;
			TypeText(L"Silk Pants", 1); std::wcout << std::endl;
			TypeText(L"Silk", 1); std::wcout << std::endl;
			TypeText(L"Staff", 1); std::wcout << std::endl;
			TypeText(L"5 Health Potions", 1); std::wcout << std::endl;
			TypeText(L"5 Mana Potions", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Confirm? (Y/N)", 1); std::wcout << std::endl;

			
			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;

		case 3:
			system("cls");
			TypeText(L"Swindler", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"The Swindler is a Dexterity based class.\n"
				      "Focused on ranged it comes with bonus to\n"
				      "dexterity but a weakness to melee.\n", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Strength: 10", 1); std::wcout << std::endl;
			TypeText(L"Dexterity: 15", 1); std::wcout << std::endl;
			TypeText(L"Wisdom: 5", 1); std::wcout << std::endl;
			TypeText(L"Charisma: 10", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Starting Eqiupment: ", 1); std::wcout << std::endl;
			TypeText(L"Light mail tunic", 1); std::wcout << std::endl;
			TypeText(L"Light mail pants", 1); std::wcout << std::endl;
			TypeText(L"Light mail boots", 1); std::wcout << std::endl;
			TypeText(L"Short Bow", 1); std::wcout << std::endl;
			TypeText(L"10 Health Potions", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Confirm? (Y/N)", 1); std::wcout << std::endl;

			
			std::getline(std::cin, Confirm);
			confirmed = Confirm == "Y" || Confirm == "y";
			if (!confirmed)
				continue;
			break;

		case 4:
			system("cls");
			TypeText(L"Jester", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"The Jester is a Charisma based class.\n" 
				      "Focused on support it comes with bonus\n"
				      "to charisma but a weakness to melee.\n", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Strength: 5", 1); std::wcout << std::endl;
			TypeText(L"Dexterity: 10", 1); std::wcout << std::endl;
			TypeText(L"Wisdom: 10", 1); std::wcout << std::endl;
			TypeText(L"Charisma: 15", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Starting Eqiupment: ", 1); std::wcout << std::endl;
			TypeText(L"Cloth chest", 1); std::wcout << std::endl;
			TypeText(L"Cloth pants", 1); std::wcout << std::endl;
			TypeText(L"Cloth boots", 1); std::wcout << std::endl;
			TypeText(L"Raipier", 1); std::wcout << std::endl;
			TypeText(L"10 Health Potions", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Confirm? (Y/N)", 1); std::wcout << std::endl;

			
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
	}while (!confirmed);
}

////////////////////////////////// Combat functions   //////////////////////////////////

void PlayerCharacter::PerformAction(std::vector<std::shared_ptr<CharacterTemplate>>& Combatants)
{
	int choice = 0;
	while (choice < 1 || choice > 4)
	{
		std::cout << "Selection an action: \n";
		std::cout << "[1] Attack\n";
		std::cout << "[2] Defend\n";
		std::cout << "[3] Use Item\n";
		std::cout << "[4] Run Away\n";
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
	}
};

void PlayerCharacter::Attack(std::vector<std::shared_ptr<CharacterTemplate>>& Combatants)
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
	std::vector<std::shared_ptr<Enemy>> enemyList;

	// Generate a list of enemies
	for (auto& combatant : Combatants) {
		auto enemy = std::dynamic_pointer_cast<Enemy>(combatant);
		if (enemy != nullptr && enemy->GetCurrentHealth() > 0) {
			std::cout << index + 1 << ". " << enemy->GetName() << std::endl;
			enemyList.push_back(enemy);
			index++;
		}
	}

	int enemyChoice;
	std::cin >> enemyChoice;
	enemyChoice--;

	if (enemyChoice >= 0 && enemyChoice < enemyList.size())
	{
		auto enemy = enemyList[enemyChoice];
		int damage = CalculateDamage(attackType, enemy);
		enemy->TakeDamage(damage);

		std::cout << "You attack " << enemy->GetName() << " for " << damage << " damage!" << std::endl;
	}
	else
	{
		std::cout << "Invalid choice!" << std::endl;
	}
}

void PlayerCharacter::Defend()
{
	// increase defense by 25%
	Defense *= 1.25;
	// indicate that player is defending
	IsDefending = true;

	std::cout << "You brace yourself for incoming attacks, increasing your defense!" << std::endl;
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