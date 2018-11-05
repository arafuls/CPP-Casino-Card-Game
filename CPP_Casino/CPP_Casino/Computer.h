// COMPUTER CLASS
// This class is responsible for how the computer AI plays during its turn

#pragma once
#include "Player.h"

class Computer :
	public Player
{
public:
	Computer();

	void Play(Table &table);
	bool AutoBuild(Table &table);
	bool AutoCapture(Table &table);
	void AutoTrail(Table &table);
	std::vector<Card> FindBuildCards(Card buildCard, Card dropCard, std::vector<Card> setOfCards);

	~Computer();
};

