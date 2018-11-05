#include "Table.h"


Table::Table()
{
	tableHand.clear();
	allBuilds.clear();
}



// Function:	PrintHand
// Purpose:		Displays a players hand
// Parameters:	vector<Card> playersHand, string playersName
// Returns:		
//		ALGORITHM
void Table::PrintHand(std::vector<Card> playerHand, std::string playerName)
{
	// Show Player 1's Hand
	std::cout << playerName << "'s Hand" << std::endl;
	for (unsigned i = 0; i < playerHand.size(); ++i)
	{
		std::cout << playerHand[i].GetRank();
		std::cout << playerHand[i].GetSuit() << " ";
	}
	std::cout << std::endl << std::endl;
}



// Function:	PrintTable
// Purpose:		Displays all table cards and builds
// Parameters:	
// Returns:		
//		ALGORITHM
void Table::PrintTable()
{
	// Print Cards
	std::cout << "Table Cards" << std::endl;
	for (unsigned i = 0; i < tableHand.size(); ++i)
	{
		std::cout << tableHand[i].GetRank();
		std::cout << tableHand[i].GetSuit() << " ";
	}

	// Print Builds
	for (unsigned i = 0; i < allBuilds.size(); i++)
	{
		std::cout << "[";

		if (allBuilds[i].owner == "CPU") { std::cout << " CPU "; }
		else { std::cout << " HUMAN "; }

		// Grab current build
		Build cBuildSet = allBuilds[i];

		// Grab that builds set of cards
		std::vector<Card> cBuildSetCards = cBuildSet.buildSet;

		// for each card in the set, print it!
		for (unsigned j = 0; j < cBuildSetCards.size(); j++)
		{
			std::cout << cBuildSetCards[j].GetRank();
			std::cout << cBuildSetCards[j].GetSuit() << " ";
		}
		std::cout << "]";
	}
	std::cout << std::endl << std::endl;
}



// Function:	SetHasCard
// Purpose:		Check if a players set has the card passed in
// Parameters:	string cardName, vector<Card> &buildSet, vector<Card> &cardSet
// Returns:		Returns a bool representing if the card exists within the set
bool Table::SetHasCard(std::string cardName, std::vector<Card> &buildSet, std::vector<Card> &cardSet)
{
	// Look for the card name in players hand
	for (unsigned i = 0; i < cardSet.size(); i++)
	{
		// Get card in hand as (i.e. JD, 5C)
		std::string tmpCard = cardSet[i].GetRank() + cardSet[i].GetSuit();

		// Valid card selected
		if (tmpCard == cardName)
		{
			buildSet.push_back(cardSet[i]);		// Add card to build set
			cardSet.erase(cardSet.begin() + i); // Erase from old set
			return true;
		}
	}

	return false;
}



// Function:	TableHasCard
// Purpose:		Checks if the table has the card passed in and modified the passed in card with the card found
// Parameters:	string cardNameToCheck, Card cardToCheck
// Returns:		Returns a bool representing if the card exists on the table or not
bool Table::TableHasCard(std::string cardName, Card &card)
{
	// Look for the card name on the table
	for (unsigned i = 0; i < tableHand.size(); i++)
	{
		// Get card on table as (i.e. JD, 5C)
		std::string tmpCard = tableHand[i].GetRank() + tableHand[i].GetSuit();

		// Valid card selected
		if (tmpCard == cardName)
		{
			card = tableHand[i];
			return true;
		}
	}

	return false;
}



// Function:	TableHasCard
// Purpose:		Checks if the table has the card passed in and modified the passed in index for EraseCard
// Parameters:	string cardNameToCheck, int index
// Returns:		Returns a bool representing if the card exists on the table or not
bool Table::TableHasCard(std::string cardName, int &idx)
{
	// Look for the card name in players hand
	for (unsigned i = 0; i < tableHand.size(); i++)
	{
		// Get card in hand as (i.e. JD, 5C)
		std::string tmpCard = tableHand[i].GetRank() + tableHand[i].GetSuit();

		// Valid card selected
		if (tmpCard == cardName)
		{
			idx = i;
			return true;
		}
	}

	return false;
}



// Function:	EraseCard
// Purpose:		Erases a card from the table
// Parameters:	string cardNameToBeErased
// Returns:		
void Table::EraseCard(std::string cardName)
{
	int index;
	if (TableHasCard(cardName, index))
	{
		tableHand.erase(tableHand.begin() + index);
	}
}



// Function:	CheckCapture
// Purpose:		Checks if a player has the ability to capture
// Parameters:	vector<Card> playersHand, string playersName
// Returns:		Returns a bool representing if the player can capture or not
//		ALGORITHM
// (For Uncommented Section)
// 1.) iff player has any builds
// 1a.)		return false, he can capture and therefore can't trail
// 2.) for each card in hand, check if there is a matching table card
bool Table::CheckCapture(std::vector<Card> playerHand, std::string playerName)
{
	// If player has a build, he can capture
	for (unsigned i = 0; i < allBuilds.size(); i++)
	{
		if (allBuilds[i].owner == playerName) { return true; }
	}

	// Grab next card in players hand to be the card we are trying to build
	for (unsigned i = 0; i < playerHand.size(); i++)
	{
		// Grab card on table to be a pivot
		for (unsigned j = 0; j < tableHand.size(); j++)
		{
			// If both cards have same value
			if (IsMatch(playerHand[i], tableHand[j]))
			{
				return true;
			}

			// Grab next card on table
			//for (unsigned k = 0; k < tableHand.size(); k++)
			//{
			//	// Can't add the same card to itself
			//	if (j != k)
			//	{ 
			//		// Get int values of card ranks
			//		int captureTarget = playerHand[i].GetRankAsInt();
			//		int pivotValue = tableHand[j].GetRankAsInt();
			//		int tableValue = tableHand[k].GetRankAsInt();
			//		int tmp = pivotValue + tableValue;
			//
			//		if (tmp == captureTarget) { return true; }
			//	}
			//}
		}
	}
	return false;
}



