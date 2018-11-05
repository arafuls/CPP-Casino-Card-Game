#include "Human.h"



Human::Human()
{
	// Set name of human player
	name = "Human";
}



// Function:	Play
// Purpose:		Lets the user choose what action he wants to perform
// Parameters:	Table &table
// Returns:		
void Human::Play(Table &table)
{
	if (myHand.size() < 1) { return; }

	// Restart menu selection when false
	bool result = false;

	// Display moves to the player
	std::cout << std::endl;
	std::cout << "	   MAIN MENU OPTIONS" << std::endl;
	std::cout << "	1.) Save      4.) Trail" << std::endl;
	std::cout << "	2.) Build     5.) Help" << std::endl;
	std::cout << "	3.) Capture   6.) Quit" << std::endl;

	do
	{
		// Get user input
		int input = ValidInput();

		switch (input)
		{
		case 1:
			// Save
			std::cout << "Sorry, saving is not implemented yet!" << std::endl;
			break;
		case 2:
			result = Build(table);
			break;
		case 3:
			result = Capture(table);
			break;
		case 4:
			result = Trail(table);
			break;
		case 5:
			result = Help(table);
			break;
		case 6:
			exit(EXIT_SUCCESS);
			break;
		default:
			std::cout << "Invalid option, please try again." << std::endl;
			break;
		}

	} while (!result);
}



