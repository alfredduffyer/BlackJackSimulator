#include "Hand.h"
#include "System.h"

#ifndef SYSTEM_BASIC_STRATEGY_H
#define SYSTEM_BASIC_STRATEGY_H

class System_BasicStrategy : public System
{
	private:
		
	
	public:
		System_BasicStrategy();				// Calls initiateTables
		virtual bool insure();				// true if the player should insure, false otherwise
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);	// Gives a decision if there is an exception with the situation, 0 otherwise
		void initiateTables();				// Calls the initiate_xxx methods
		void initiate_hardStandingNumbers();		// Fills the Hard Standing Numbers table
		void initiate_softStandingNumbers();		// Fills the Soft Standing Numbers table
		void initiate_hardDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_softDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_splittingPairs();			// Fills the Splitting Pairs table
};

#endif
