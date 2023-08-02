 //event abstract class
 //all events will inherit from this class
 //all events will have an eventID and eventStatus
 //eventID will be used to identify the event
 //eventStatus will be used to determine if the event is active or not
 //eventTrigger will be used to trigger the event
 //eventComplete will be used to complete the event
 //eventInfo will be used to display the event information
#pragma once

#include "Main.h"

class Item;
class PlayerCharacter;

enum class EventStatus
{
	Active,
	Complete,
	Failed,
	Inactive
};

class Event
{
private:
	std::string Name; // event name
	int EventID {0000}; // unique event ID
	std::string Description; // event description gives background information about the event and completion details

	EventStatus eventStatus; // event status, active, complete, failed, inactive

	std::function<bool(std::shared_ptr<PlayerCharacter>)> ActivationCondition; // checks player for conditions to activate event
	std::function<bool(std::shared_ptr<PlayerCharacter>)> CompletionCondition; // checks player for conditions to complete event
	std::function<bool(std::shared_ptr<PlayerCharacter>)> FailureCondition;    // checks player for conditions to fail event

public:
	Event();
	~Event();
	Event(std::string Name, int eventId, std::string description, EventStatus eventstatus, 
		std::function<bool(std::shared_ptr<PlayerCharacter>)> activationCondition,
		std::function<bool(std::shared_ptr<PlayerCharacter>)> victoryCondition,
		std::function<bool(std::shared_ptr<PlayerCharacter>)> failureCondition);

	virtual void EventStart(std::shared_ptr<PlayerCharacter> player);

	virtual void EventComplete(std::shared_ptr<PlayerCharacter> player);
	virtual void EventFail(std::shared_ptr<PlayerCharacter> player);

	virtual void EventInfo();

	virtual void RewardHandler(std::shared_ptr<PlayerCharacter> player);
	virtual void PenaltyHandler(std::shared_ptr<PlayerCharacter> player);
	virtual void EventHandler(std::shared_ptr<PlayerCharacter> player);

//getters
	int GetEventID() { return EventID; };
	std::string GetDescription() { return Description; };
	EventStatus GetEventStatus() { return eventStatus; };
	std::string GetName() { return Name; };

//setters
	void SetEventID(int eventID) { EventID = eventID; };
	void SetDescription(std::string description) { Description = description; };
};



