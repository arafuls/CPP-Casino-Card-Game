// TABLE CLASS
// This class controls everything that happens in the table's jurisdiction

#pragma once
#include "Card.h"
#include "Build.h"
#include "Build.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

class Table
{
public:
	Table();
	
	// Varriables
	std::vector<Card> tableHand;
	std::vector<Build> allBuilds;

	// Functions
	void PrintHand(std::vector<Card> playerHand, std::string playerName);		// Display players hands
	void PrintTable();									// Display table cards

	bool SetHasCard(std::string cardName, std::vector<Card> &buildSet, std::vector<Card> &cardSet); // Adds cardSet to buildSet if condition is true
	bool TableHasCard(std::string cardName, Card &card);
	bool TableHasCard(std::string cardName, int &idx);
	void EraseCard(std::string cardName);

	bool CheckCapture(std::vector<Card> playerHand, std::string playerName);	// Assign canCapture if building is possible
	bool CheckTrail(std::vector<Card> playerHand, std::string playerName);		// Assign canTrail if building is possible

	bool IsMatch(Card x, Card y);						// Return true if both cards have matching rank
	void AddTrailCard(Card trail);						// Adds trail card to table hand
	void Append(Build playerBuild);						// Adds build to list of builds

	// https://www.geeksforgeeks.org/find-distinct-subsets-given-set/
	bool ReturnSubset(std::vector<Card> cards, int buildTarget, std::vector<Card> &currentBuild);		// Function to return a subset for a build
	bool FindAllSubsets(std::vector<Card> cards, int buildTarget);		// Function to find all subsets for a build
	std::vector<std::string> Split(const std::string &s, char delim);	// Utility function for AllSubsets functions

	~Table();
};

