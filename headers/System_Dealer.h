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
#include "System_BasicStrategy.h"

#ifndef SYSTEM_DEALER_H
#define SYSTEM_DEALER_H

class System_Dealer : public System
{
	protected:
		
	
	private:
		void initiate();
	
	public:
		System_Dealer();
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);
};

#endif
