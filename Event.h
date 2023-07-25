// event abstract class
// all events will inherit from this class
// all events will have an eventID and eventStatus
// eventID will be used to identify the event
// eventStatus will be used to determine if the event is active or not
// eventTrigger will be used to trigger the event
// eventComplete will be used to complete the event
// eventInfo will be used to display the event information
// PrintEvent will be used to display the event information in a formatted way

#pragma once
class Event
{
private:
	int eventID;
    bool eventStatus;
public:
	Event();
	~Event();
	virtual void EventTrigger(PlayerCharacter* player) = 0;
	virtual void EventComplete(PlayerCharacter* player) = 0;
	virtual void EventInfo() = 0;
	virtual void PrintEvent() = 0;
};

