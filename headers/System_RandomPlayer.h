#include "Hand.h"
#include "System.h"

#ifndef SYSTEM_RANDOM_PLAYER_H
#define SYSTEM_RANDOM_PLAYER_H

class System_RandomPlayer : public System
{
	private:
		
	
	public:
		System_RandomPlayer();
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);	// Takes a decision according to all the parameters of the situation
};

#endif
