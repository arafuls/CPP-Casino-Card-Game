#include "Serialization.h"
#include <algorithm>

// Function:	Serialization
// Purpose:		Initalizes class data members upon construction
// Parameters:	
// Returns:		
Serialization::Serialization()
{
	// Not mentions class vars are declared in their respective constuctors
	sRound = NULL;
	sCurrentPlayer = NULL;
	sNextPlayer = NULL;
}



// Function:	ReadSave
// Purpose:		Starts the new tournament from save file if said file was formatted properly.
// Parameters:	
// Returns:		
void Serialization::ReadSave()
{
	if (ReadFile())
	{
		StartTournament();
	}
}



bool Serialization::ReadFile()
{
	static std::string filename;
	filename.clear();

	// Get filename from user
	while (filename.empty())
	{
		std::cout << std::endl;
		std::cout << "Enter savefile name including extension (ie. 'savefile.txt')." << std::endl;
		std::cout << "Save File: ";
		std::getline(std::cin, filename);
	}

	// Open file for reading
	std::ifstream fs_file;
	fs_file.open(filename);

	// If file is not open
	if (fs_file.is_open() == false)
	{
		std::cout << "Could not open file, make sure the filename is not mispelt!" << std::endl << std::endl;
		return false;
	}

	// Round Data
	int roundScore = 0;

	// Tmp Vars for Data
	std::istringstream ss;
	char scoreChar;
	std::string scoreString;
	int scoreInt;
	std::string tmpCardString;

	// CPU Data
	int cScore = 0;
	std::string cHandString;
	std::vector<Card> cHand;
	std::string cPileString;
	std::vector<Card> cPile;

	// Player Data
	int pScore = 0;
	std::string pHandString;
	std::vector<Card> pHand;
	std::string pPileString;
	std::vector<Card> pPile;

	// Board Data
	std::vector<Card> buildCards;
	std::vector<Card> currDeck;

	// Player Pointer Data


	/// I know this code could have been made more reusable but I was in the
	/// middle of a panic attack and was trying it get it done before the 
	/// next day, Wednesday.
	std::string line;		// Hold current line data
	int lineCount = 0;		// Track what line we are are
	while (std::getline(fs_file, line))
	{
		Card tmpCard;

		switch (lineCount)
		{
		case 0:		// Round
			roundScore = stoi(line.substr(line.find(':') + 1));
			break;
		case 3:		// CPU Score
			scoreChar = line.find(":") + 1;			// Round value as char 
			scoreString = line.substr(scoreChar);	// Convert to string
			scoreInt = stoi(scoreString);			// Convert to int
			cScore = scoreInt;						// Store
			break;
		case 4:		// CPU Hand
			cHandString = line.substr(line.find(':') + 1);
			if (!cHandString.empty()) // If there are cards
			{
				Card oldTmpCard(0, 14);
				ss.clear();
				ss.str(cHandString);	// Convert string into ss for easy manip
				do
				{
					ss >> tmpCardString;
					if (!tmpCardString.empty()) // If there is a card
					{
						// Convert token from string to card and add to card vector
						tmpCard = StrToCard(tmpCardString.at(0), tmpCardString.at(1));
						if (oldTmpCard.GetRankAsInt() != tmpCard.GetRankAsInt() ||
							oldTmpCard.GetSuit() != tmpCard.GetSuit())
						{
							cHand.push_back(tmpCard);
							oldTmpCard = tmpCard;
						}
					}
				} while (ss);
			}
			break;
		case 5:		// CPU Pile
			cPileString = line.substr(line.find(':') + 1);
			if (!cPileString.empty()) // If there are cards
			{
				Card oldTmpCard(0, 14);
				ss.clear();
				ss.str(cPileString);	// Convert string into ss for easy manip
				do
				{
					ss >> tmpCardString;
					if (!tmpCardString.empty()) // If there is a card
					{
						// Convert token from string to card and add to card vector
						tmpCard = StrToCard(tmpCardString.at(0), tmpCardString.at(1));
						if (oldTmpCard.GetRank() != tmpCard.GetRank() ||
							oldTmpCard.GetSuit() != tmpCard.GetSuit())
						{
							cPile.push_back(tmpCard);
							oldTmpCard = tmpCard;
						}
					}
				} while (ss);
			}
			break;
		case 8:		// Player Score
			scoreChar = line.find(":") + 1;			// Round value as char 
			scoreString = line.substr(scoreChar);	// Convert to string
			scoreInt = stoi(scoreString);			// Convert to int
			pScore = scoreInt;						// Store
			break;
		case 9:		// Player Hand
			pHandString = line.substr(line.find(':') + 1);
			if (!pHandString.empty()) // If there are cards
			{
				Card oldTmpCard(0, 14);
				ss.clear();
				ss.str(pHandString);	// Convert string into ss for easy manip
				do
				{
					ss >> tmpCardString;
					if (!tmpCardString.empty()) // If there is a card
					{
						// Convert token from string to card and add to card vector
						tmpCard = StrToCard(tmpCardString.at(0), tmpCardString.at(1));
						if (oldTmpCard.GetRank() != tmpCard.GetRank() ||
							oldTmpCard.GetSuit() != tmpCard.GetSuit())
						{
							pHand.push_back(tmpCard);
							oldTmpCard = tmpCard;
						}
					}
				} while (ss);
			}
			break;
		case 10:	// Player Pile
			pPileString = line.substr(line.find(':') + 1);
			if (!pPileString.empty()) // If there are cards
			{
				Card oldTmpCard(0, 14);
				ss.clear();
				ss.str(pPileString);	// Convert string into ss for easy manip
				do
				{
					ss >> tmpCardString;
					if (!tmpCardString.empty()) // If there is a card
					{
						// Convert token from string to card and add to card vector
						tmpCard = StrToCard(tmpCardString.at(0), tmpCardString.at(1));
						if (oldTmpCard.GetRank() != tmpCard.GetRank() ||
							oldTmpCard.GetSuit() != tmpCard.GetSuit())
						{
							pPile.push_back(tmpCard);
							oldTmpCard = tmpCard;
						}
					}
				} while (ss);
			}
			break;
		case 12:	// Table Cards
			RecordTableCards(line);
			break;
		case 14:	// Build Owner
			RecordBuildCards(line);
			break;
		case 16:	// Deck
			RecordDeck(line);
			break;
		case 18:	// Next Player
			RecordPlayerPointers(line);
			break;

		}
		lineCount += 1;
	}
	
	sRound = roundScore;
	sComputerScore = cScore;
	sHumanScore = pScore;
	sComputerHand = cHand;
	sHumanHand = pHand;
	sComputerPile = cPile;
	sHumanPile = pPile;

	return true;
}

