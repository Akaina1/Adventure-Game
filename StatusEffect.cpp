// implements the StatusEffect class
#include "StatusEffect.h"
#include "CharacterTemplate.h"
#include "Effect.h"

StatusEffect::StatusEffect() // default constructor
{
}

StatusEffect::~StatusEffect() // destructor
{
}

StatusEffect::StatusEffect(std::string name, std::string description, int id, std::function<void(CharacterTemplate& character)> addEffect, std::function<void(CharacterTemplate& character)> undoEffect, int duration) // constructor with parameters
{
	this->Name = name;
	this->Description = description;
	this->Id = id;
	this->AddEffect = addEffect;
	this->UndoEffect = undoEffect;
	this->duration = duration;
}

void StatusEffect::Print(const StatusEffect& effect) const // print effect info
{
	std::cout << "Name: " << Name << std::endl;
	std::cout << "Description: " << Description << std::endl;
	std::cout << "ID: " << Id << std::endl;
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

void StatusEffect::ApplyEffect(CharacterTemplate& character)
{
	this->AddEffect(character);
}
void StatusEffect::RemoveEffect(CharacterTemplate& character)
{
	this->UndoEffect(character);
}

