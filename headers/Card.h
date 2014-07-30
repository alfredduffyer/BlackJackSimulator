#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"
#include "print.h"

#ifndef CARD_H
#define CARD_H

typedef struct Card Card;

struct Card
{
	int value;		// 1 - 10
	char title;		// A 2-9 0 J Q K
	char color;		// S-Spades, H-Heart, C-Clubs, D-Diamonds
};

#endif
