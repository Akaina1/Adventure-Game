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
    std::vector<Room> RoomList;

public:
    virtual std::string GetName() const override;
    virtual std::string GetDescription() const override;
    virtual void OnEnter(PlayerCharacter* player)override;
    virtual void OnExit(PlayerCharacter* player) override;

    void Visit(PlayerCharacter* player);// players can enter the Tavern with this command from anywhere in the game.  Takes in a pointer to the player character. Function should update the player's current location to the Tavern. 
    void TavernMenu(PlayerCharacter& player); // displays the menu of options for the player to choose from while in the Tavern.
    void Rest(PlayerCharacter& player); // players can rest in the Tavern to regain health, will cost gold.
    void Drink(PlayerCharacter& player); // players can drink in the Tavern, will cost gold.
    void ViewNpcs(std::vector<NPC> NPCList); // players can view the NPC's in the Tavern, some NPCs will sell items, others can upgrade gear, etc.
    void TalkToNpc(NPC& npc); // allows player to talk to selected NPC from the list of NPC's in the Tavern.
};

// prototype the main tavern object that will be created when the game starts







