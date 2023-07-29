#pragma once
#include "Location.h"
#include "Main.h"
#include "CharacterTemplate.h"
#include "PlayerCharacter.h"
#include "MainMenu.h"


class Dungeon : public Location
{
private:
	std::string Name; // Name of location
	std::string Description; // Description of location
	std::vector<std::shared_ptr<Room>> connectedRooms;
	std::vector<std::shared_ptr<Location>> connectedLocations;
	std::shared_ptr<PlayerCharacter> Player;

public:
	Dungeon(std::string name, std::string description, std::shared_ptr<PlayerCharacter> player) : Name(name), Description(description), Player{ player } {};

	std::string GetName() const { return Name; }; // function for getting name of location
	std::string GetDescription() const { return Description; }; // function for getting description of location
	virtual void OnEnter(std::shared_ptr<PlayerCharacter> player) override; // function for entering location
	virtual void OnExit(std::shared_ptr<PlayerCharacter> player) override; //function for exiting location

	virtual size_t GetConnectedRoomsCount() const override { return connectedRooms.size(); };
	virtual size_t GetConnectedLocationsCount() const override { return connectedLocations.size(); };

	virtual std::shared_ptr<Room> GetConnectedRoom(int index) const override;
	virtual std::shared_ptr<Location> GetConnectedLocation(int index) const override;

	virtual void ConnectRoom(std::shared_ptr<Room> room) override { connectedRooms.push_back(room); };
	virtual void ConnectLocation(std::shared_ptr<Location> location)override { connectedLocations.push_back(location); };
};

