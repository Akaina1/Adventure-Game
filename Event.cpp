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

void Event::EventTrigger(PlayerCharacter* player)
{
	// EventTrigger takes in the player character and checks for certain conditions based on EventFlags
	// If the conditions are met, the event is triggered and the EventFlags are updated
	// EventTrigger will call Eventinfo to print out the event's Description attribute
	// EventFlags are used to prevent the same event from triggering multiple times
}

void Event::EventComplete(PlayerCharacter* player)
{
	// EventComplete takes in the player character and checks for certain conditions based on EventFlags
	// EventTrigger will call Eventinfo to print out the event's Completion attribute
    // If the conditions are met, the event is completed and the EventFlags are updated
}

void Event::EventInfo(Event* event)
{
	// EventInfo takes in the event and prints out the event's description attribute or completion attribute
	// This is used to print out the event's information when the player starts an event or completes an event
	// EventInfo is called by EventTrigger and EventComplete, and needs to diferentiate between the two to print out the correct information (description or completion)
}



void Event1::EventTrigger(PlayerCharacter* player)
{

}
