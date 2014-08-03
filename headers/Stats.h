#include "Hand.h"

#ifndef STATS_H
#define STATS_H

class Stats
{
	private:
		int playerValue;
		int dealerValue;
		int softHand;
		int decisionConcerned;
		int decision;
		int handsNumber;
		int handsPlayed;
		bool* boxes;
	
	public:
		Stats(int playerValue, int dealerValue, bool softHand, int decisionConcerned, int decision, int handsNumber);
		void resetBoxes();
		int getPlayerValue();
		int getDealerValue();
		int isSoftHand();
		int getDecisionConcerned();
		int getDecision();
		int getHandsNumber();
		bool finished();
		void addBox(int boxIndex);
		void printStatus();
};

#endif
