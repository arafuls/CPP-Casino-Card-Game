#include "Round.h"


Round::Round()
{
	deck.CreateDeck();
}



// Function:	Show cards
// Purpose:		Reveals everyones cards
// Parameters:	(Player *player1, Player *player2, Table table
// Returns:		
void Round::ShowCards(Player *player1, Player *player2, Table table)
{
	table.PrintHand(player1->GetHand(), player1->name);
	table.PrintTable();
	deck.PrintDeck();
	table.PrintHand(player2->GetHand(), player2->name);
}



// Function:	PlayRound
// Purpose:		Starts a new round
// Parameters:	int roundCounter, Player *&player1, Player *&player2, int &humanPts, int &computerPts
// Returns:		
//		ALGORITHM
// 1.) Init table and clear piles and hands
// 2.) Deal cards to human, then CPU, then table
// 3.) Keep playing a new round until both players have an empty hand and the deck is empty
// 3a.)		If currentPlayers hand is empty, deal cards
// 3b.)		Play the round
// 4.) Give remaining table cards to last player after round is over
// 5.) Tally scores
// 6.) Update points
void Round::PlayRound(int roundCounter, Player *&player1, Player *&player2, int &humanPts, int &computerPts)
{
	// The game's current table
	Table table;

	// Update and shuffle
	deck.CreateDeck();

	// Clear player piles & hands
	player1->pile.clear();
	player1->myHand.clear();
	player2->pile.clear();
	player2->myHand.clear();

	// Deal cards to human, then CPU, then table
	if (player1->name == "Human")
	{
		for (int i = 0; i < 4; i++)
		{
			deck.DealCards(player1);
			deck.DealCards(player2);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			deck.DealCards(player2);
			deck.DealCards(player1);
		}
	}
	deck.DealCards(table);

	int count = 1;

	// Keep playing till round end condition
	while (!deck.IsEmpty() || player1->myHand.size() != 0 || player2->myHand.size() != 0 )
	{
		std::cout << "=+= ROUND " << roundCounter << " =+=" << std::endl << std::endl;

		// Deal cards
		if (player1->myHand.size() < 1)
		{
			deck.DealCards(player1);
		}

		std::cout << "TURN " << count << ": " << player1->name << "'s turn!" << std::endl;
		std::cout << "= = = = = = = = = = = = = =" << std::endl;
		ShowCards(player1, player2, table);	// Display cards 
		player1->Play(table);				// Player's turn
		SwitchPlayers(player1, player2);	// End of player's turn
		count++;

		for (int i = 0; i < 6; i++) { std::cout << std::endl; }
	}

	// Give remaining cards to last player and erase from table
	if (table.tableHand.size() > 0)
	{
		for (unsigned i = 0; i < table.tableHand.size(); i++)
		{
			// Give cards to player 2 (because switched players above)
			player2->myHand.push_back(table.tableHand[i]);
			table.tableHand.erase(table.tableHand.begin() + i);
		}
	}

	// Tally scores
	int player1Pts = 0, player2Pts = 0;
	std::cout << "Tallying scores for the round. . ." << std::endl << std::endl;

	// Who has the most cards?
	if (player1->pile.size() == player2->pile.size())
	{
		std::cout << player1->pile.size() << " to " << player2->pile.size() << ". You both had the same amount of cards, no points awarded to either player." << std::endl << std::endl;
	}
	else if (player1->pile.size() > player2->pile.size())
	{
		std::cout << player1->pile.size() << " to " << player2->pile.size() << ". ";
		std::cout << player1->name << " has the majority of the cards, +3 points to them!" << std::endl << std::endl;
		player1Pts += 3;
	}
	else
	{
		std::cout << player1->pile.size() << " to " << player2->pile.size() << ". ";
		std::cout << player2->name << " has the majority of the cards, +3 points to them!" << std::endl << std::endl;
		player2Pts += 3;
	}

	// Find bonus cards
	int p1Spades, p2Spades;
	player1Pts += FindBonusCards(player1, p1Spades);
	player2Pts += FindBonusCards(player2, p2Spades);

	if (p1Spades == p2Spades) { std::cout << "Both players have " << p1Spades << " Spades, no points awarded!" << std::endl << std::endl; }
	else if (p1Spades > p2Spades)
	{
		std::cout << p1Spades << " to " << p2Spades << ". ";
		std::cout << player1->name << " has the majority of the Spades, +1 point to them!" << std::endl << std::endl;
		player1Pts++;
	}
	else
	{
		std::cout << p1Spades << " to " << p2Spades << ". ";
		std::cout << player2->name << " has the majority of the Spades, +1 point to them!" << std::endl << std::endl;
		player2Pts++;
	}

	std::cout << player1->name << " earned " << player1Pts << " that round!" << std::endl;
	std::cout << player2->name << " earned " << player2Pts << " that round!" << std::endl;

	// Update points
	if (player1->name == "Human")
	{
		humanPts += player1Pts;
		computerPts += player2Pts;
	}
	else
	{
		humanPts += player2Pts;
		computerPts += player1Pts;
	}
}



