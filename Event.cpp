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

void EventUpdate(Event* event)
{
	// Event update will update the event's eventStatus attribute
    // This is used to update the event's status when the player completes an event or starts an event
}

void Event::EventStart(Event& obj)
{
	//EventStart is called by EventTrigger and takes in a event object
	//EventStart will update the event's eventStatus attribute to "Started" with the EventUpdate function
}

void Event::EventComplete(Event& obj)
{
	//EventComplete takes in an event object and updates the event's eventStatus attribute to "Completed" with the EventUpdate function
}

void Event::EventInfo(Event* event)
{
	// EventInfo takes in the event and prints out the event's description attribute or completion attribute
	// This is used to print out the event's information when the player starts an event or completes an event
	// EventInfo is called by EventTrigger and EventComplete, and needs to diferentiate between the two to print out the correct information (description or completion)
}