// Function:	ValidInput
// Purpose:		Gets input from user and validates it
// Parameters:	
// Returns:		Returns int representing the users input
int Human::ValidInput()
{
	int input;
	do
	{
		std::cout << "Input: ";
		std::cin >> input;

		// Clear and ignore incorrect entries
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (input < 1 && input > 6);

	return input;
}



// Function:	Build
// Purpose:		Get which type of build the user wants to perform
// Parameters:	Table &table
// Returns:		Returns a bool representing if the player successfully completed an action or not
bool Human::Build(Table &table)
{
	bool result = false;

	// Display moves to the player
	std::cout << std::endl;
	std::cout << "	   BUILD OPTIONS" << std::endl;
	std::cout << "	1.) Single    2.) Multi" << std::endl;
	std::cout << "	3.) Extend" << std::endl;
	// Get user input
	int input = ValidInput();

	switch (input)
	{
	case 1:
		// Single Build
		result = SingleBuild(table);
		break;
	case 2:
		// Multi Build
		result = MultiBuild(table);
		break;
	case 3:
		// Extend Build
		break;
	default:
		// Throw exception
		break;
	}

	return result;
}



// Function:	MultiBuild
// Purpose:		Create multiple builds of equal value to prior builds
// Parameters:	Table &table
// Returns:		Returns a bool representing if the player successfully created a multibuild or not
//		ALGORITHM
// It is easier to read the commenting within the function
bool Human::MultiBuild(Table &table)
{
	// Check to make sure builds already exist to this player
	if (!PlayerHasBuilds(table))
	{
		std::cout << "You do not have any builds! Either make a single build, capture, or trail!" << std::endl;
		return false;
	}

	// Get prior builds sum
	int priorBuildSum = 0;
	for (unsigned i = 0; i < table.allBuilds.size(); i++)
	{
		std::string tmp = table.allBuilds[i].owner;
		if (tmp == name) 
		{ 
			if (0 == table.allBuilds[i].trueSum)
			{
				// No true sum defined, calculate trueSum manually
				int tmpSum = 0;
				for (unsigned j = 0; j < table.allBuilds[i].buildSet.size(); j++)
				{
					// Account for soft ace
					if (14 == table.allBuilds[i].buildSet[j].GetRankAsInt())
					{
						tmpSum += 1;
					}
					else
					{
						tmpSum += table.allBuilds[i].buildSet[j].GetRankAsInt();
					}
				}
				table.allBuilds[i].trueSum = tmpSum;
				priorBuildSum = tmpSum;
			}
			else
			{
				priorBuildSum = table.allBuilds[i].trueSum;
			}
		}
	}

	// Keeps track of cards we are building and dropping
	Card buildCard;
	Card dropCard;

	// Get build card from user and assign buildCard
	if (!UserGetCard(buildCard, "build")) { return false; }
	if (buildCard.GetRankAsInt() != priorBuildSum)
	{
		std::cout << "You can only create another build equal to the sum of prior builds! ( " << priorBuildSum << " )" << std::endl;
		return false;
	}

	// Get drop card from user and assign dropCard
	if (!UserGetCard(dropCard, "drop")) { return false; }

	// Get amount of cards needed from table to make a build
	int looseCards = UserGetLooseCards(table);

	// Gets assigned the cards the user picks from the table
	std::vector<Card> buildSet;

	// Get the cards the user wants to build with
	if (!UserGetTableCards(table, looseCards, buildSet)) { return false; }

	// Add dropCard to buildSet
	buildSet.push_back(dropCard);

	// Confirm sum of buildSet is equal to sum of buildCard
	int buildSum;
	if (!CheckBuildSum(buildCard, buildSet, buildSum)) { return false; }

	// Add cards to build
	myBuild.Append(buildSet, buildCard, name, buildSum);
	table.Append(myBuild);

	// Erase cards from table
	for (unsigned i = 0; i < buildSet.size(); i++)
	{
		std::string cardName = buildSet[i].GetRank() + buildSet[i].GetSuit();
		table.EraseCard(cardName);
	}

	// Erase dropCard from hand
	for (unsigned i = 0; i < myHand.size(); i++)
	{
		std::string cardName = myHand[i].GetRank() + myHand[i].GetSuit();
		std::string dropName = dropCard.GetRank() + dropCard.GetSuit();
		if (cardName == dropName) { myHand.erase(myHand.begin() + i); }
	}

	return true;
}



// Function:	Capture
// Purpose:		Captures builds, sets, and/or matching loose cards
// Parameters:	Table table
// Returns:		Returns a bool representing if the player captured successfully or not
//		ALGORITHM
// It is easier to read the commenting within the function
bool Human::Capture(Table &table)
{
	// Represents if user captured at least 1 card successfully
	bool captured = false;

	// Get build card from user and assign buildCard
	Card captureCard;
	if (!UserGetCard(captureCard, "capture with")) { return false; }

	// Auto capture
	// Check if any of the cards on the table match the capture cards face
	std::vector<Card> looseMatchingCards;
	for (unsigned i = 0; i < table.tableHand.size(); i++)
	{
		int tableCardFace = table.tableHand[i].GetRankAsInt();
		if (tableCardFace == captureCard.GetRankAsInt())
		{
			// Matching card found, erase from table and add to pile
			Card tmp = table.tableHand[i];
			std::string tmpTableCard = table.tableHand[i].GetRank() + table.tableHand[i].GetSuit();

			std::cout << "You have automatically captured " << table.tableHand[i].GetRank() << table.tableHand[i].GetSuit()
				<< " as it matched your capture card!" << std::endl;

			table.EraseCard(tmpTableCard);
			pile.push_back(tmp);
			captured = true;
		}
	}
	
	// Check if user has any builds
	for (unsigned i = 0; i < table.allBuilds.size(); i++)
	{
		// Current build belongs to the player
		// AND if captureCard is valid for the current build
		if (table.allBuilds[i].owner == name)
		{
			// If sum is null from starting game from save file..
			if (table.allBuilds[i].trueSum == 0)
			{
				// Try to re-assign
				if (table.allBuilds[i].hardSum == captureCard.GetRankAsInt()) { table.allBuilds[i].trueSum = table.allBuilds[i].hardSum; }
				else { table.allBuilds[i].trueSum = table.allBuilds[i].softSum; }
			}

			// For each card in the current build
			for (unsigned j = 0; j < table.allBuilds[i].buildSet.size(); j++)
			{
				// Add each card to the player's pile
				Card buildCard = table.allBuilds[i].buildSet[j];
				pile.push_back(buildCard);
				captured = true;
			}
			// the build is now empty, erase the build
			table.allBuilds.erase(table.allBuilds.begin() + i);
			i = i - 1;
		}
	}

	// See if user wants to capture any sets
	int captureSets = -1;
	char input;
	do
	{
		std::cout << std::endl << "Would you like to capture any sets? (Y/N) ";
		std::cin >> input;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (input != 'Y' && input != 'N' && input != 'y' && input != 'n');

	if (input == 'Y' || input == 'y') { captureSets = true; }
	else { captureSets = false; }

	// Capture set
	while (captureSets)
	{
		// Get amount if cards user wants to use
		int looseCards = UserGetLooseCards(table);

		// Get the cards the user wants to capture
		std::vector<Card> captureSet;
		if (!UserGetTableCards(table, looseCards, captureSet)) { return false; }

		// Check if cards are equal to capture set
		int captureSum;
		if (!CheckBuildSum(captureCard, captureSet, captureSum)) { return false; }

		// Add cards to pile and erase from table
		for (unsigned i = 0; i < captureSet.size(); i++)
		{
			pile.push_back(captureSet[i]);
			table.EraseCard(captureSet[i].GetRank() + captureSet[i].GetSuit());
			captured = true;
		}

		do
		{
			std::cout << std::endl << "Would you like to capture any other sets? (Y/N) ";
			std::cin >> input;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (input != 'Y' && input != 'N' && input != 'y' && input != 'n');

		if (input == 'Y') { captureSets = true; }
		else { captureSets = false; }
	}

	// Add captureCard to pile and erase from hand
	if (captured)
	{
		pile.push_back(captureCard);
		for (unsigned i = 0; i < myHand.size(); i++)
		{
			if (myHand[i].GetRank() == captureCard.GetRank() &&
				myHand[i].GetSuit() == captureCard.GetSuit())
			{
				myHand.erase(myHand.begin() + i);
			}
		}
	}

	return captured;
}



// Function:	Trail
// Purpose:		Trails a card for the user
// Parameters:	Table &table
// Returns:		Returns a bool representing if user trailed successfully or not
//		ALGORITHM
// 1.) Check if player can trail, if not return false
// 2.) Get card to trail from user, if invalid return false
// 3.) Add valid trail card to table
// 4.) Erase the trail card from players hand
// 5.) return true
bool Human::Trail(Table &table)
{
	// Check if player is allowed to trail
	if (!table.CheckTrail(myHand, name))
	{
		std::cout << "You cannot trail if you can capture!" << std::endl;
		return false;
	}


	// Get trail card from user and assign trailCard
	Card trailCard;
	if (!UserGetCard(trailCard, "trail with")) { return false; }

	// Add card to table
	table.tableHand.push_back(trailCard);

	// Erase from hand
	for (unsigned i = 0; i < myHand.size(); i++)
	{
		if (myHand[i].GetRank() == trailCard.GetRank() &&
			myHand[i].GetSuit() == trailCard.GetSuit())
		{
			myHand.erase(myHand.begin() + i);
		}
	}

	return true;
}



// Function:	Help
// Purpose:		Tell the user their options
// Parameters:	Card &tmpDropCard, string cardType
// Returns:		
bool Human::Help(Table & table)
{
	if (PlayerHasBuilds(table))
	{ 
		std::cout << "[HELP] You can either try to make a multi-build or capture." << std::endl;
	}
	else
	{
		std::cout << "[HELP] You can either try to make a single-build, capture, or trail." << std::endl;
	}
	return false;
}



// Function:	UserGetCard
// Purpose:		Gets card from the user and validates user input
// Parameters:	Card &tmpDropCard, string cardType
// Returns:		Returns as bool representing if user successfully entered a card
//		ALGORITHM
// 1.) User inputs card and card type (drop, build, etc)
// 2.) Validate user has ownership of entered card and assign it to tmpDropCard build
// 2a.) If not valid, return false
// 3.) return true
bool Human::UserGetCard(Card &tmpDropCard, std::string cardType)
{
	std::string input;

	std::cout << "Input card in your hand to " << cardType << " with: ";
	std::cin >> input;

	char r = toupper(input.at(0));
	switch (r)
	{
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'X':
	case 'J':
	case 'Q':
	case 'K':
	case 'A':
		break;
	default:
		std::cout << "Invalid Rank!" << std::endl;
		return false;
	}
	
	char s = toupper(input.at(1));
	switch (s)
	{
	case 'S':
	case 'D':
	case 'H':
	case 'C':
		break;
	default:
		std::cout << "Invalid Suit!" << std::endl;
		return false;
	}

	std::string tmpCard;
	tmpCard += r;
	tmpCard += s;

	if (!PlayerHasCard(tmpCard, tmpDropCard)) { return false; }

	return true;
}



// Function:	SingleBuild
// Purpose:		Builds a single build
// Parameters:	Table &table
// Returns:		Returns a bool representing if the player successfully created a build or not
//		ALGORITHM
// It is easier to read the commenting within the function
bool Human::SingleBuild(Table &table)
{
	std::vector<Card> buildSet;		// Holds cards the user picks from the table

	// Check to make sure no builds already exist to this player
	if (PlayerHasBuilds(table))
	{
		std::cout << "You already have a build! Either make a multi-build, capture, or trail!" << std::endl;
		return false;
	}

	// Keeps track of cards we are building and dropping
	Card buildCard;
	Card dropCard;

	// Get build and drop cards from the user
	if (!UserGetCard(buildCard, "build")) { std::cout << "Invalid card or you do not own it!"; return false; }
	if (!UserGetCard(dropCard, "drop")) { std::cout << "Invalid card or you do not own it!"; return false; }

	// Get amount of cards needed from table to make a build
	int looseCards = UserGetLooseCards(table);

	// Get the cards the user wants to build with
	if (!UserGetTableCards(table, looseCards, buildSet)) { return false; }

	// Add dropCard to buildSet
	buildSet.push_back(dropCard);

	int buildSum;
	if (!CheckBuildSum(buildCard, buildSet, buildSum)) { return false; }

	// Add cards to build
	myBuild.Append(buildSet, buildCard, name, buildSum);
	table.Append(myBuild);

	// Erase cards from table
	for (unsigned i = 0; i < buildSet.size(); i++)
	{
		std::string cardName = buildSet[i].GetRank() + buildSet[i].GetSuit();
		table.EraseCard(cardName);
	}

	// Erase dropCard from hand
	for (unsigned i = 0; i < myHand.size(); i++)
	{
		std::string cardName = myHand[i].GetRank() + myHand[i].GetSuit();
		std::string dropName = dropCard.GetRank() + dropCard.GetSuit();
		if (cardName == dropName) { myHand.erase(myHand.begin() + i); }
	}

	return true;
}



// Function:	UserGetTableCards
// Purpose:		Gets which cards from the table the user wants
// Parameters:	Table table, int numberOfCardsNeeded, vector<Card> &currentBuildSet
// Returns:		Returns a bool representing if user cancelled or not
//		ALGORITHM
// 1.) Ask user for card from the table
// 2.) If user entered a valid card,
// 2a.)		Add card to buildSet
// 2b.) Else
// 2c.)		Do nothing
// 3.) If user entered -1, return false to cancel
// 4.) If user hasn't entered enough cards to satisfy the number of cards needed, goto step 1
bool Human::UserGetTableCards(Table table, int totalCards, std::vector<Card> &currentBuildSet)
{
	// Clone the table cards so we can use it to build the above
	std::vector<Card> tmpTableHand = table.tableHand;

	// Get the cards the user wants to build with
	std::string input;
	for (signed i = 0; i < totalCards; i++)
	{
		std::string tmpCard;
		do
		{
			tmpCard.clear();
			std::cout << "Enter a card from the table to build with: ";
			std::cin >> input;

			char r = toupper(input.at(0));
			switch (r)
			{
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'X':
			case 'J':
			case 'Q':
			case 'K':
			case 'A':
				break;
			default:
				std::cout << "Invalid Rank!" << std::endl;
				return false;
			}

			char s = toupper(input.at(1));
			switch (s)
			{
			case 'S':
			case 'D':
			case 'H':
			case 'C':
				break;
			default:
				std::cout << "Invalid Suit!" << std::endl;
				return false;
			}

			tmpCard += r;
			tmpCard += s;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		} while (!table.SetHasCard(tmpCard, currentBuildSet, tmpTableHand) && tmpCard != "-1"); // Adds card to buildSet if true

		if (input == "-1") 
		{
			std::cout << "Action cancelled." << std::endl;
			return false; 
		}
	}

	return true;
}



// Function:	UserGetLooseCards
// Purpose:		Gets how many loose cards the user wants to use for his build or set
// Parameters:	Table table
// Returns:		Returns integer representing the number of cards needed from the table
//		ALGORITHM
int Human::UserGetLooseCards(Table table)
{
	unsigned looseCards = 0;
	do
	{
		std::string input;

		// Get how many cards the user needs to make their build
		std::cout << "How many loose cards from the table are you using: ";
		std::cin >> input;

		looseCards = stoi(input);

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (looseCards < 1 || looseCards > table.tableHand.size() || -1 == looseCards);
	return looseCards;
}



// Function:	PlayerHasBuilds
// Purpose:		Checks if human player has any builds on the table
// Parameters:	Table table
// Returns:		Returns a bool representing if the player owns any builds
//		ALGORITHM
// 1.) Go through all builds on the table
// 2.) if a build has the owner property == "Human"
// 2a.)		player owns a build, return true
// 2b.) else, return false
bool Human::PlayerHasBuilds(Table table)
{
	for (unsigned i = 0; i < table.allBuilds.size(); i++)
	{
		std::string tmp = table.allBuilds[i].owner;
		if (tmp == name)
		{
			return true;
		}
	}
	return false;
}



Human::~Human()
{
}
