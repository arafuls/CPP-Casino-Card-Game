#include "Computer.h"



Computer::Computer()
{
	// Set computers name
	name = "CPU";
}



// Function:	Play
// Purpose:		Plays for the computer
// Parameters:	Table table
// Returns:		
//		ALGORITHM
// 1.) If computer can build, build
// 2.) Else if computer cant build, capture
// 3.) Else if computer cant capture, trail
void Computer::Play(Table &table)
{
	if (!AutoBuild(table))
	{
		if (!AutoCapture(table))
		{
			AutoTrail(table);
		}
	}
}



// Function:	AutoBuild
// Purpose:		Builds for the computer
// Parameters:	Table table
// Returns:		Returns a bool representing if the computer can build or not
//		ALGORITHM
bool Computer::AutoBuild(Table &table)
{
	// Hand is too small to build
	if (myHand.size() < 2) { return false; }

	for (unsigned i = 0; i < table.allBuilds.size(); i++)
	{
		// CPU has a build, cannot build
		if (table.allBuilds[i].owner == name) { return false; }
	}

	// Track cards
	Card buildCard;
	Card dropCard;

	// Grab next available card
	for (unsigned i = 0; i < myHand.size(); i++)
	{
		buildCard = myHand[i];
		// Grab another card to be the drop card
		for (unsigned j = 0; j < myHand.size(); j++)
		{
			// Cannot be the same card
			if (i != j)
			{
				// Assign dropCard
				dropCard = myHand[j];

				// Make copy of table cards with dropCard
				std::vector<Card> tableCards = table.tableHand;

				// Check table for build
				std::vector<Card> buildSet = FindBuildCards(buildCard, dropCard, tableCards);
				if (buildSet.size() == NULL || buildSet.size() == 0) { continue; }

				// Display CPU Action
				std::cout << "CPU has dropped " << dropCard.GetRank() << dropCard.GetSuit() 
					<< " to create the set [ ";

				for (unsigned k = 0; k < buildSet.size(); k++)
				{
					std::cout << buildSet[k].GetRank() << buildSet[k].GetSuit() << " ";
				}

				std::cout << "]" << std::endl;
				std::cout << "This was done to maximize amount of cards gained." << std::endl;
				

				// Append build to table
				myBuild.Append(buildSet, buildCard, name, buildCard.GetRankAsInt());
				table.Append(myBuild);
				
				// Erase cards from table
				for (unsigned k = 0; k < buildSet.size(); k++)
				{
					for (unsigned l = 0; l < tableCards.size(); l++)
					{
						std::string currCard = tableCards[l].GetRank() + tableCards[l].GetSuit();

						if (buildSet[k].GetRank() == tableCards[l].GetRank() &&
							buildSet[k].GetSuit() == tableCards[l].GetSuit())
						{
							table.EraseCard(currCard);
						}
					}
				}
				
				// Erase dropCard from hand
				for (unsigned k = 0; k < myHand.size(); k++)
				{
					std::string cardName = myHand[k].GetRank() + myHand[k].GetSuit();
					std::string dropName = dropCard.GetRank() + dropCard.GetSuit();
					if (cardName == dropName) { myHand.erase(myHand.begin() + k); }
				}
				return true;
			}
		}
	}
	return false;
}