// Function:	CheckTrail
// Purpose:		Checks if the player has the ability to trail
// Parameters:	vector<Card> playersHand, string playersName
// Returns:		Returns a bool representing if the player can trail or not
bool Table::CheckTrail(std::vector<Card> playerHand, std::string playerName)
{
	return !CheckCapture(playerHand, playerName);
	// Change to check for only loose cards only
}



// Function:	IsMatch
// Purpose:		Check if both cards are the same rank
// Parameters:	Card compare1, Card compare2
// Returns:		Returns a bool representing if both cards match
bool Table::IsMatch(Card x, Card y)
{
	if (x.GetRank() == y.GetRank()) { return true; }
	return false;
}



// Function:	AddTrailCard
// Purpose:		Adds players card to the table hand
// Parameters:	Card cardToBeTrailed
// Returns:		
void Table::AddTrailCard(Card trail)
{
	tableHand.push_back(trail);
}



// Function:	Append
// Purpose:		Add player's build to the table's list of builds
// Parameters:	Build playersBuild
// Returns:		
void Table::Append(Build playerBuild)
{
	allBuilds.push_back(playerBuild);
}



// Function:	ReturnSubset
// Purpose:		Modifies the passed in vector<Card> currenBuildSet with new subset
//				Obtained from GeeksForGeeks
// Parameters:	vector<Card> setOfCards, int sumOfbuildCard, vector<Card> &currentBuildSet
// Returns:		Returns a bool representing if a subset was found		
bool Table::ReturnSubset(std::vector<Card> cards, int buildTarget, std::vector<Card> &currentBuild)
{
	// Holds unique subsets only
	std::vector<std::string> list;
	int n = cards.size();

	for (int i = 0; i < (int)pow(2, n); i++)
	{
		std::string subset = "";

		for (int j = 0; j < n; j++)
		{
			// Check if jth item in the i is set. If the item
			// is set, we consider jth element from set
			if ((i & (1 << j)) != 0)
			{
				subset += cards[j].GetRank() + "|";

				// Account for Aces being 14 or 1
				if (cards[j].GetRank() == "14")
				{
					subset += '1' + "|";
				}
			}
		}

		// if subset is encountered for the first time
		if (find(list.begin(), list.end(), subset) == list.end())
		{
			list.push_back(subset);
		}
		
		// consider every subset
		for (std::string subset : list)
		{
			// split the subset
			std::vector<std::string> vec = Split(subset, '|');

			int sum = 0;
			std::vector<Card> cardList;	// list of cards to return
			for (std::string str : vec)
			{
				// Convert card string rank to int
				//sum += stoi(str);
				if (str == "2" || str == "3" || str == "4" || str == "5" || str == "6" ||
					str == "7" || str == "8" || str == "9" || str == "10")
				{ sum += stoi(str); }
				else if (str == "X") { sum += 10; }
				else if (str == "J") { sum += 11; }
				else if (str == "Q") { sum += 12; }
				else if (str == "K") { sum += 13; }
				else if (str == "A") { sum += 14; }

				// Find card on table with needed value
				// add that card to the list
				// return the list of cards
				for (unsigned i = 0; i < cards.size(); i++)
				{
					Card cCard = cards[i];
					if (cCard.GetRank() == str)
					{
						cardList.push_back(cCard);
					}
					// Account for Aces
					else if (cCard.GetRank() == "14" || str == "A")
					{
						cardList.push_back(cCard);
					}
				}

				// A build set is found
				if (sum == buildTarget && cardList.size() > 1) { currentBuild = cardList; return true; }
			}
		}
	}
	return false;
}



// Function:	FindAllSubsets
// Purpose:		Return true if a subset was found of the passed in <Card> vector
//				Obtained from GeeksForGeeks
// Parameters:	vector<Card> setOfCards, int sumOfbuildCard
// Returns:		Returns a bool representing if a subset was found
bool Table::FindAllSubsets(std::vector<Card> cards, int buildTarget)
{
	// Holds unique subsets only
	std::vector<std::string> list;
	int n = cards.size();

	for (int i = 0; i < (int) pow(2, n); i++)
	{
		std::string subset = "";

		for (int j = 0; j < n; j++)
		{
			// Check if jth item in the i is set. If the item
			// is set, we consider jth element from set
			if ((i & (1 << j)) != 0)
			{
				subset += cards[j].GetRank() + "|";

				// Account for Aces being 14 or 1
				if (cards[j].GetRank() == "14") 
				{
					subset += '1' + "|";
				}
			}
		}

		// if subset is encountered for the first time
		// If we use set<string>, we can directly insert
		if (find(list.begin(), list.end(), subset) == list.end())
			list.push_back(subset);

		// consider every subset
		for (std::string subset : list)
		{
			// split the subset and print its elements
			std::vector<std::string> vec = Split(subset, '|');

			int sum = 0;
			for (std::string str : vec)
			{
				//std::cout << str << " ";
				sum += stoi(str);
				// A build is found
				if (sum == buildTarget) { return true; }
			}
			//std::cout << std::endl;
		}
	}
	return false;
}



// Function:	Split
// Purpose:		Ultility function of ReturnSubset obtained from GeeksForGeeks
// Parameters:	string &s, char delimiter
// Returns:		vector<string> element
std::vector<std::string> Table::Split(const std::string & s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}


Table::~Table()
{
}
