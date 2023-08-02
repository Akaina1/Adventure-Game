#include "Event.h"
#include "PlayerCharacter.h"
#include "Item.h"


Event::Event()
{
}

Event::~Event()
{
}

Event::Event(std::string name, int eventId, std::string description, EventStatus eventstatus, 
	std::function<bool()> activationCondition,
	std::function<bool()> completeCondition,
	std::function<bool()> failureCondition)
	: Name (name), EventID (eventId), Description(description), eventStatus (eventstatus), 
		ActivationCondition (activationCondition),
	    CompletionCondition (completeCondition),
		FailureCondition (failureCondition)
{}

void Event::EventHandler(std::shared_ptr<PlayerCharacter> player)
{
	// Event Handler is the checker and updater for events
    // This will be called often by the program to check if an event has been triggered or completed
	// this will need to check all the events in the game to see if any are Active
	// if an event has been triggered, it will call EventStart
    // if an event has been completed, it will call EventComplete
	// if an event has been failed, it will call EventFail

	for (auto& event : player->GetEvents())
	{
		if(event->GetEventStatus() == EventStatus::Inactive && event->ActivationCondition())
		{
			//if event is inactive and activation condition met, trigger event

			event->EventStart(player);
		}
		else if (event->GetEventStatus() == EventStatus::Active)
		{
			if (event->CompletionCondition())
			{
				// event is active and completion condition met, complete event

				event->EventComplete(player);
			}
			else if (event->FailureCondition())
			{
				// event is active and failure condition met, fail the event

				event->EventFail(player);
			}
		}
	}
}

void Event::EventStart(std::shared_ptr<PlayerCharacter> player)
{
	//EventStart is called by EventHandler and takes in a shared pointer to the player
	//EventStart will update the event's EventStatus attribute to "Active" 
	//EventStart will also call EventInfo to display the event info again

	this->eventStatus = EventStatus::Active;
	EventInfo();
}

void Event::EventComplete(std::shared_ptr<PlayerCharacter> player)
{
	//EventStart is called by EventHandler and takes in a shared pointer to the player
	//EventComplete updates the event's eventStatus attribute to "Completed" 
	//EventComplete will also call EventInfo to display the event info again

	this->eventStatus = EventStatus::Complete;
	RewardHandler(player);
}

void Event::EventInfo()
{
	// EventInfo takes in the event and prints out the event's description attribute or completion attribute
	// This is used to print out the event's information when the player starts an event or completes an event
	// EventInfo is called by EventTrigger and EventComplete, and needs to diferentiate between the two to print out the correct information (description or completion)
}

void Event::EventFail(std::shared_ptr<PlayerCharacter> player)
{
	//EventFail is called by EventHandler and takes in a shared pointer to the player
	//EventFail updates the event's eventStatus attribute to "Failed" 
	//EventFail will also call EventInfo to display the event info again

	this->eventStatus = EventStatus::Failed;
	PenaltyHandler(player);
}

void Event::RewardHandler(std::shared_ptr<PlayerCharacter> player)
{
	//RewardHandler is called by EventComplete and takes in a shared pointer to the player
	//RewardHandler will check event ID and give rewards based on the event ID
	//RewardHandler will also call EventInfo to display the event info again

	//if (GetEventID() == 1234) // give rewards out based on EventID
	//{
	//	player->AddItem(DragonSword, 1); // can add anything here
	//	player->AddExperience(1000);
	//	player->AddGold(5000);
	//}


	//EventInfo(); //print event again
}

void Event::PenaltyHandler(std::shared_ptr<PlayerCharacter> player)
{
	// PenaltyHandler is called by EventFail and takes in a shared pointer to the player
	// PenaltyHandler will check event ID and give penalty based on the event ID
	//RewardHandler will also call EventInfo to display the event info again

	//if (GetEventID() == 1234) // give penalty out based on EventID
	//{
	//	player->TakeDamage(20); // can add anything here
	//	player->Perish(); // kill em
	//	player->RemoveExperience(5000);
	//	player->RemoveGold(1000);
	//}

	//EventInfo(); //print event again
}


