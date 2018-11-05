// TOURNAMENT CLASS
// This class is responsible for holding the entire instance of the game

#pragma once
#include "Player.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>


class Tournament
{
public:
	// Default constructor
	Tournament();

	void SavedTournament(int sRound, Table sTable, Deck sDeck, Computer sCPU, Human sHuman, Player *sCurrentPlayer, Player *sNextPlayer, int sComputerScore, int sHumanScore);

	// Displays the wins of each player
	void DisplayWins();

	// Start the game
	void StartRound();

	// Coin flip to determine who goes first
	void CoinFlip(Player *&currentPlayer, Player *&nextPlayer);

	// Default destructor
	~Tournament();

private:
	// Round tracker
	int roundCounter;

	// Integers to track scores
	int humanPts;
	int computerPts;

	// Players
	Human humanPlayer;
	Computer computerPlayer;

	// Points to the current and next player
	Player *currentPlayer;
	Player *nextPlayer;
};

