#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"
#include "GlobalCount.h"

#ifndef HAND_H
#define HAND_H

class Hand
{
	private:
		int value;
		int softValue;
		int size;
		bool pair;
		bool isSplitted;
	
	public:
		Hand();
		void reset();
		int add(int value);
		bool isSoft();
		bool isNatural();
		bool isPair();
		int getValue();
		int getSoftValue();
		int getSize();
		bool isBusted();
		int beats(Hand* hand);
		void setSplitted(bool isSplitted);
};

#endif
