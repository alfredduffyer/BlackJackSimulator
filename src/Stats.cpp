#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
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

bool Stats::finished()
{
	return false;
}

void Stats::printStatus()
{
	puts("Youyou");
}
