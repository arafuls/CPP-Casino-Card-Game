#include "Player.h"



Player::Player()
{
	// Init player data members
	name.clear();
	myHand.clear();
	pile.clear();
}


void Player::Play(Table &table)
{
}



// Function:	GetHand
// Purpose:		Gets hand of the user
// Parameters:	
// Returns:		vector<Card> playersHand
//		ALGORITHM
std::vector<Card> Player::GetHand()
{
	return std::vector<Card>(myHand);
}



// Function:	PlayerHasCard
// Purpose:		Validates if player has a specified card
// Parameters:	string cardName, Card &card
// Returns:		Returns a bool representing if the user possesses the passed in card
bool Player::PlayerHasCard(std::string cardName, Card &card)
{
	// Look for the card name in players hand
	for (unsigned i = 0; i < myHand.size(); i++)
	{
		// Get card in hand as (i.e. JD, 5C)
		std::string tmpCard = myHand[i].GetRank() + myHand[i].GetSuit();

		// Valid card selected
		if (tmpCard == cardName) 
		{ 
			card = myHand[i];
			return true; 
		}
	}

	return false;
}



// Function:	CheckBuildSum
// Purpose:		Validates that the buildSet adds up to the overall value of the buildCard
// Parameters:	Card buildCard, vector<Card> currentBuildSet, int &buildSum
// Returns:		Returns a bool representing if the buildSet adds up to the buildCard's value
bool Player::CheckBuildSum(Card buildCard, std::vector<Card> currentBuildSet, int &buildSum)
{
	// Check if those cards add up to the sum of the build card
	int softSum = 0;
	int hardSum = 0;
	for (unsigned i = 0; i < currentBuildSet.size(); i++)
	{
		// Account for Aces
		if (currentBuildSet[i].GetRankAsInt() == 14) { softSum += 1; }
		else { softSum += currentBuildSet[i].GetRankAsInt(); }

		hardSum += currentBuildSet[i].GetRankAsInt();
	}

	// Make sure sum of cards add up
	buildSum = buildCard.GetRankAsInt();
	if (buildSum != softSum && buildSum != hardSum)
	{
		if (name == "Human") { std::cout << "Sum of the cards selected do not equal the value of the build card!" << std::endl; }
		return false;
	}

	return true;
}



Player::~Player()
{
}
