// PLAYER CLASS
// This class determines the properties of all players in the game as they are derived from this class

#pragma once
#include "Table.h"
#include "Card.h"
#include <vector>

class Player
{
public:
	Player();

	// Variables
	std::string name;
	std::vector<Card> myHand;
	std::vector<Card> pile;
	Build myBuild;
	
	// Functions
	virtual void Play(Table &table);	// Virtual play function
	std::vector<Card> GetHand();

protected:
	// Functions
	bool PlayerHasCard(std::string cardName, Card &card);
	bool CheckBuildSum(Card buildCard, std::vector<Card> currentBuildSet, int &buildSum);

	~Player();
private:
};

