// implementation file for PlayerCharacter class
#include "PlayerCharacter.h"



// override the print function from the I_Print class

void PlayerCharacter::Print(std::ostream& os) const
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
	//print inventory
	for (auto item : Inventory)
	{
		os << item.first.GetName() << ": " << item.second << std::endl;
	}	
	os << "-------------------------------------------" << std::endl;
	os << "Status Effects: " << std::endl;
	for (auto effect : Afflictions)
	{
		if (effect.state == StatusEffect::State::Active)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;
			break;
		}
		else if (effect.state == StatusEffect::State::Inactive)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;
			break;
		}
		else if (effect.state == StatusEffect::State::Blocked)
		{
			os << effect.GetName() << ": " << effect.state << std::endl;
			break;
		}
	}
}

// default constructor
PlayerCharacter::PlayerCharacter()
	: Name{ "Default" }, MaxHealth{ 100 }, MaxMana{ 100 }, Level{ 1 }, Experience{ 0 }, Gold{ 1000 }, PlayerClass{0}, StatValues{ {"Strength", 0}, {"Dexterity", 0}, {"Wisdom", 0}, {"Charisma", 0} }, Inventory{}, Afflictions{ }, CurrentLocation { }
{
}

// constructor with parameters
PlayerCharacter::PlayerCharacter(std::string name, int maxhealth,int currenthealth, int maxmana, int currentmana, int level, int experience, int gold, int pclass, std::map<std::string, int> statValues, std::map<Item, int> inventory, std::vector<StatusEffect> afflictions)
	: Name{ name }, MaxHealth{ maxhealth }, CurrentHealth{currenthealth}, MaxMana{maxmana},CurrentMana{currentmana}, Level{level}, Experience{experience}, Gold{gold}, PlayerClass{pclass}, StatValues{statValues}, Inventory{inventory}, Afflictions{afflictions}, CurrentLocation{}
{
}

// destructor
PlayerCharacter::~PlayerCharacter()
{
}

