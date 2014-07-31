#include "Hand.h"
#include "System.h"

#ifndef SYSTEM_DEALER_H
#define SYSTEM_DEALER_H

class System_Dealer : public System
{
	private:
		
	
	public:
		System_Dealer();
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);	// Takes a decision (draws on 16, stands on all 17's)
};

#endif
