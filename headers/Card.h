#ifndef CARD_H
#define CARD_H

typedef struct Card Card;

struct Card
{
	int value;	// 1 - 10
	char title;	// A 2-9 0 J Q K
	char color;	// S-Spades, H-Heart, C-Clubs, D-Diamonds
};

#endif
