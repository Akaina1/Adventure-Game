#include "Event.h"
#include "PlayerCharacter.h"
#include "Location.h"
#include "Dungeon.h"
#include "Room.h"

Event::Event()
{
}

Event::~Event()
{
}

void EventHandler(Event* event, PlayerCharacter* player)
{
	// Event Handler is the checker and updater for events
    // This will be called often by the program to check if an event has been triggered or completed
	// this will need to check all the events in the game to see if any have been triggered or completed
	// if an event has been triggered, it will call EventStart
    // if an event has been completed, it will call EventComplete

}

void Event::EventStart(Event* event)
{
	//EventStart is called by EventHandler and takes in a event object
	//EventStart will update the event's eventStatus attribute to "Started" with the EventUpdate function
	//EventStart will also call EventInfo to print out the event's description attribute
}

void Event::EventComplete(Event* event)
{
	//EventStart is called by EventHandler and takes in a event object
	//EventComplete takes in an event object and updates the event's eventStatus attribute to "Completed" with the EventUpdate function
	//EventComplete will also call EventInfo to print out the event's completion attribute
}

void Event::EventInfo(Event* event)
{
	// EventInfo takes in the event and prints out the event's description attribute or completion attribute
	// This is used to print out the event's information when the player starts an event or completes an event
	// EventInfo is called by EventTrigger and EventComplete, and needs to diferentiate between the two to print out the correct information (description or completion)
}


