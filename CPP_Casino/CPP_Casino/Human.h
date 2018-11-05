// HUMAN CLASS
// This class determines the actions of the human player by prompting the user what action
// they would like to perform throughout the game.

#pragma once
#include "Build.h"
#include "Player.h"
#include <algorithm>

class Human :
	public Player
{
public:
	// Functions
	Human();
	void Play(Table &table);
	int ValidInput();

	bool Build(Table &table);
	bool SingleBuild(Table &table);
	bool MultiBuild(Table &table);

	bool Capture(Table &table);
	bool Trail(Table &table);
	bool Help(Table &table);

	bool UserGetCard(Card &tmpDropCard, std::string cardType);
	bool UserGetTableCards(Table table, int totalCards, std::vector<Card> &currentBuildSet);
	int UserGetLooseCards(Table table);

	bool PlayerHasBuilds(Table table);
	~Human();
};

