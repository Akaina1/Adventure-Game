// definition of the combat class, will handle all combat related functions
#pragma once
#include "Main.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Item.h"
#include "StatusEffect.h"

class Combat
{
private:
	bool InCombat = false; // First thing to check is if the player is in combat
	bool IsPlayerTurn = false; // If the player is in combat, is it their turn?
	std::shared_ptr<PlayerCharacter> Player; // player character
	std::vector<std::shared_ptr<CharacterTemplate>> Combatants; // Vector of all combatants
	int CurrentTurn; // Current turn in combat
	int MaxTurns; // Max turns in combat before Player death
	struct CompareSpeed {
		bool operator()(const std::shared_ptr<CharacterTemplate>& a, const std::shared_ptr<CharacterTemplate>& b) 
		{
			if (a == nullptr || b == nullptr)
			{
				std::cerr << "Error: Null pointer detected in CompareSpeed." << std::endl;
				return false;
			}
			return a->GetSpeed() > b->GetSpeed();
		}
	};
	std::priority_queue<std::shared_ptr<CharacterTemplate>, std::vector<std::shared_ptr<CharacterTemplate>>, CompareSpeed> SpeedQueue;

public:
	Combat(std::shared_ptr<PlayerCharacter> player, std::vector<std::shared_ptr<CharacterTemplate>> combatants); // Default constructor
	~Combat() {} // Destructor

	void StartCombat(); // Start combat
	void EndCombat(); // End combat

    void CurrentAction(); // Current Character action
	
	void HandleTurn(); // Handle turn
	void CombatDisplay(); // Display combat
	bool EnemiesAreAlive(); // Check if enemies are alive
	bool AlliesAreAlive(); // Check if allies are alive

	void PerformAction(); // Perform action

};

