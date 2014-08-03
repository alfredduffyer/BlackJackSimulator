#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/print.h"
#include "../headers/Stats.h"

Stats::Stats(int playerValue, int dealerValue, bool softHand, int decisionConcerned, int decision, int handsNumber)
{
	this->playerValue = playerValue;
	this->dealerValue = dealerValue;
	this->softHand = softHand;
	this->decisionConcerned = decisionConcerned;
	this->decision = decision;
	this->handsNumber = handsNumber;
	this->handsPlayed = 0;
	this->boxes = (bool*) calloc((MAX_SPLIT+1) * NB_BOXES, sizeof(bool));
	this->resetBoxes();
	this->wins = 0;
	this->loses = 0;
	this->ties = 0;
}

void Stats::resetBoxes()
{
	for (int i = 0 ; i < (MAX_SPLIT+1) * NB_BOXES ; i++)
	{
		this->boxes[i] = false;
	}
}

int Stats::getPlayerValue()
{
	return this->playerValue;
}

int Stats::getDealerValue()
{
	return this->dealerValue;
}

int Stats::isSoftHand()
{
	return this->softHand;
}

int Stats::getDecisionConcerned()
{
	return this->decisionConcerned;
}

int Stats::getDecision()
{
	return this->decision;
}

int Stats::getHandsNumber()
{
	return this->handsNumber;
}

void Stats::addBox(int boxIndex)
{
	if (this->boxes[boxIndex])
	{
		return;
	}
	this->boxes[boxIndex] = true;
	this->handsPlayed++;
}

bool Stats::isConcerned(int boxIndex)
{
	return this->boxes[boxIndex];
}

bool Stats::finished()
{
	return false;
}

void Stats::printStatus()
{
	system("clear");
	double total = this->handsPlayed ? ((double) this->handsPlayed) : 100;
	printHr();
	printf("Hands played : %9d\n", this->handsPlayed);
	printf("               %9d\n", this->handsNumber);
	printf("Wins :  %9d (%2.1f %%)\n", this->wins, this->wins / total * 100);
	printf("Loses : %9d (%2.1f %%)\n", this->loses, this->loses / total * 100);
	printf("Ties :  %9d (%2.1f %%)\n", this->ties, this->ties / total * 100);
	printf("Interest index :  %f", (double)this->wins - (double)this->loses);
	printHr();
}

void Stats::update(int boxIndex, int status)
{
	this->boxes[boxIndex] = false;
	if (status == 1)
	{
		this->wins++;
	}
	if (status == 0)
	{
		this->ties++;
	}
	if (status == -1)
	{
		this->loses++;
	}
}