// Function:	AutoCapture
// Purpose:		Captures for the computer
// Parameters:	Table table
// Returns:		Returns a bool representing if the computer can capture or not
//		ALGORITHM
// It is easier to read the commenting within
bool Computer::AutoCapture(Table &table)
{
	Card captureCard;
	int captureCardIdx;
	bool buildCaptured = false;

	// Find captureCard
	for (unsigned i = 0; i < myHand.size(); i++)
	{
		// j = current build
		// k = card in current build
		for (unsigned j = 0; j < table.allBuilds.size(); j++)
		{
			// CPU has a build, capture it
			if (table.allBuilds[j].owner == name &&
				myHand[i].GetRank() == table.allBuilds[j].buildCard.GetRank() &&
				myHand[i].GetSuit() == table.allBuilds[j].buildCard.GetSuit())
			{
				// captureCard found, log it
				captureCard = myHand[i];
				buildCaptured = true;
				captureCardIdx = i;

				// For each card in the current build
				for (unsigned k = 0; k < table.allBuilds[j].buildSet.size(); k++)
				{
					// Add cards to pile
					Card buildCard = table.allBuilds[j].buildSet[k];
					pile.push_back(buildCard);
				}

				std::cout << "CPU has captured a build with " << captureCard.GetRank() << captureCard.GetSuit() << "." << std::endl;

				// Erase build
				table.allBuilds.erase(table.allBuilds.begin() + j);
			}
		}
	}

	// Find matching loose cards
	if (buildCaptured)
	{
		// for every card on table
		for (unsigned i = 0; i < table.tableHand.size(); i++)
		{
			// card found with same rank
			if (captureCard.GetRank() == table.tableHand[i].GetRank())
			{
				std::cout << "CPU has captured " << table.tableHand[i].GetRank() << table.tableHand[i].GetSuit() << " as it matched with " << captureCard.GetRank() << captureCard.GetSuit() << "." << std::endl;
				std::cout << "This was the last available option prior to trailing." << std::endl;

				pile.push_back(table.tableHand[i]);
				table.tableHand.erase(table.tableHand.begin() + i);
			}
		}
	}
	else
	{
		// Try to find a loose match for each hand card
		for (unsigned i = 0; i < myHand.size(); i++)
		{
			bool success = false;

			// for every card on the table
			for (unsigned j = 0; j < table.tableHand.size(); j++)
			{
				if (myHand[i].GetRank() == table.tableHand[j].GetRank())
				{
					captureCard = myHand[i];
					captureCardIdx = i;

					std::cout << "CPU has captured " << table.tableHand[j].GetRank() << table.tableHand[j].GetSuit() << " as it matched with " << captureCard.GetRank() << captureCard.GetSuit() << "." << std::endl;
					std::cout << "This was the last available option prior to trailing." << std::endl;

					pile.push_back(table.tableHand[j]);
					table.tableHand.erase(table.tableHand.begin() + j);

					buildCaptured = true;
					success = true;
				}
			}

			// Only capture cards for a single unique card
			if (success) { break; }
		}
	}

	// capture card into pile and erase
	if (buildCaptured) { pile.push_back(captureCard); myHand.erase(myHand.begin() + captureCardIdx); }

	return buildCaptured;
}



// Function:	AutoTrail
// Purpose:		Trails for the computer
// Parameters:	Table table
// Returns:		
//		ALGORITHM
// 1.) Trails first card in computers hand to the table and erases from hand
// 2.) Displays action to the user
void Computer::AutoTrail(Table &table)
{
	Card trailCard = myHand.front();  // Select card to trail
	std::cout << "CPU has trailed " << trailCard.GetRank() << trailCard.GetSuit() << "." << std::endl;
	std::cout << "It had no other option than to trail." << std::endl;

	myHand.erase(myHand.begin() + 0); // Remove trail card from hand
	table.AddTrailCard(trailCard);
}



// Function:	FindBuildCards
// Purpose:		Returns the set of cards needed for the build
// Parameters:	Card buildCard, Card dropCard, vector<Card> setOfCards
// Returns:		vector<Card> buildSet
//		ALGORITHM
// 1.) If table card + drop card = the sum of the build card
//		1a.) return the set of cards, table and drop card
// 2.) Else return NULL card vector
std::vector<Card> Computer::FindBuildCards(Card buildCard, Card dropCard, std::vector<Card> setOfCards)
{
	for (unsigned i = 0; i < setOfCards.size(); i++)
	{
		int targetSum = buildCard.GetRankAsInt();
		int sum = 0;

		// Count sum
		if (dropCard.GetRank() == "A") { sum += 1; }
		else { sum += dropCard.GetRankAsInt(); }
		if (setOfCards[i].GetRank() == "A") { sum += 1; }
		else { sum += setOfCards[i].GetRankAsInt(); }


		// If cards add up to sum
		if (sum == targetSum)
		{
			// Add them to vector and return
			std::vector<Card> buildSet;
			buildSet.push_back(dropCard);
			buildSet.push_back(setOfCards[i]);
			return buildSet;
		}
	}

	return std::vector<Card>(NULL);
}



Computer::~Computer()
{
}
