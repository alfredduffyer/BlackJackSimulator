#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/Card.h"
#include "../headers/GlobalCount.h"

GlobalCount::GlobalCount()
{
	GlobalCount(52);
}

GlobalCount::GlobalCount(int remainingCards)
{
	this->reset(remainingCards);
}

void GlobalCount::reset(int remainingCards)
{
	this->count = 0;
	this->remainingCards = remainingCards;
	this->tens = 0;
	this->others = 0;
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


