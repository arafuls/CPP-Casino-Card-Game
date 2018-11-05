// BUILD CLASS
// This class was made to hold a build and the name of the player owning it

#pragma once
#include "Card.h"
#include <vector>

class Build
{
public:
	// Variables
	std::vector<Card> buildSet;
	std::string owner;
	Card buildCard;
	int trueSum;
	int hardSum;
	int softSum;

	// Functions
	Build();
	void Append(std::vector<Card> &set, Card card, std::string setOwner, int val);
	void Append(std::vector<Card> &set, std::string setOwner);
	~Build();

private:
};

