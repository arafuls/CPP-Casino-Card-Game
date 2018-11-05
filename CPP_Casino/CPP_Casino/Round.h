// ROUND CLASS
// This class controls everything in the rounds jurisdiction, such as how the round starts, with what settings it starts, etc

#pragma once
#include "deck.h"
#include "Table.h"

class Round
{
public:
	Round();

	void ShowCards(Player *player1, Player *player2, Table table);
	void PlayRound(int roundCounter, Player *&cPlayer, Player *&nPlayer, int &humanPts, int &computerPts);	// Plays the rounds
	void ResumeRound(int roundCounter, Player *&cPlayer, Player *&nPlayer, int &humanPts, int &computerPts, Table &sTable, Deck &sDeck);	// Plays from saved game
	void SwitchPlayers(Player *&player1, Player *&player2);
	int FindBonusCards(Player *player, int &spades);

	~Round();
private:
	// The game's current deck
	Deck deck;
};

