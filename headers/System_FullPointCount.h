#include "Hand.h"
#include "System.h"

#ifndef SYSTEM_FULL_POINT_COUNT_H
#define SYSTEM_FULL_POINT_COUNT_H

class System_FullPointCount : public System
{
	private:
		
	
	public:
		System_FullPointCount();
		void initiate_hardStandingNumbers();		// Fills the Hard Standing Numbers table
		void initiate_softStandingNumbers();		// Fills the Soft Standing Numbers table
		void initiate_hardDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_softDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_splittingPairs();			// Fills the Splitting Pairs table
		void initiateTables();				// Calls the initiate_xxx methods
		virtual void updateComparator();		// Updates the comparator according to the counting numbers
		virtual int howManyHands(int maxHands);		// Calculates how many hands the player should be playing for a turn
		virtual int bet();				// Calculates how many units the player should be betting for a turn
		virtual bool insure();				// true if the player should insure, false otherwise
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);		// Gives a decision if there is an exception with the situation, 0 otherwise
};

#endif
