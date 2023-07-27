#pragma once
#include "Location.h"
#include "Main.h"

class Room : public Location
{
private:
	std::string name;
    std::string description;
	std::vector<std::shared_ptr<Room>> connectedRooms;
	std::vector<std::shared_ptr<Location>> connectedLocations;

public:
	Room(std::string name, std::string description) : name(name), description(description) {};

	std::string getName() const { return name; };
	std::string getDescription() const { return description; };
	void OnEnter(PlayerCharacter* player) override;
	void OnExit(PlayerCharacter* player) override;

	//int OnEvent(EventFlag& obj) override;
	virtual int GetConnectedRoomsCount() const override { return connectedRooms.size(); };
	virtual int GetConnectedLocationsCount() const override { return connectedLocations.size(); };

	virtual std::shared_ptr<Room> GetConnectedRoom(int index) const override; 
	virtual std::shared_ptr<Location> GetConnectedLocation(int index) const override;

	virtual void ConnectRoom(std::shared_ptr<Room> room);
	virtual void ConnectLocation(std::shared_ptr<Location> location);	
};