void Serialization::RecordTableCards(std::string line)
{
	// Remove builds since we only want table cards
	//line.erase(std::remove(line.begin(), line.end(), '['), line.end());
	//line.erase(std::remove(line.begin(), line.end(), ']'), line.end());
	bool remove = false;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '[')
		{
			remove = true;
		}
		else if (line[i] == ']')
		{
			line.erase(line.begin() + i);
			remove = false;
			break;
		}

		if (remove)
		{
			line.erase(line.begin() + i);
			i -= 1;
		}
	}

	// Now find table cards 
	std::string tableCardsString = line.substr(line.find(':') + 1);
	if (!tableCardsString.empty()) // If there are cards
	{
		Card oldTmpCard(0, 14);
		std::istringstream ss;
		ss.clear();
		ss.str(tableCardsString);	// Convert string of cards into ss for easy manip

		Card tmpCard;
		std::string tmpCardString;
		do
		{
			ss >> tmpCardString;
			if (!tmpCardString.empty()) // If there is a card
			{
				// Convert token from string to card and add to card vector
				tmpCard = StrToCard(tmpCardString.at(0), tmpCardString.at(1));
				if (oldTmpCard.GetRank() != tmpCard.GetRank() ||
					oldTmpCard.GetSuit() != tmpCard.GetSuit())
				{
					sTableCards.push_back(tmpCard);
					oldTmpCard = tmpCard;
				}
			}
		} while (ss);
	}
}

void Serialization::RecordBuildCards(std::string line)
{
	std::vector<Card> unknownBuild;
	std::string unknownCard;
	std::string unknownOwner;

	// Track build status
	bool isBuild = false;

	// Iterate char by char through the line
	line = line.substr(line.find(':') + 1);
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '[')	// Beginning of build
		{
			isBuild = true;
		}
		else if (line[i] == ']') // End of build
		{
			isBuild = false;
		}
		else if (isBuild) // Inside of build
		{
			if (line[i] != ' ')	// There is a card
			{
				if (!unknownCard.empty())
				{
					// Convert str to card and add to build
					Card tmpCard = StrToCard(line.at(i - 1), line.at(i));
					unknownBuild.push_back(tmpCard);
					unknownCard.clear();
				}
				else
				{
					unknownCard += line[i];
				}
			}
			else
			{
				if (line[i] != ' ')
				{
					unknownCard += line[i];
				}
			}
		}
		else if (line[i] != ' ') // Outside of build
		{
			unknownOwner += line[i];
		}

		// Assign Ownership
		if (!isBuild && line.size() == i)
		{
			if (unknownOwner == "Human" ||
				unknownOwner == "Computer")
			{
				tmpBuild.Append(unknownBuild, unknownOwner);
				sAllBuilds.push_back(tmpBuild);
			}
		}
	}
}



