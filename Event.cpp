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
	// EventFlags are used to prevent the same event from triggering multiple times
}

void Event::EventComplete(PlayerCharacter* player)
{
}
