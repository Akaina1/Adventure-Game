//definition of the Tavern class
#pragma once
#include "PlayerCharacter.h"
#include "NPC.h"
#include "Room.h"
#include "Location.h"
#include "Main.h"
#include "Item.h"

class Tavern : public Location
{
private:
	std::string Name {"The Tavern"};
    std::string Description {"A Place to Rest, Relax, Drink and forget about the monsters below us..."};
    std::vector<NPC> NPCList;
    std::vector<std::shared_ptr<Room>> connectedRooms;
    std::vector<std::shared_ptr<Location >> connectedLocations;
    std::shared_ptr<Location> dungeonEntrance;

public:
    virtual std::string GetName() const override;
    virtual std::string GetDescription() const override;

    virtual void OnEnter(PlayerCharacter* player)override;
    virtual void OnExit(PlayerCharacter* player) override;

    void TavernMenu(PlayerCharacter& player); // displays the menu of options for the player to choose from while in the Tavern.
    void Rest(PlayerCharacter& player); // players can rest in the Tavern to regain health, will cost gold.
    void Drink(PlayerCharacter& player); // players can drink in the Tavern, will cost gold.
    void ViewNpcs(std::vector<NPC> NPCList); // players can view the NPC's in the Tavern, some NPCs will sell items, others can upgrade gear, etc.
    void TalkToNpc(NPC& npc); // allows player to talk to selected NPC from the list of NPC's in the Tavern.

    virtual int GetConnectedRoomsCount() const override { return connectedRooms.size(); };
    virtual int GetConnectedLocationsCount() const override { return connectedLocations.size(); };

    virtual std::shared_ptr<Room> GetConnectedRoom(int index) const override;
    virtual std::shared_ptr<Location> GetConnectedLocation(int index) const override;

    virtual void ConnectRoom(std::shared_ptr<Room> room) override { connectedRooms.push_back(room); };
    virtual void ConnectLocation(std::shared_ptr<Location> location) override { connectedLocations.push_back(location); };

    void SetDungeonEntrace(std::shared_ptr<Location> dungeon) { dungeonEntrance = dungeon; };
    std::shared_ptr<Location> GetDungeonEntrance() { return dungeonEntrance; };
};