// returns the name of the player class
std::string PlayerCharacter::GetPlayerClassName() const
{
    int Class = PlayerClass;
	
	if (Class == 0)
	{
		return "Brawler";
	}
	else if (Class == 1)
	{
		return "Scourge";
	}
	else if (Class == 2)
	{
		return "Sorcerer";
	}
	else if (Class == 3)
	{
		return "Ranger";
	}
	else
	{
		return "Invalid Class";
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









void PlayerCharacter::AddItem(Item& item, int quantity,PlayerCharacter* player) // adds an item to the player character's inventory
{
	if (Inventory.count(item) > 0)
	{
		Inventory[item] += quantity;
	}
	else
	{
		Inventory[item] = quantity;
	}
}

void PlayerCharacter::RemoveItem(Item& item, int quantity, PlayerCharacter* player) // removes an item from the player character's inventory
{
	if (Inventory.count(item) > 0)
	{
		Inventory[item] -= quantity;
	}
	else
	{
		Inventory[item] = 0;
	}
}

int PlayerCharacter::GetItemQuantity(Item& item, PlayerCharacter& player) // returns the quantity of an item in the player character's inventory
{
	if (Inventory.count(item) > 0)
	{
		return Inventory[item];
	}
	else
	{
		return 0;
	}
}

void PlayerCharacter::PrintInventory()  // prints the inventory of the player character
{
	for ( auto &pair : Inventory)
	{
		std::cout << pair.first.GetName() << ": " << pair.second << std::endl;
	}

}











void PlayerCharacter::IncreaseMaxHealth(int health, PlayerCharacter* player) // sets the max health of the player character
{
	MaxHealth += health;
}

void PlayerCharacter::DecreaseMaxHealth(int health, PlayerCharacter* plaer)
{
	MaxHealth -= health;
}

void PlayerCharacter::heal(int health, PlayerCharacter* player) // heals the player character
{
	CurrentHealth += health;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void PlayerCharacter::TakeDamage(int damage, PlayerCharacter* player) // damages the player character
{
	CurrentHealth -= damage;

	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}

bool PlayerCharacter::IsDead(PlayerCharacter& player) // checks if the player character is dead
{
	return CurrentHealth <= 0;
}












void PlayerCharacter::SetMaxMana(int mana, PlayerCharacter* player) // sets the max mana of the player character
{
	if (MaxMana < mana)
	{
		MaxMana += mana;
	}
	else
	{
		MaxMana = MaxMana;
	}
}

void PlayerCharacter::RestoreMana(int mana, PlayerCharacter* player) // restores mana to the player character
{
	CurrentMana += mana;

	if (CurrentMana > MaxMana)
	{
		CurrentMana = MaxMana;
	}
}

void PlayerCharacter::UseMana(int cost, PlayerCharacter* player) // uses mana from the player character
{
	CurrentMana -= cost;

	if (CurrentMana < 0)
	{
		CurrentMana = 0;
	}
}









void PlayerCharacter::ApplyEffect(StatusEffect& effect,PlayerCharacter* player) // applies a status effect to the player character
{
	

	effect.state = StatusEffect::State::Active;

	effect.StatusEffect::GetEffect()(*player);

	Afflictions.push_back(effect);

	std::cout << "EFFECT ADDED TO PLAYER" << std::endl;

};


void PlayerCharacter::UpdateEffects(StatusEffect& effect,PlayerCharacter* player) // takes in an effect to update, and a pointer to a character to access their Afflictions vector
{
	// check if the effect is in the vector

	for (auto& affliction : Afflictions)
	{
		if (affliction.GetId() == effect.GetId() )
		{
			// if the effect is in the vector check if the effect is active or not

			if (affliction.state == StatusEffect::State::Active)
			{
				affliction.state = StatusEffect::State::Inactive;
				std::cout << "EFFECT REMOVED" << std::endl;
			}
			else if (affliction.state == StatusEffect::State::Inactive)
			{
				affliction.state = StatusEffect::State::Active;
				effect.StatusEffect::GetEffect()(*player);
				std::cout << "EFFECT ADDED" << std::endl;
			}
			else if (affliction.state == StatusEffect::State::Blocked)
			{
				std::cout << "CAN'T UPDATE BLOCKED EFFECT" << std::endl;
			}	
		}
		// if the effect is not in the vector add the effect to the vector
		else
		{
			ApplyEffect(effect, player);
		}
	}

	


	
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
		MaxHealth = 500;
		MaxMana = 30;
		ClassStatValues = { {"Strength", 15}, { "Dexterity", 10 }, { "Wisdom", 10 }, { "Charisma", 10 } };
		continue;
		}

	case 2: //Scourge
		PlayerClass = 2;
		MaxHealth = 125;
		MaxMana = 200;
		ClassStatValues = { {"Strength", 10}, { "Dexterity", 10 }, { "Wisdom", 15 }, { "Charisma", 10 } };
		break;

	case 3://Swindler
		PlayerClass = 3;
		MaxHealth = 125;
		MaxMana = 20;
		ClassStatValues = { {"Strength", 10}, { "Dexterity", 15 }, { "Wisdom", 10 }, { "Charisma", 10 } };
		break;

	case 4://Jester
		PlayerClass = 4;
		MaxHealth = 150;
		MaxMana = 100;
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
	//Inventory = {};
    
	/*Afflictions = 
	{ {"Poisoned", false}, { "Bleeding", false }, { "Burned", false }, { "Frozen", false }, { "Stunned", false }, 
	{ "Blinded", false }, { "Confused", false }, { "Charmed", false }, { "Enraged", false }, { "Blessed", false }, 
	{ "Cursed", false }, { "Invisible", false }, { "Silenced", false }, { "Sleeping", false }, { " ", false } };*/

	// show confirmation of character creation
	std::wcout << "Press Enter to start the game..." << std::endl;
	std::wcin.ignore();
	std::wcin.get();
	
	// return the newly created player character  
	return Player;
}