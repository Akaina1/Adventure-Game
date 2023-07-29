#include "Dungeon.h"


void Dungeon::OnEnter(std::shared_ptr<PlayerCharacter> player) // function for entering location
{
	HWND console = GetConsoleWindow(); // get console window
	RECT ConsoleRect; // create a rectangle for the console window
	GetWindowRect(console, &ConsoleRect); // get the console window rectangle
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 385, 900, TRUE); // set console window size

	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "YOU HAVE ENTERED THE DUNGEON PREPARE TO PERISH" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	Player->ChooseMove();
}
void Dungeon::OnExit(std::shared_ptr<PlayerCharacter> player) // function for exiting location;
{
	std::cout << "YOU HAVE LEFT THE DUNGEON..." << std::endl;

}


std::shared_ptr<Room> Dungeon::GetConnectedRoom(int index) const
{
	if (index < 0 || index >= connectedRooms.size())
	{
		throw std::out_of_range("ERROR - Room::GetConnectedRoom() - INDEX IS OUT OF RANGE");
	}

	return connectedRooms[index];
}

std::shared_ptr<Location> Dungeon::GetConnectedLocation(int index) const
{
	if (index < 0 || index >= connectedLocations.size())
	{
		throw std::out_of_range("ERROR - Room::GetConnectedLocation() - INDEX IS OUT OF RANGE");
	}

	return connectedLocations[index];
}
