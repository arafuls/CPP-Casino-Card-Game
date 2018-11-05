#include "Build.h"



Build::Build()
{
	trueSum = NULL;
}



// Function:	Append
// Purpose:		Set a new build with defined parameters
// Parameters:	vector<Card> setOfCards, Card buildCard, string playerNameOwningThisSet, int valueYouAreBuildingTo
// Returns:		
void Build::Append(std::vector<Card> &set, Card card, std::string setOwner, int val)
{
	buildSet = set;
	buildCard = card;
	owner = setOwner;
	trueSum = val;
}



// Function:	Append
// Purpose:		Set a new build with defined parametets from save file
// Parameters:	vector<Card> setOfCards, string playerNameOwningThisSet
// Returns:		
void Build::Append(std::vector<Card>& set, std::string setOwner)
{
	buildSet = set;
	owner = setOwner;

	// Tracks sum of the cards, two sums due to aces being 14 or 1
	// for each card
	for (unsigned i = 0; i < set.size(); i++)
	{
		// add up the sum
		if (set[i].GetRankAsInt() == 14) { softSum += 1; }
		else { softSum += set[i].GetRankAsInt(); }

		hardSum += set[i].GetRankAsInt();
	}
}





// Function:	~Build
// Purpose:		Release resources upon deconstruction
// Parameters:	
// Returns:		
Build::~Build()
{
	buildSet.clear();
	owner.clear();
	buildCard.~Card();
	trueSum = NULL;
}
