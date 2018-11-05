#include "Casino.h"
#include "Serialization.h"



Casino::Casino()
{
}



// Function:	StartMenu
// Purpose:		Displays start menu for user and gets desired action
// Parameters:	
// Returns:		
void Casino::StartMenu()
{
	// Welcome prompt
	std::cout << "   Welcome to Casino!   " << std::endl << std::endl;

	// Ask user for action
	std::cout << " =+=   START MENU   =+= " << std::endl;
	std::cout << "   1: NEW GAME" << std::endl;
	std::cout << "   2: CONTINUE A SAVE" << std::endl;
	std::cout << "   3: QUIT GAME" << std::endl;
	std::cout << " =+=                =+= " << std::endl << std::endl;

	// User input for action
	int input = 0;
	do
	{
		std::cout << "Input: ";
		std::cin >> input;

		// Clear and ignore incorrect entries
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (input < 1 || input > 3);

	Serialization save;
	switch (input)
	{
	case 1: // New game
		StartNewGame();
		break;
	case 2: // Continue a save
		save.ReadSave();
		break;
	case 3: // Exit the game
		exit(EXIT_SUCCESS);
		break;
	}
}



// Function:	StartNewGame
// Purpose:		Starts a new tournament
// Parameters:	
// Returns:		
void Casino::StartNewGame()
{
	tournament.StartRound();
}



Casino::~Casino()
{
}