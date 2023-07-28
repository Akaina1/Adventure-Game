// definition for StatusEffect class
// will hold the different status effects that can be applied to the player character
// the player will have a map of status effects and booleans representing whether the status effect is active or not
// the status effect will be applied to the player character when the boolean is set to true
// the status effect will be removed from the player character when the boolean is set to false
// status effects can directly affect the player character's stats, or they can affect the player character's ability to perform certain actions
// status effects can be applied to the player character by items, spells, or attacks
// status effects can be applied to the player character by the player character's actions (such as moving to a new location, picking up an item, etc.)
#pragma once

class CharacterTemplate;

#include "Main.h"
#include "Location.h"
#include "Item.h"
#include "MainMenu.h"

class StatusEffect
{
	
private:
	std::string Name; // name of the status effect
	std::string Description; // description of the status effect
	int Id; // id of the status effect
	//int Duration; // duration of the status effect (need to implement turn system when creating combat system) for now, duration will be left out
	std::function<void(CharacterTemplate& character)> AddEffect; // function to add the status effect to the player character
	std::function<void(CharacterTemplate& character)> RemoveEffect; // function to remove the status effect from the player character
	

public:

	enum class State { // enum class for the type of effect the status effect has
		Active = 1,
		Inactive = 2,
		Blocked = 3
	};
	State state; // state of the status effect

	StatusEffect(); // default constructor
	virtual ~StatusEffect(); // destructor
	StatusEffect(std::string name, std::string description, int id, std::function<void(CharacterTemplate& character)> addEffect, std::function<void(CharacterTemplate& character)> removeEffect, State state); // constructor with parameters
	
//getters
	std::string GetName() const { return Name; }; // returns the name of the status effect
	std::string GetDescription() const { return Description; }; // returns the description of the status effect
	int GetId() const { return Id; }; // returns the id of the status effect
	std::function<void(CharacterTemplate& character)> GetAddEffect() const { return AddEffect;}; // returns the add effect of the status effect
	std::function<void(CharacterTemplate& character)> GetRemoveEffect() const { return RemoveEffect;}; // returns the remove effect of the status effect
	State GetEffectState() const { return state;}; // returns the state of the status effect

	//setters
	void SetName(std::string name); // sets the name of the status effect
	void SetDescription(std::string description); // sets the description of the status effect
	//void SetEffect(std::function<void(PlayerCharacter& player)> effect); // sets the effect of the status effect
	void SetEffectState(State newstate); // sets the state of the status effect

	//other functions
	void Print(const StatusEffect& effect) const; // prints the status effect
	friend std::ostream& operator<<(std::ostream& os, const StatusEffect::State& state);
};

