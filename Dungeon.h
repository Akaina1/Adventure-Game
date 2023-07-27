#pragma once
#include "Location.h"
#include "Room.h"
#include "PlayerCharacter.h"

class Dungeon : public Location
{
private:
	std::string name; // Name of location
	std::string description; // Description of location
	std::vector<std::shared_ptr<Room>> connectedRooms;
	std::vector<std::shared_ptr<Location>> connectedLocations;

public:
	virtual std::string GetName() const = 0; // Pure virtual function for getting name of location
	virtual std::string GetDescription() const = 0; // Pure virtual function for getting description of location

	virtual void OnEnter(PlayerCharacter* player) = 0; // Pure virtual function for entering location
	virtual void OnExit(PlayerCharacter* player) = 0; // Pure virtual function for exiting location

	virtual int GetConnectedRoomsCount()const { return false; }; // Pure virtual function for getting number of connected rooms
	virtual int GetConnectedLocationsCount()const { return false; }; // Pure virtual function for getting number of connected locations

	virtual std::shared_ptr<Room> GetConnectedRoom(int index) const { return nullptr; };
	virtual std::shared_ptr<Location> GetConnectedLocation(int index) const { return nullptr; }; // Pure virtual function for getting connected location

	virtual void ConnectRoom(std::shared_ptr<Room> room) { };
	virtual void ConnectLocation(std::shared_ptr<Location> location) { };

	//virtual int OnEvent(EventFlag& obj); // Pure virtual function for event handling in locations (takes in an EventFlag object) (implement later)
};

