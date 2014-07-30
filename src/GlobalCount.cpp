#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/Card.h"
#include "../headers/GlobalCount.h"

GlobalCount::GlobalCount()
{
	this->reset();
}

void GlobalCount::reset()
{
	this->count = 0;
	this->remainingCards = NB_DECKS * 52;
	this->tens = NB_DECKS * 16;
	this->others = NB_DECKS * 36;
}

void GlobalCount::update(int value)
{
	this->remainingCards--;
	if (value == 10 || value == 1)
	{
		this->count--;
	}
	if (value >= 2 && value <= 6)
	{
		this->count++;
	}
	if (value == 10)
	{
		this->tens--;
	}
	if (value != 10 && value != 0)
	{
		this->others--;
	}
}

int GlobalCount::getCount()
{
	return this->count;
}

int GlobalCount::getRoughCount()
{
	if (this->remainingCards <= 1)
	{
		return 0;
	}
	return this->count / (((this->remainingCards-1) / 52) + 1);
}

int GlobalCount::getRemainingCards()
{
	return this->remainingCards;
}

int GlobalCount::getHiLoIndex()
{
	if (this->remainingCards == 0)
	{
		return 0;
	}
	return (int)((double)((double)this->count / (double)this->remainingCards) * 100);
}

int GlobalCount::getTens()
{
	return this->tens;
}

int GlobalCount::getOthers()
{
	return this->others;
}

double GlobalCount::getTenCount()
{
	this->tens = (this->tens == 0) ? 0.1 : this->tens;
	return (double)(this->others) / (double)(this->tens);
}

void GlobalCount::printStatus()
{
	char message[100];
	sprintf(message, "[count: %d, remainingCards: %d (%d), others: %d, tens: %d, (%1.2f)]\n", count, remainingCards, this->getHiLoIndex(), others, tens, this->getTenCount());
	printColor(C_YELLOW, message);
}




