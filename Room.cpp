#include "Room.h"
#include "Enemy.h"
#include "Combat.h"

void Room::OnEnter(std::shared_ptr<PlayerCharacter> player)
{
	if (!Enemies.empty())
	{
		auto combat = std::make_shared<Combat> (player, Enemies);
		combat->StartCombat();
	}
	else
	{
		std::cout << "There are no enemies in this room, you are safe for now..." << std::endl;
	}
}
void Room::OnExit(std::shared_ptr<PlayerCharacter> player)
{

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