// Function:	ResumeRound
// Purpose:		Start a new round based on the input from the save file
// Parameters:	int roundCounter, Player *&player1, Player *&player2, int &humanPts, int &computerPts, Table &table, Deck &deck
// Returns:		
//		ALGORITHM
// 1.) Mimic of PlayRound only without initialization preparations
void Round::ResumeRound(int roundCounter, Player *&player1, Player *&player2, int &humanPts, int &computerPts, Table &sTable, Deck &sDeck)
{
	// The game's current table
	Table table = sTable;
	deck = sDeck;

	int count = 1;

	// Keep playing till round end condition
	while (!deck.IsEmpty() || player1->myHand.size() != 0 || player2->myHand.size() != 0)
	{
		std::cout << "=+= ROUND " << roundCounter << " =+=" << std::endl << std::endl;

		// Deal cards
		if (player1->myHand.size() < 1 && !deck.IsEmpty())
		{
			while (player1->myHand.size() != 4 && !deck.IsEmpty())
			{
				deck.DealCards(player1);
			}
		}

		std::cout << "TURN " << count << ": " << player1->name << "'s turn!" << std::endl;
		std::cout << "= = = = = = = = = = = = = =" << std::endl;
		ShowCards(player1, player2, table);	// Display cards 
		player1->Play(table);				// Player's turn
		SwitchPlayers(player1, player2);	// End of player's turn
		count++;

		for (int i = 0; i < 6; i++) { std::cout << std::endl; }
	}

	// Give remaining cards to last player and erase from table
	if (table.tableHand.size() > 0)
	{
		for (unsigned i = 0; i < table.tableHand.size(); i++)
		{
			// Give cards to player 2 (because switched players above)
			player2->myHand.push_back(table.tableHand[i]);
			table.tableHand.erase(table.tableHand.begin() + i);
		}
	}

	// Tally scores
	int player1Pts = 0, player2Pts = 0;
	std::cout << "Tallying scores for the round. . ." << std::endl << std::endl;

	// Who has the most cards?
	if (player1->pile.size() == player2->pile.size())
	{
		std::cout << player1->pile.size() << " to " << player2->pile.size() << ". You both had the same amount of cards, no points awarded to either player." << std::endl << std::endl;
	}
	else if (player1->pile.size() > player2->pile.size())
	{
		std::cout << player1->pile.size() << " to " << player2->pile.size() << ". ";
		std::cout << player1->name << " has the majority of the cards, +3 points to them!" << std::endl << std::endl;
		player1Pts += 3;
	}
	else
	{
		std::cout << player1->pile.size() << " to " << player2->pile.size() << ". ";
		std::cout << player2->name << " has the majority of the cards, +3 points to them!" << std::endl << std::endl;
		player2Pts += 3;
	}

	// Find bonus cards
	int p1Spades, p2Spades;
	player1Pts += FindBonusCards(player1, p1Spades);
	player2Pts += FindBonusCards(player2, p2Spades);

	if (p1Spades == p2Spades) { std::cout << "Both players have " << p1Spades << " Spades, no points awarded!" << std::endl << std::endl; }
	else if (p1Spades > p2Spades)
	{
		std::cout << p1Spades << " to " << p2Spades << ". ";
		std::cout << player1->name << " has the majority of the Spades, +1 point to them!" << std::endl << std::endl;
		player1Pts++;
	}
	else
	{
		std::cout << p1Spades << " to " << p2Spades << ". ";
		std::cout << player2->name << " has the majority of the Spades, +1 point to them!" << std::endl << std::endl;
		player2Pts++;
	}

	std::cout << player1->name << " earned " << player1Pts << " points that round!" << std::endl;
	std::cout << player2->name << " earned " << player2Pts << " points that round!" << std::endl;

	// Update points
	if (player1->name == "Human")
	{
		humanPts += player1Pts;
		computerPts += player2Pts;
	}
	else
	{
		humanPts += player2Pts;
		computerPts += player1Pts;
	}
}

void Round::SwitchPlayers(Player *&player1, Player *&player2)
{
	Player *tmp;
	tmp = player1;
	player1 = player2;
	player2 = tmp;
}



// Function:	FindBonusCards
// Purpose:		Tallies the score for a player based off their hand
// Parameters:	Player *player, int &spades
// Returns:		Returns an integer representing the number of points tallied for this player,
//				passed integer spades is updated with amount of spades the player owned
//		ALGORITHM
// 1.) For each card in player's pile
// 1a.)		Display the card
// 1b.)		If card is a Spade, inc spade count by 1
// 1c.)		If card is an Ace, inc point count by 1
// 1d.)		If card is 2S, inc point count by 1
// 1e.)		If card is XD, inc point count by 2
// 2.)	Assign spade count, return tallied points
int Round::FindBonusCards(Player *player, int &spades)
{
	int bonus = 0;
	std::cout << player->name << "'s pile: ";
	for (unsigned i = 0; i < player->pile.size(); i++)
	{
		std::cout << player->pile[i].GetRank() + player->pile[i].GetSuit() << " ";
	}
	std::cout << std::endl;

	int playerSpadesCount = 0;
	for (unsigned i = 0; i < player->pile.size(); i++)
	{
		if (player->pile[i].GetSuit() == "S") 
		{
			playerSpadesCount++;
		}

		if (player->pile[i].GetRankAsInt() == 14)
		{
			std::cout << player->name << " has an Ace, +1 point!" << std::endl;
			bonus++;
		}
		else if (player->pile[i].GetRankAsInt() == 2 && player->pile[i].GetSuit() == "S")
		{
			std::cout << player->name << " has the 2 of Spades, +1 point!" << std::endl;
			bonus++;
		}
		else if (player->pile[i].GetRankAsInt() == 10 && player->pile[i].GetSuit() == "D")
		{
			std::cout << player->name << " has the 10 of Diamonds, +2 point!" << std::endl;
			bonus++;
		}
	}

	spades = playerSpadesCount;
	return bonus;
}

Round::~Round()
{
}