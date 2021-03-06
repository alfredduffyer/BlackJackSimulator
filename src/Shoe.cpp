#include <stdio.h>
#include <stdlib.h>
#include "../headers/_variables.h"
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/GlobalCount.h"
#include "../headers/Shoe.h"

extern GlobalCount count;

Shoe::Shoe()
{
	this->size = NB_DECKS * 52;
	this->cards = (Card*) calloc(this->size, sizeof(Card));
	this->topIndex = 0;
	this->create();
}

void Shoe::create()
{
	int i = 0, j = 0, k = 0, currentIndex = 0;
	
	char colors[4] = {'H', 'S', 'D', 'C'};
	char titles[14] = {'\0', 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
	
	for (i = 0 ; i < this->size / 52 ; i++)
	{
		for (j = 0 ; j < 4 ; j++)
		{
			for (k = 1 ; k <= 13 ; k++)
			{
				currentIndex = i*52+j*13+k-1;
				this->cards[currentIndex].color = colors[j];
				this->cards[currentIndex].value = (k < 10) ? k : 10;
				this->cards[currentIndex].title = titles[k];
			}
		}
	}
}

void Shoe::shuffle()
{
	int i = 0, j = 0;
	Card tmp;
	
	for (i = 0 ; i < this->size ; i++)
	{
		j = random(0, this->size - 1);
		tmp = this->cards[j];
		this->cards[j] = this->cards[i];
		this->cards[i] = tmp;
	}
	
	this->topIndex = 0;
	count.reset();
}

void Shoe::burn()
{
	this->topIndex = CARDS_BURNED;
	int i = 0;
	for (i = 0 ; i < CARDS_BURNED ; i++)
	{
		count.update(0);
	}
}

void Shoe::reset()
{
	int tmp = 0;
	this->shuffle();
	this->burn();
	this->dealingLimit = (tmp = this->size * (100-WASTE_PROPORTION) / 100) > CARDS_BURNED ? tmp : CARDS_BURNED + 1;
}

void Shoe::print()
{
	int i = 0;
	for (i = 0 ; i < this->size ; i++)
	{
		if (i % 52 == 0)
		{
			puts("\n");
			printHr();
		}
		
		printf("%c", this->cards[i].title);
		printCardColor(this->cards[i].color);
	}
}

int Shoe::getSize()
{
	return this->size;
}

int Shoe::getLimit()
{
	return this->dealingLimit;
}

int Shoe::getIndex()
{
	return this->topIndex;
}

bool Shoe::isTheEnd()
{
	return (this->topIndex >= this->dealingLimit);
}

Card Shoe::top()
{
	if (this->topIndex >= this->size) {
		this->reset();
	}
	count.update(this->cards[this->topIndex].value);
	return this->cards[this->topIndex++];
}
