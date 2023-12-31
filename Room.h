#pragma once
#include "Location.h"
#include "Main.h"
#include "CharacterTemplate.h"

class Enemy;

class Room : public Location
{
private:
	std::string Name;
	std::string Description;
	std::vector<std::shared_ptr<Room>> connectedRooms;
	std::vector<std::shared_ptr<Location>> connectedLocations;
	std::deque<std::shared_ptr<CharacterTemplate>> Combatants; // could do the same for NPCs - vector to hold what is in the room

public:
	Room(std::string name, std::string description) : Name(name), Description(description) {}; // room with no enemies
	Room(std::string name, std::string description, std::deque<std::shared_ptr<CharacterTemplate>> combatants) : Name(name), Description(description), Combatants(combatants) {};


	std::string GetName() const { return Name; };
	std::string GetDescription() const { return Description; };
	virtual void OnEnter(std::shared_ptr<PlayerCharacter> player) override;
	virtual void OnExit(std::shared_ptr<PlayerCharacter> player) override;

	//int OnEvent(EventFlag& obj) override;
	virtual size_t GetConnectedRoomsCount() const override { return connectedRooms.size(); };
	virtual size_t GetConnectedLocationsCount() const override { return connectedLocations.size(); };

	virtual std::shared_ptr<Room> GetConnectedRoom(int index) const override;
	virtual std::shared_ptr<Location> GetConnectedLocation(int index) const override;

	virtual void ConnectRoom(std::shared_ptr<Room> room) override { connectedRooms.push_back(room); };
	virtual void ConnectLocation(std::shared_ptr<Location> location)override { connectedLocations.push_back(location); };

	const std::deque<std::shared_ptr<CharacterTemplate>>& GetCombatants() const { return Combatants; };
	void AddEnemy(const std::shared_ptr<CharacterTemplate>&enemy) { this->Combatants.push_back(enemy); };

};
