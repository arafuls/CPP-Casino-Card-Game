// CARD CLASS
// Defines what a card is and maintains its attributes

#pragma once
#include <string>

// Enumerators for card suits and ranks
enum Suit { Spades, Hearts, Diamonds, Clubs };
enum Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 11, Queen = 12, King = 13, Ace = 14 };

class Card
{
	friend class Deck;	// Deck Class needs access to Card Class but not vice versa

public:
	Card();
	Card(const int &suit, const int &rank);
	~Card();

	// Functions
	std::string GetSuit();
	std::string GetRank();
	int GetRankAsInt();

private:
	// Variables
	int suit_;
	int rank_;
};

