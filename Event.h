// event abstract class
// all events will inherit from this class
// all events will have an eventID and eventStatus
// eventID will be used to identify the event
// eventStatus will be used to determine if the event is active or not
// eventTrigger will be used to trigger the event
// eventComplete will be used to complete the event
// eventInfo will be used to display the event information
#pragma once
#include "PlayerCharacter.h"
#include "Item.h"
#include "Main.h"
#include "Location.h"
#include "Dungeon.h"
#include "Room.h"

class Item;

class Event
{
private:
	const int eventID {0000}; // unique event ID
	bool eventStatus{ false }; // event status
	std::string Description; // event description gives background information about the event and completion details
	std::string Completion; // event completion gives completion text as well as reward information
	std::map<Item, int> Reward; // event reward stored in a map of items and quantity

public:
	Event();
	~Event();
	virtual void EventStart(Event* obj) = 0;
	virtual void EventComplete(Event* obj) = 0;
	virtual void EventInfo(Event* event) = 0;
	virtual void RewardHandler(Event* event, PlayerCharacter* player) = 0;
	virtual void EventHandler(Event* event, PlayerCharacter* player) = 0;
};



