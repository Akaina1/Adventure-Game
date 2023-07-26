// Defining the Location class
#pragma once
#include "Main.h"
class PlayerCharacter;

class Location
{
private:
	std::string name; // Name of location
	std::string description; // Description of location
public:
	virtual std::string GetName() const =0; // Pure virtual function for getting name of location
    virtual std::string GetDescription() const =0; // Pure virtual function for getting description of location
	virtual void OnEnter(PlayerCharacter* player) =0; // Pure virtual function for entering location
	virtual void OnExit(PlayerCharacter* player) =0; // Pure virtual function for exiting location
    //virtual int OnEvent(EventFlag& obj); // Pure virtual function for event handling in locations (takes in an EventFlag object) (implement later)
};

