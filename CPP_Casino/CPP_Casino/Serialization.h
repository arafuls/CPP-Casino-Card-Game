// SERIALIZATION CLASS
// This class was made to read and write to and from save files

#pragma once
#include "Tournament.h"

#include <fstream>

class Serialization
{
public:
	Serialization();
	void ReadSave();
	~Serialization();
private:
	// Variables
	Tournament sTournament;

	int sRound;
	Deck sDeck;

	Table sTable;
	std::vector<Card> sTableCards;
	Build tmpBuild;
	std::vector<Build> sAllBuilds;
	
	Computer sComputerPlayer;
	int sComputerScore;
	std::vector<Card> sComputerHand;
	std::vector<Card> sComputerPile;

	Human sHumanPlayer;
	int sHumanScore;
	std::vector<Card> sHumanHand;
	std::vector<Card> sHumanPile;

	Player *sCurrentPlayer;
	Player *sNextPlayer;

	std::stringstream sstream;

	// Functions
	bool ReadFile();
	void RecordTableCards(std::string line);
	void RecordBuildCards(std::string line);
	void RecordDeck(std::string line);
	void RecordPlayerPointers(std::string line);
	void StartTournament();
	Card StrToCard(char suit, char rank);
};

