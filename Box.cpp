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
#include "System_Dealer.h"
#include "Player.h"
#include "Box.h"

Box::Box()
{
	this->reset();
}

void Box::reset()
{
	this->player = NULL;
	this->bet = 0;
	this->hand.reset();
}

void Box::add(int value)
{
	this->hand.add(value);
}

void Box::take(Player* player, int bet)
{
	this->player = player;
	this->bet = bet;
}

bool Box::isFree()
{
	return (this->bet == 0 || this->player == NULL);
}

bool Box::isBusted()
{
	return this->hand.getValue() > 21;
}

char* Box::getName()
{
	return this->player->getName();
}

double Box::getStack()
{
	return this->player->getStack();
}

void Box::tie()
{
	this->player->win(this->bet);
}

void Box::win()
{
	this->player->win(this->bet * ( (this->isNatural()) ? 2.5 : 2 ));
}

bool Box::isNatural()
{
	return this->hand.isNatural();
}

int Box::getValue()
{
	return this->hand.getValue();
}

int Box::getBet()
{
	return this->bet;
}

Hand* Box::getHand()
{
	return &this->hand;
}

int Box::decision(Hand* dealerHand, bool canSplit, bool canDoubleDown)
{
	return this->player->decision(&this->hand, dealerHand, canSplit, canDoubleDown);
}



