// implementation file for PlayerCharacter class
#include "PlayerCharacter.h"
////////////////////////////////// Default functions //////////////////////////////////

PlayerCharacter::PlayerCharacter() // default constructor
	: Name{ "Default" }, MaxHealth{ 100 }, MaxMana{ 100 }, Level{ 1 }, Experience{ 0 }, Gold{ 1000 }, PlayerClass{ 0 }, StatValues{ {"Strength", 0}, {"Dexterity", 0}, {"Wisdom", 0}, {"Charisma", 0} }, Inventory{}, Afflictions{ }, CurrentLocation{ }
{
}

PlayerCharacter::~PlayerCharacter() // destructor
{
}

// constructor with parameters
PlayerCharacter::PlayerCharacter(std::string name, int maxhealth, int currenthealth, int maxmana,
	int currentmana, int level, int experience, int gold, int pclass,
	std::map<std::string, int> statValues, std::map<Item, int> inventory,
	std::vector<StatusEffect> afflictions)
	: Name{ name }, MaxHealth{ maxhealth }, CurrentHealth{ currenthealth }, MaxMana{ maxmana }, CurrentMana{ currentmana }, Level{ level }, Experience{ experience }, Gold{ gold }, PlayerClass{ pclass }, StatValues{ statValues }, Inventory{ inventory }, Afflictions{ afflictions }, CurrentLocation{}
{
}

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










////////////////////////////////// Name functions     //////////////////////////////////








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
		return "Invalid Class";
	}
}









////////////////////////////////// Gold functions     //////////////////////////////////










////////////////////////////////// Experience functions ////////////////////////////////









////////////////////////////////// Inventory functions /////////////////////////////////

void PlayerCharacter::AddItem(Item& item, int quantity, PlayerCharacter* player) // adds an item to the player character's inventory
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
	for (auto& pair : Inventory)
	{
		std::cout << pair.first.GetName() << ": " << pair.second << std::endl;
	}

}


////////////////////////////////// Health functions   //////////////////////////////////

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


////////////////////////////////// Mana functions     //////////////////////////////////

void PlayerCharacter::IncreaseMaxMana(int mana, PlayerCharacter* player) // sets the max mana of the player character
{
	MaxMana += mana;
}

void PlayerCharacter::DecreaseMaxMana(int mana, PlayerCharacter* player)
{
	MaxMana -= mana;
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


////////////////////////////////// Effect functions   //////////////////////////////////

void PlayerCharacter::ApplyEffect(StatusEffect& effect, PlayerCharacter* player) // applies a status effect to the player character
{

	effect.state = StatusEffect::State::Active;

	effect.StatusEffect::GetAddEffect()(*player);

	std::cout << "EFFECT ADDED TO PLAYER" << std::endl;

};

void PlayerCharacter::RemoveEffect(StatusEffect& effect, PlayerCharacter* player) // removes a status effect from the player character
{
	effect.state = StatusEffect::State::Inactive;

	effect.StatusEffect::GetRemoveEffect()(*player);

	std::cout << "EFFECT REMOVED FROM PLAYER" << std::endl;
}

void PlayerCharacter::UpdateEffects(StatusEffect& effect, PlayerCharacter* player) // takes in an effect to update, and a pointer to a character to access their Afflictions vector
{
	bool foundEffect = false;
	// check if the effect is in the vector
	for (auto& affliction : Afflictions)
	{
		if (affliction.GetId() == effect.GetId())
		{
			foundEffect = true;
			// if the effect is in the vector check if the effect is active or not
			if (affliction.state == StatusEffect::State::Active)
			{
				RemoveEffect(affliction, player);
			}
			else if (affliction.state == StatusEffect::State::Inactive)
			{
				ApplyEffect(affliction, player);
			}
			else if (affliction.state == StatusEffect::State::Blocked)
			{
				std::cout << "CAN'T UPDATE BLOCKED EFFECT" << std::endl;
			}

		}
	}

	if (!foundEffect) //don't want to edit vector while iterating through it, so add effect after iterating through vector
	{
		ApplyEffect(effect, player);
		Afflictions.push_back(effect);
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

	while (!confirmed)
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

		ChosenClass = choice;

		switch (choice)
		{
		case 1:
			system("cls");
			TypeText(L"Brawler", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Description: The brawler is a strength based class. Focused on melee it comes with bonus to strength but a weakness to magic.", 1); std::wcout << std::endl;
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

			char Confirm;
			std::cin >> Confirm;
			confirmed = Confirm == 'Y' || Confirm == 'y';
			break;

		case 2:
			system("cls");
			TypeText(L"Scourge", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Description: The scourge is a Mage type class. Focused on magic it comes with bonus to wisdom but a weakness to melee.", 1); std::wcout << std::endl;
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

			char Confirm2;
			std::cin >> Confirm2;
			confirmed = Confirm2 == 'Y' || Confirm2 == 'y';
			break;

		case 3:
			system("cls");
			TypeText(L"Swindler", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Description: The swindler is a Dexterity based class. Focused on ranged it comes with bonus to dexterity but a weakness to melee.", 1); std::wcout << std::endl;
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

			char Confirm3;
			std::cin >> Confirm3;
			confirmed = Confirm3 == 'Y' || Confirm3 == 'y';
			break;

		case 4:
			system("cls");
			TypeText(L"Jester", 1); std::wcout << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Description: The Jester is a Charisma based class. Focused on support it comes with bonus to charisma but a weakness to melee.", 1); std::wcout << std::endl;
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

			char Confirm4;
			std::cin >> Confirm4;
			confirmed = Confirm4 == 'Y' || Confirm4 == 'y';
			break;

		}

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
		TypeText(L"Points to spend: ", 1); std::wcout << StatPoints << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"1. Strength", 0); std::wcout << std::endl;
		TypeText(L"2. Dexterity", 0); std::wcout << std::endl;
		TypeText(L"3. Wisdom", 0); std::wcout << std::endl;
		TypeText(L"4. Charisma", 0); std::wcout << std::endl;
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
		TypeText(L"Choose a stat to increase: ", 1); std::wcout << std::endl;

		while (StatPoints > 0)
		{
			TypeText(L"Points to spend: ", 1); std::wcout << StatPoints << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			TypeText(L"Current Stats: ", 0); std::wcout << std::endl;
			TypeText(L"Strength: ", 0); std::wcout << StatValues["Strength"] << std::endl;
			TypeText(L"Dexterity: ", 0); std::wcout << StatValues["Dexterity"] << std::endl;
			TypeText(L"Wisdom: ", 0); std::wcout << StatValues["Wisdom"] << std::endl;
			TypeText(L"Charisma: ", 0); std::wcout << StatValues["Charisma"] << std::endl;
			TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;
			int ChosenStat;
			std::cin >> ChosenStat;

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

		/*system("cls");
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
		TypeText(L"-------------------------------------------", 1); std::wcout << std::endl;*/

	}
}




