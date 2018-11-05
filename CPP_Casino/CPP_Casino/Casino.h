// CASINO CLASS
// This class stores the entire instance of the game casino

#pragma once
#include "deck.h"
#include "Tournament.h"

#include <iostream>
#include <sstream>
#include <string>
#include <limits>


class Casino
{
public:
	Casino();

	// Runs when game is booted, asks user for action
	void StartMenu();

	// Initialize new game
	void StartNewGame();

	~Casino();
private:
	// Holds the game's current data
	Tournament tournament;
};

