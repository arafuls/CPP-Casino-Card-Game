#include "deck.h"


Deck::Deck()
{
	// Create a new deck and shuffle it upon construction
	CreateDeck();
}


Deck::~Deck()
{
}



// Function:	CreateDeck
// Purpose:		Genereates a new deck and shuffles it
// Parameters:	
// Returns:		
void Deck::CreateDeck()
{
	// Clear the deck if not already
	deck.clear();

	// Iterating through each suit
	for (int i = 0; i <= 3; i++) {
		// Iterating through each rank
		for (int j = 2; j <= 14; j++) {
			Card card(i, j);		// Create the card
			deck.push_back(card);	// Append to the end of the vector
		}
	}

	// Shuffle the deck
	Shuffle();
}



// Function:	PrintDeck
// Purpose:		For debugging purposes, displays the deck
// Parameters:	
// Returns:		
void Deck::PrintDeck()
{
	//std::cout << "Current Deck " << std::endl;
	int count = 0;

	// Iterate through all cards in the deck
	std::cout << "Deck" << std::endl;
	for (int i = 0; i < (int)deck.size(); i++)
	{
		// Print the card's suit and rank
		std::cout << deck[i].GetSuit();
		std::cout << deck[i].GetRank();
		std::cout << " ";
		count++;

		// New line for each suit
		if (count == 13) { std::cout << std::endl; count = 0; }
	}
	std::cout << std::endl << std::endl;
}



// Function:	Shuffle
// Purpose:		Pseudo-randomly shuffles the deck
// Parameters:	
// Returns:		
void Deck::Shuffle()
{
	srand(static_cast<unsigned int>(time(NULL)));
	std::random_shuffle(deck.begin(), deck.end());
}



// Function:	DealCards
// Purpose:		Deals cards to the player
// Parameters:	Player *&player
// Returns:		
void Deck::DealCards(Player *&player)
{
	// Append first card to players hand, then erase the same card from deck
	player->myHand.push_back(deck.front());
	deck.erase(deck.begin() + 0);
}



// Function:	DealCards					
// Purpose:		Deals 4 cards to the table
// Parameters:	Table *&table				
// Returns:								
void Deck::DealCards(Table &table)
{
	// Deal 4 cards to table
	for (int i = 0; i < 4; i++)
	{
		// Append first card to table then erase from deck
		table.tableHand.push_back(deck.front());
		deck.erase(deck.begin() + 0);
	}
}



// Function:	IsEmpty
// Purpose:		Check if the deck is empty or not
// Parameters:	
// Returns:		Returns a bool representing if the deck is empty or not
bool Deck::IsEmpty()
{
	if (deck.size() == 0 || deck.size() == NULL)
	{
		return true;
	}
	return false;
}



// Function:	SetCustomDeck
// Purpose:		Used to set custom deck from serialization
// Parameters:	vector<Card> customDeck
// Returns:		
void Deck::SetCustomDeck(std::vector<Card> customDeck)
{
	deck.clear();

	for (unsigned i = 0; i < customDeck.size(); i++)
	{
		deck.push_back(customDeck[i]);
	}
}
