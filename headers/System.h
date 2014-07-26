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

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
	protected:
		double** hardStanding;		//  8 x 10
		double** softStanding;		//  3 x 10
		double** hardDoublingDown;	// 10 x 10
		double** softDoublingDown;	//  9 x 10
		double** splittingPairs;	// 10 x 10
		double comparator;
	
	public:
		System();
		~System();
		bool split(int player, int dealer);
		bool doubleDown(int player, int dealer, bool soft);
		bool draw(int player, int dealer, bool soft);
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);
		virtual void initiate() = 0;
		virtual int howManyHands(int maxHands);
		int bet();
		void updateComparator();
};

#endif
