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

#ifndef SYSTEM_THE_PLAYER_WHO_NEVER_BUSTS_H
#define SYSTEM_THE_PLAYER_WHO_NEVER_BUSTS_H

class System_ThePlayerWhoNeverBusts : public System
{
	private:
		
	
	public:
		System_ThePlayerWhoNeverBusts();
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);	// Takes a decision according to all the parameters of the situation
};

#endif
