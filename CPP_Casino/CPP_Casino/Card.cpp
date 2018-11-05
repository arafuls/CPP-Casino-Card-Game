#include "Card.h"


Card::Card()
{
	// Card init
	suit_ = NULL;
	rank_ = NULL;
}



// Function:	Card
// Purpose:		Assign card with specific suit and rank
// Parameters:	const int &cardSuit, const int &cardRank
// Returns:		Returns a card with desired parameters
Card::Card(const int &suit, const int &rank)
{
	suit_ = suit;
	rank_ = rank;
}



Card::~Card()
{
}



// Function:	GetSuit
// Purpose:		Gets suit of card
// Parameters:	
// Returns:		Returns a string representing the cards suit
std::string Card::GetSuit()
{
	switch ((Suit)suit_)
	{
	case Spades: return "S";
	case Hearts: return "H";
	case Diamonds: return "D";
	case Clubs: return "C";
	default: throw std::logic_error("Invalid Suit");
	}
}



// Function:	GetRank
// Purpose:		Gets rank of card
// Parameters:	
// Returns:		Returns a string representin the cards rank
std::string Card::GetRank()
{
	switch ((Rank)rank_)
	{
	case Ace: return "A";
	case Two: return "2";
	case Three: return "3";
	case Four: return "4";
	case Five: return "5";
	case Six: return "6";
	case Seven: return "7";
	case Eight: return "8";
	case Nine: return "9";
	case Ten: return "X";
	case Jack: return "J";
	case Queen: return "Q";
	case King: return "K";
	default: throw std::logic_error("Invalid Rank");
	}
}



// Function:	GetRankAsInt
// Purpose:		Converts char rank to int
// Parameters:	
// Returns:		Returns an integer representing the cards rank
int Card::GetRankAsInt()
{
	switch ((Rank)rank_)
	{
	case Two: return 2;
	case Three: return 3;
	case Four: return 4;
	case Five: return 5;
	case Six: return 6;
	case Seven: return 7;
	case Eight: return 8;
	case Nine: return 9;
	case Ten: return 10;
	case Jack: return 11;
	case Queen: return 12;
	case King: return 13;
	case Ace: return 14;
	default: throw std::logic_error("Invalid Rank");
	}
}