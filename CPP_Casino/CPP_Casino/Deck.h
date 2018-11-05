// DECK CLASS
// This class is responsible or creating, shuffling, and dealing cards to players (managing the deck)

#pragma once
#include "Card.h"
#include "Table.h"
#include "Player.h"
#include <vector>
#include <algorithm>	// Pesudo-random shuffling
#include <random>		// Pesudo-random shuffling
#include <time.h>
#include <iostream>

class Deck
{
public:
	Deck();
	~Deck();
	void CreateDeck();
	void PrintDeck();
	void Shuffle();
	void DealCards(Player *&player);
	void DealCards(Table &table);
	bool IsEmpty();
	void SetCustomDeck(std::vector<Card> customDeck);

private:
	std::vector<Card> deck;
};
