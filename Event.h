// event abstract class
// all events will inherit from this class
// all events will have an eventID and eventStatus
// eventID will be used to identify the event
// eventStatus will be used to determine if the event is active or not
// eventTrigger will be used to trigger the event
// eventComplete will be used to complete the event
// eventInfo will be used to display the event information

#include "PlayerCharacter.h"

#pragma once
class Event
{
private:
	const int eventID {0};
	bool eventStatus{ false };
	std::string Description;
	std::string Completion;

public:
	Event();
	~Event();
	virtual void EventTrigger(PlayerCharacter* player) = 0;
	virtual void EventComplete(PlayerCharacter* player) = 0;
	virtual void EventInfo(Event* event) = 0;
};


// event 1
// event 1 will be a simple event to test the event system

class Event1 : public Event
{
private:
	const int eventID{ 0001 };
	bool eventStatus{ false };
	std::string Description{ "You have found a chest" };
	std::string Completion{ "You have opened the chest" };
public:
	Event1();
	~Event1();
	virtual void EventTrigger(PlayerCharacter* player) override;
	virtual void EventComplete(PlayerCharacter* player) override;
	virtual void EventInfo(Event* event) override;
	



};
