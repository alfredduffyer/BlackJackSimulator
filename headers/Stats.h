#include <stdio.h>
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
		int goal;
		int handsPlayed;
		bool* boxes;
		int wins;
		int loses;
		int ties;
		int startTime;
		int lastHandsPlayed;
		int lastTotalHandsPlayed;
		double lastTime;
		int logFile;
	
	public:
		Stats();
		~Stats();
		void init(int playerValue, int dealerValue, bool softHand, int decisionConcerned, int decision, int handsNumber, char* filename);
		void resetBoxes();
		int getPlayerValue();
		int getDealerValue();
		int isSoftHand();
		int getDecisionConcerned();
		int getDecision();
		int getGoal();
		bool finished();
		void addBox(int boxIndex);
		bool isConcerned(int boxIndex);
		void printStatus(int handsNumber);
		void printStatus(int handsNumber, bool doClear);
		void update(int boxIndex, int status);
		void setTime();
		void write(int handsPlayed);
};

#endif
