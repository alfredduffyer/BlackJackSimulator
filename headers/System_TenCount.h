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

#ifndef SYSTEM_TEN_COUNT_H
#define SYSTEM_TEN_COUNT_H

class System_TenCount : public System
{
	protected:
		
	
	private:
		void initiate_hardStandingNumbers();
		void initiate_softStandingNumbers();
		void initiate_hardDoublingDown();
		void initiate_softDoublingDown();
		void initiate_splittingPairs();
		void initiate();
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);
		virtual int howManyHands(int maxHands);
		virtual bool insure();
		virtual int bet();
	
	public:
		System_TenCount();
};

#endif
