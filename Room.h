#pragma once
#include "Location.h"
#include "Main.h"

class Room : public Location
{
private:
	std::string Name;
    std::string Description;
	std::vector<std::shared_ptr<Room>> connectedRooms;
	std::vector<std::shared_ptr<Location>> connectedLocations;

public:
	Room(std::string name, std::string description) : Name(name), Description(description) {};

	std::string GetName() const { return Name; };
	std::string GetDescription() const { return Description; };
	virtual void OnEnter(PlayerCharacter* player) override;
	virtual void OnExit(PlayerCharacter* player) override;

	//int OnEvent(EventFlag& obj) override;
	virtual size_t GetConnectedRoomsCount() const override { return connectedRooms.size(); };
	virtual size_t GetConnectedLocationsCount() const override { return connectedLocations.size(); };

	virtual std::shared_ptr<Room> GetConnectedRoom(int index) const override; 
	virtual std::shared_ptr<Location> GetConnectedLocation(int index) const override;

	virtual void ConnectRoom(std::shared_ptr<Room> room) override { connectedRooms.push_back(room); };
	virtual void ConnectLocation(std::shared_ptr<Location> location)override { connectedLocations.push_back(location); };
};

