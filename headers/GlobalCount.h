#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"

#ifndef GLOBALCOUNT_H
#define GLOBALCOUNT_H

class GlobalCount
{
	private:
		int count;
		int remainingCards;
		int tens;
		int others;
	
	public:
		GlobalCount();
		GlobalCount(int remainingCards);
		void reset(int remainingCards);
		void update(int value);
		int getCount();
		int getRemainingCards();
		int getHiLoIndex();
		int getTens();
		int getOthers();
		double getTenCount();
};

#endif