void Serialization::RecordDeck(std::string line)
{
	// Store new deck
	std::vector<Card> tmpDeck;

	// Now find table cards 
	std::string deckCardsString = line.substr(line.find(':') + 1);
	if (!deckCardsString.empty()) // If there are cards
	{
				Card oldTmpCard(0, 14);
		std::istringstream ss;
		ss.clear();
		ss.str(deckCardsString);	// Convert string of cards into ss for easy manip

		Card tmpCard;
		std::string tmpCardString;
		while (ss)
		{
			ss >> tmpCardString;
			if (!tmpCardString.empty()) // If there is a card
			{
				// Convert token from string to card and add to card vector
				tmpCard = StrToCard(tmpCardString.at(0), tmpCardString.at(1));
				tmpDeck.push_back(tmpCard);
			}
		}
	}

	// Assign new deck
	sDeck.SetCustomDeck(tmpDeck);
}



// Function:	RecordPlayerPointers
// Purpose:		Get nextPlayer and currentPlayer from save file
// Parameters:	
// Returns:		
//		ALGORITHM
// 1.) Grab lines until at desired loc (bc we know the format of the save file)
// 2.) If this line contains the string "Human"
// 2a.) Assign nextPlayer to be the Human and current to be the Computer
// 3.) Else assign nextPlayer to be the Computer and current as Human
void Serialization::RecordPlayerPointers(std::string line)
{
	line = line.substr(line.find(':') + 1);
	line.erase(line.begin() + 0);

	if (line == "Human")
	{
		sNextPlayer = &sHumanPlayer;
		sCurrentPlayer = &sComputerPlayer;
	}
	else
	{
		sNextPlayer = &sComputerPlayer;
		sCurrentPlayer = &sHumanPlayer;
	}
}



// Function:	StartTournament()
// Purpose:		Starts a new tournament using save file settings
// Parameters:	
// Returns:		
//		ALGORITHM
// 1.) Set all variables from save settings
// 2.) Start the tournament while passing needed save file settings
void Serialization::StartTournament()
{
	sTable.tableHand = sTableCards;
	sTable.allBuilds = sAllBuilds;

	sComputerPlayer.myHand = sComputerHand;
	sComputerPlayer.pile = sComputerPile;

	sHumanPlayer.myHand = sHumanHand;
	sHumanPlayer.pile = sHumanPile;
	
	sTournament.SavedTournament(sRound, sTable, sDeck, sComputerPlayer, sHumanPlayer, sCurrentPlayer, sNextPlayer, sComputerScore, sHumanScore);
}



// Function:	StrToCard
// Purpose:		Converts string (or really two characters) into a string
// Parameters:	char suit, char rank
// Returns:		Returns a Card of the entered suit and rank
//		ALGORITHM
// 1.) switch statement processess suit character, if not valid throw an exception
// 2.) switch statement processess rank character, if not valid throw an exception
// 3.) Convert into a card and return it
Card Serialization::StrToCard(char suit, char rank)
{
	int suitAsInt;
	int rankAsInt;

	switch (suit)
	{
	case 'S':
		suitAsInt = 0;
		break;
	case 'H':
		suitAsInt = 1;
		break;
	case 'D':
		suitAsInt = 2;
		break;
	case 'C':
		suitAsInt = 3;
		break;
	default:
		throw std::logic_error("Invalid Suit");
		break;
	}

	switch (rank)
	{
	case '2':
		rankAsInt = 2;
		break;
	case '3':
		rankAsInt = 3;
		break;
	case '4':
		rankAsInt = 4;
		break;
	case '5':
		rankAsInt = 5;
		break;
	case '6':
		rankAsInt = 6;
		break;
	case '7':
		rankAsInt = 7;
		break;
	case '8':
		rankAsInt = 8;
		break;
	case '9':
		rankAsInt = 9;
		break;
	case 'X':
		rankAsInt = 10;
		break;
	case 'J':
		rankAsInt = 11;
		break;
	case 'Q':
		rankAsInt = 12;
		break;
	case 'K':
		rankAsInt = 13;
		break;
	case 'A':
		rankAsInt = 14;
		break;
	default:
		throw std::logic_error("Invalid Rank");
		break;
	}

	Card tmpCard(suitAsInt, rankAsInt);
	return tmpCard;
}


Serialization::~Serialization()
{
}
