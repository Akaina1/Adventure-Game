#include "Room.h"

void Room::OnEnter(PlayerCharacter* player)
{

}
void Room::OnExit(PlayerCharacter* player)
{

}

void Room::ConnectRoom(std::shared_ptr<Room> room) // add a Room to the list of connected Rooms
{
	connectedRooms.push_back(room);
}

void Room::ConnectLocation(std::shared_ptr<Location> location)
{
	connectedLocations.push_back(location);

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