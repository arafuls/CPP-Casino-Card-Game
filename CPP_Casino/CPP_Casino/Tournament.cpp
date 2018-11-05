#include "Tournament.h"

// Default constructor
Tournament::Tournament()
{
	// Init for new tournament
	roundCounter = 1;
	humanPts = 0;
	computerPts = 0;
	currentPlayer = NULL;
	nextPlayer = NULL;

	// Player names
	humanPlayer.name = "Human";
	computerPlayer.name = "CPU";
}



// Function:	SavedTournament
// Purpose:		Starts a round where the user left off according to the save file
// Parameters:	int round, Table table, Deck deck, Computer computerPlayer, Human humanPlayer, Player *currentPlayer, Player *nextPlayer, int computerPts, int humanPts
// Returns:		
void Tournament::SavedTournament(int sRound, Table sTable, Deck sDeck, Computer sCPU, Human sHuman, Player *sCurrentPlayer, Player *sNextPlayer, int sComputerScore, int sHumanScore)
{
	Round aRound;
	roundCounter = sRound;

	currentPlayer = sCurrentPlayer;
	nextPlayer = sNextPlayer;

	computerPlayer = sCPU;
	computerPts = sComputerScore;

	humanPlayer = sHuman;
	humanPts = sHumanScore;

	DisplayWins();
	aRound.ResumeRound(roundCounter, currentPlayer, nextPlayer, humanPts, computerPts, sTable, sDeck);
	roundCounter++;

	// Keep playing till winner
	while (humanPts < 21 && computerPts < 21)
	{
		// Display current scores to the player
		DisplayWins();

		// Play a round
		aRound.PlayRound(roundCounter, currentPlayer, nextPlayer, humanPts, computerPts);
		roundCounter++;
	}

	// End of game prompts
	if (humanPts == computerPts && humanPts >= 21)
	{
		std::cout << "Scores are both " << humanPts << " the tournament results in a tie!" << std::endl;
	}
	else if (humanPts > computerPts && humanPts >= 21)
	{
		std::cout << "Congratulation, you won the tournament!" << std::endl;
	}
	else if (computerPts > humanPts && computerPts >= 21)
	{
		std::cout << "The dumb robot has won the tournament. ha ha ha" << std::endl;
	}
}



// Function:	DisplayWins
// Purpose:		Displays the score to the player
// Parameters:	
// Returns:		
//		ALGORITHM
void Tournament::DisplayWins()
{
	std::cout << "=+=   CURRENT SCORE   =+=" << std::endl;
	std::cout << "      Human Points: " << humanPts << std::endl;
	std::cout << "   Computer Points: " << computerPts << std::endl << std::endl;
}



// Function:	StartRound
// Purpose:		Starts a new game
// Parameters:	
// Returns:		
//		ALGORITHM
// 1.) Call CoinFlip for players 1 and 2
// 2.) Keep playing a new round until win condition is reached
// 3.) Display winner of the tournament based on players point values
void Tournament::StartRound()
{
	// Create new round
	Round aRound;

	// Determine first player
	CoinFlip(currentPlayer, nextPlayer);

	// Keep playing till winner
	while (humanPts < 21 && computerPts < 21)
	{
		// Display current scores to the player
		DisplayWins();

		// Play a round
		aRound.PlayRound(roundCounter, currentPlayer, nextPlayer, humanPts, computerPts);
		roundCounter++;
	}

	// End of game prompts
	if (humanPts == computerPts && humanPts >= 21)
	{
		std::cout << "Scores are both " << humanPts << " the tournament results in a tie!" << std::endl;
	}
	else if (humanPts > computerPts && humanPts >= 21)
	{
		std::cout << "Congratulation, you won the tournament!" << std::endl;
	}
	else if (computerPts > humanPts && computerPts >= 21)
	{
		std::cout << "The dumb robot has won the tournament. ha ha ha" << std::endl;
	}
}



// Function:	CoinFlip
// Purpose:		To determine the first player of a new game
// Parameters:	Player *currentPlayerPointer, Player *nextPlayerPointer
// Returns:		
//		ALGORITHM
// 1.) Seed pseudo-random time
// 2.) Take a random int from time and mod it by 2 and assign each value heads or tails
// 3.) Let user call whether they think it'll be heads or tails
// 4.) If they call correctly, they play first
// 4a.)		Assign currentPointer, humanPlayer
// 4b.)		Assign nextPointer, computerPlayer
// 4c.)	Else, they play after the CPU
// 4d.)		Assign currentPointer, computerPlayer
// 4e.)		Assign nextPointer, humanPlayer
// 5.) Display results to player

void Tournament::CoinFlip(Player *&cPlayer, Player *&nPlayer)
{
	// Seed "random" time
	// Casting due to time returning a long and not an unsigned int
	srand(static_cast<unsigned int>(time(NULL)));

	// Coin flip results
	std::string coinFlipResultText;
	int coinFlipResult = rand() % 2 + 1;

	// Assign text value of flip
	if (coinFlipResult == 1) { coinFlipResultText = "heads"; }
	else { coinFlipResultText = "tails"; }

	// Coin flip prompt
	std::cout << std::endl;
	std::cout << "The first round will begin with a coin flip." << std::endl;

	// User input for call
	std::string call;
	do
	{
		std::cout << "Please call heads or tails: ";
		std::cin >> call;

		// Force user input to lowercase
		std::transform(call.begin(), call.end(), call.begin(), ::tolower);

		// Clear and ignore incorrect entries
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (call != "heads" && call != "tails");

	// Reveal results to player
	std::cout << "You called " << call << " and the coin flip was " << coinFlipResultText << "." << std::endl;

	// DELETE THIS, FOR DEBUGGING PURPOSES ONLY
	//call = coinFlipResultText;

	// Determine if the call was correct and who goes first
	if (call == coinFlipResultText)
	{
		// Assign current and next players
		std::cout << "You are playing first." << std::endl << std::endl;
		cPlayer = &humanPlayer;
		nPlayer = &computerPlayer;
	}
	else
	{
		// Assign current and next players
		std::cout << "The dumb robot is playing first." << std::endl << std::endl;
		cPlayer = &computerPlayer;
		nPlayer = &humanPlayer;
	}
}


Tournament::~Tournament()
{
}
