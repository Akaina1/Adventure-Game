// implements the StatusEffect class
#include "StatusEffect.h"

StatusEffect::StatusEffect() // default constructor
{
}

StatusEffect::~StatusEffect() // destructor
{
}

StatusEffect::StatusEffect(std::string name, std::string description, int id, std::function<void(PlayerCharacter& player)> effects, State state) // constructor with parameters
{
	this->Name = name;
	this->Description = description;
	this->Id = id;
	this->Effects = effects;
	this->state = state;
}

void StatusEffect::Print(const StatusEffect& effect) const // print effect info
{
	std::cout << "Name: " << Name << std::endl;
	std::cout << "Description: " << Description << std::endl;
	std::cout << "ID: " << Id << std::endl;
	std::cout << "State: " << effect.state << std::endl;
}

//setters

void StatusEffect::SetName(std::string name)
{
	this->Name = name;
}

void StatusEffect::SetDescription(std::string description)
{
	this->Description = description;
}

void StatusEffect::SetEffectState(State newstate)				// sets the state of the status effect
{
	enum State oldstate = this->GetEffectState();
	oldstate = newstate;
}

// other functions

//void StatusEffect::ApplyEffect(StatusEffect& effect, PlayerCharacter* player)
//{
//
//	//std::map<StatusEffect, bool> Afflictions;
//	// update effect in player's status effects vector
//	// if effect is already active, do nothing
//	// if effect is inactive, apply effect
//	// if effect is blocked, do nothing
//
//
//	if (effect.state == State::Inactive)
//	{
//		effect.Effects(*player);
//		std::cout << "EFFECT APPLIED TO PLAYER" << std::endl;
//		effect.state = StatusEffect::State::Active;
//	}
//	else if (state == State::Active)
//	{
//		std::cout << "**EFFECT IS ALREADY ACTIVE**" << std::endl;
//	}
//	else if (state == State::Blocked)
//	{
//		std::cout << "**PLAYER IS BLOCKING THAT EFFECT**" << std::endl;
//	}
//}
//
//void StatusEffect::RemoveEffect(StatusEffect& effects, PlayerCharacter* player)
//{
//
//	enum State state = this->GetEffectState();
//	if (state == State::Active)
//	{
//		effects.Effects(*player); // I don't know if this is the right way to do this (calling the effect function again will just reset the effect)
//		std::cout << "**EFFECT REMOVED FROM PLAYER**" << std::endl;
//		state = State::Inactive;
//	}
//	else if (state == State::Blocked)
//	{
//		std::cout << "**PLAYER IS BLOCKING THAT EFFECT**" << std::endl;
//	}
//	else if (state == State::Inactive)
//	{
//		std::cout << "**EFFECT IS NOT ACTIVE**" << std::endl;
//	}
//}

// overloaded operator<< for printing the state of the effect

std::ostream& operator<<(std::ostream& os, const StatusEffect::State& state)
{
	switch (state) {

		case StatusEffect::State::Active: os << "Active"; break;
		case StatusEffect::State::Inactive: os << "Inactive"; break;
		case StatusEffect::State::Blocked: os << "Blocked"; break;
		default: os << "Unknown"; break;
	}
	return os;
}