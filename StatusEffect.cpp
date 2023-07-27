// implements the StatusEffect class
#include "StatusEffect.h"

StatusEffect::StatusEffect() // default constructor
{
}

StatusEffect::~StatusEffect() // destructor
{
}

StatusEffect::StatusEffect(std::string name, std::string description, int id, std::function<void(PlayerCharacter& player)> addEffect, std::function<void(PlayerCharacter& player)> removeEffect, State state) // constructor with parameters
{
	this->Name = name;
	this->Description = description;
	this->Id = id;
	this->AddEffect = addEffect;
	this->RemoveEffect = removeEffect;
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
