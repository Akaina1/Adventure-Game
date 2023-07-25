//definition of the Tavern class
#pragma once
#include "Room.h"
#include "NPC.h"
#include "PlayerCharacter.h"

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
    virtual void OnEnter() override;
    virtual void OnExit() override;

    void Visit(PlayerCharacter& Player); // players can enter the Tavern with this command from anywhere in the game.  Takes in a pointer to the player character. Function should update the player's current location to the Tavern. 
    void TavernMenu(); // displays the menu of options for the player to choose from while in the Tavern.
    void Rest(PlayerCharacter& Player,int PlayerGold); // players can rest in the Tavern to regain health, will cost gold.
    void Drink(PlayerCharacter& Player, int PlayerGold); // players can drink in the Tavern, will cost gold.
    void ViewNpcs(std::vector<NPC> NPCList); // players can view the NPC's in the Tavern, some NPCs will sell items, others can upgrade gear, etc.
    void TalkToNpc(NPC& npc); // allows player to talk to selected NPC from the list of NPC's in the Tavern.
};



// prototype the main tavern object that will be created when the game starts

Tavern TheTavern;




