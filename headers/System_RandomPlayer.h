#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
	protected:
		
	
	private:
		void initiate();
	
	public:
		System_RandomPlayer();
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);
};

#endif
