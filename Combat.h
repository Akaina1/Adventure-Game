// definition of the combat class, will handle all combat related functions
#pragma once
#include "Main.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Item.h"
#include "BossEnemy.h"



class Combat : public std::enable_shared_from_this<Combat>
{
private:
	bool InCombat = false; // First thing to check is if the player is in combat
	bool IsPlayerTurn = false; // If the player is in combat, is it their turn?
	std::shared_ptr<PlayerCharacter> Player; // player character
	std::deque<std::shared_ptr<CharacterTemplate>> Combatants; // Vector of all combatants
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

public:
	Combat(std::shared_ptr<PlayerCharacter> player, std::deque<std::shared_ptr<CharacterTemplate>> combatants); // Default constructor
	~Combat() {} // Destructor

	void StartCombat(); // Start combat loop

    bool CurrentAction(); // Current Character action
	
	void HandleTurn(); // Handle turn
	void CombatDisplay(); // Display combat
	bool EnemiesAreAlive(); // Check if enemies are alive
	bool AlliesAreAlive(); // Check if allies are alive
	int GetCurrentTurn() { return CurrentTurn; }; // Get current turn

	void UpdateEffectsDuration(CharacterTemplate& character); // Update status effect duration
	void AddCombatant(std::shared_ptr<CharacterTemplate> combatant); // Add combatant to combat)
	virtual void InitializeCombat(); // Initialize combat

	std::shared_ptr<CharacterTemplate> GetLowestHealthEnemy(std::deque<std::shared_ptr<CharacterTemplate>> Combatants); // Get lowest health enemy
	std::shared_ptr<CharacterTemplate> GetHighestHealthEnemy(std::deque<std::shared_ptr<CharacterTemplate>> Combatants); // Get highest health enemy
	std::shared_ptr<CharacterTemplate> GetLowestHealthAlly(std::deque<std::shared_ptr<CharacterTemplate>> Combatants); // Get lowest health ally
	std::shared_ptr<CharacterTemplate> GetHighestHealthAlly(std::deque<std::shared_ptr<CharacterTemplate>> Combatants); // Get highest health ally
	std::shared_ptr<CharacterTemplate> GetBossEnemy(std::deque<std::shared_ptr<CharacterTemplate>> Combatants); // Get boss enemy
	std::shared_ptr<CharacterTemplate> GetPlayer(std::deque<std::shared_ptr<CharacterTemplate>> Combatants); // Get player

};

