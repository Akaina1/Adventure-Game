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
	std::vector<std::shared_ptr<Enemy>> Enemies; // Vector of enemies in combat
	std::shared_ptr<PlayerCharacter> Player; // Vector of players and allies in combat
	std::vector<std::shared_ptr<PlayerCharacter>> Allies; // Vector of allies to the player in combat
	int CurrentTurn; // Current turn in combat
	int MaxTurns; // Max turns in combat before Player death

public:
	Combat(std::shared_ptr<PlayerCharacter> player, std::vector<std::shared_ptr<Enemy>> enemies) : Player{ player }, Enemies{enemies}, CurrentTurn{0}, MaxTurns{999} {} // Default constructor
	Combat(std::shared_ptr<PlayerCharacter> player, std::vector<std::shared_ptr<PlayerCharacter>> allies, std::vector<std::shared_ptr<Enemy>> enemies) : InCombat{ true }, IsPlayerTurn{ true }, Player{ player }, Allies{ allies }, Enemies{ enemies }, CurrentTurn{ 0 }, MaxTurns{999} {} // Constructor)
	~Combat() {} // Destructor

	void StartCombat(); // Start combat
	void EndCombat(); // End combat
	void PlayerAction(); // Player action
	void EnemyAction(int enemyIndex); // Enemy action
	void AllyAction(int allyIndex); // Ally action
	void HandleTurn(); // Handle turn
	void CheckVictory(); // Check if the player has won
	void CheckDefeat(); // Check if the player has lost
	void CombatDisplay(); // Display combat

};

