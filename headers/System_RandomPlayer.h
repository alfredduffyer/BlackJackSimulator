#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"
#include "GlobalCount.h"
#include "Hand.h"
#include "Shoe.h"
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
