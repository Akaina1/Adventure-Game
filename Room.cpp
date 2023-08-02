#include "Room.h"
#include "Enemy.h"
#include "Combat.h"

void Room::OnEnter(std::shared_ptr<PlayerCharacter> player)
{
    std::cout << "Number of Combatants: " << Combatants.size() << std::endl;

    bool hasEnemies = std::any_of(Combatants.begin(), Combatants.end(), [](std::shared_ptr<CharacterTemplate> combatant) 
        { 
            return std::dynamic_pointer_cast<Enemy>(combatant) && combatant->GetCurrentHealth() > 0;
        });

    if (hasEnemies)
    {
        std::cout << "Combatants' names: " << std::endl;
        for (const auto& combatant : Combatants) {
            if (combatant) {
                std::cout << combatant->GetName() << std::endl;
            }
            else {
                std::cout << "Invalid combatant found!" << std::endl;
            }
        }
        std::cout << "Number of Combatants: " << Combatants.size() << std::endl;
        Combatants.push_back(player);
        auto combat = std::make_shared<Combat>(player, Combatants);
        combat->InitializeCombat();
        combat->StartCombat();
        player->ChooseMove();
    }
    else
    {
        std::cout << "There are no enemies in this room, you are safe for now..." << std::endl;
        player->ChooseMove();
    }
}

void Room::OnExit(std::shared_ptr<PlayerCharacter> player)
{
    Combatants.erase(std::remove_if(Combatants.begin(), Combatants.end(), [](std::shared_ptr<CharacterTemplate> combatant) {
        return std::dynamic_pointer_cast<Enemy>(combatant) != nullptr && combatant->GetCurrentHealth() == 0;
        }), Combatants.end());
}

std::shared_ptr<Room> Room::GetConnectedRoom(int index) const
{
	if (index < 0 || index >= connectedRooms.size())
	{
		throw std::out_of_range("ERROR - Room::GetConnectedRoom() - INDEX IS OUT OF RANGE");
	}

	return connectedRooms[index];
}

std::shared_ptr<Location> Room::GetConnectedLocation(int index) const
{
	if (index < 0 || index >= connectedLocations.size())
	{
		throw std::out_of_range("ERROR - Room::GetConnectedLocation() - INDEX IS OUT OF RANGE");
	}

	return connectedLocations[index];
}
