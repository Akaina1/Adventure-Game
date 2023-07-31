//// main file to hold all events definitions
//#pragma once
//#include "Main.h"
//#include "PlayerCharacter.h"
//#include "Event.h"
//
//// event 1
//// event 1 will be a simple event to test the event system
//
//class Event1 : public Event
//{
//private:
//	const int eventID{ 0001 };
//	bool eventStatus{ false };
//	std::string Description{ "You need to collect an apple" };
//	std::string Completion{ "You found an apple!" };
//public:
//	Event1();
//	~Event1();
//	virtual void EventStart(Event* obj) override;
//	virtual void EventComplete(Event* obj) override;
//	virtual void EventInfo(Event* event) override;
//	virtual void RewardHandler(Event* event, PlayerCharacter* player) = 0;
//	virtual void EventHandler(Event* event, PlayerCharacter* player) = 0;
//};
//
//class Event2 : public Event
//{
//private:
//	const int eventID{ 0002 };
//	bool eventStatus{ false };
//	std::string Description{ "You need to defeat 5 goblins" };
//	std::string Completion{ "wow good job!" };
//public:
//	Event2();
//	~Event2();
//	virtual void EventStart(Event* obj) override;
//	virtual void EventComplete(Event* obj) override;
//	virtual void EventInfo(Event* event) override;
//	virtual void RewardHandler(Event* event, PlayerCharacter* player) = 0;
//	virtual void EventHandler(Event* event, PlayerCharacter* player) = 0;
//};
//
//class Event3 : public Event
//{
//private:
//	const int eventID{ 0003 };
//	bool eventStatus{ false };
//	std::string Description{ "You need to collect 5 iron" };
//	std::string Completion{ "Thanks! Here's something!" };
//public:
//	Event3();
//	~Event3();
//	virtual void EventStart(Event* obj) override;
//	virtual void EventComplete(Event* obj) override;
//	virtual void EventInfo(Event* event) override;
//	virtual void RewardHandler(Event* event, PlayerCharacter* player) = 0;
//	virtual void EventHandler(Event* event, PlayerCharacter* player) = 0;
//};
//
//class Event4 : public Event
//{
//private:
//	const int eventID{ 0004 };
//	bool eventStatus{ false };
//	std::string Description{ "You need to go to Cave 2!" };
//	std::string Completion{ "It's dark down here..." };
//public:
//	Event4();
//	~Event4();
//	virtual void EventStart(Event* obj) override;
//	virtual void EventComplete(Event* obj) override;
//	virtual void EventInfo(Event* event) override;
//	virtual void RewardHandler(Event* event, PlayerCharacter* player) = 0;
//	virtual void EventHandler(Event* event, PlayerCharacter* player) = 0;
//};
//
//class Event5 : public Event
//{
//private:
//	const int eventID{ 0005 };
//	bool eventStatus{ false };
//	std::string Description{ "You should go kill the Boss" };
//	std::string Completion{ "Incredible!" };
//public:
//	Event5();
//	~Event5();
//	virtual void EventStart(Event* obj) override;
//	virtual void EventComplete(Event* obj) override;
//	virtual void EventInfo(Event* event) override;
//	virtual void RewardHandler(Event* event, PlayerCharacter* player) = 0;
//	virtual void EventHandler(Event* event, PlayerCharacter* player) = 0;
//};