#include <stdio.h>
#include <stdlib.h>
#include "../headers/_variables.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/GlobalCount.h"
#include "../headers/Box.h"

extern GlobalCount count;
extern bool FORCEDEBUG;

Box::Box()
{
	this->reset();
}

void Box::reset()
{
	this->player = NULL;
	this->bet = 0;
	this->insurance = false;
	this->hand.reset();
}

void Box::take(Player* player, int bet)
{
	this->take(player, bet, false);
}

void Box::take(Player* player, int bet, bool isSplitted)
{
	this->player = player;
	this->bet = bet;
	this->hand.setSplitted(isSplitted);
}

bool Box::insure()
{
	if (this->player->insure( ((double)this->bet) / ((double)2) ))
	{
		this->player->betInsurance( ((double)this->bet) / ((double)2) );
		return this->insurance = true;
	}
	return false;
}

int Box::doubleDown()
{
	int bet = this->player->betAmount(this->bet);
	this->bet += bet;
	return bet;
}

int Box::decision(Hand* dealerHand, bool canSplit, bool canDoubleDown)
{
	if ((DEBUG || FORCEDEBUG)) count.printStatus();
	int decision = this->player->decision(&this->hand, dealerHand, canSplit && this->hand.isPair(), canDoubleDown && this->hand.getSize() == 2);
	
	return decision;
}

void Box::payInsurance()
{
	if (this->hasInsured()) {
		this->player->win(this->bet * 1.5);
	}
}

void Box::tie()
{
	this->player->win(this->bet);
}

void Box::win()
{
	this->player->win(this->bet * ( (this->hand.isNatural()) ? 2.5 : 2 ));
}

bool Box::isFree()
{
	return (this->bet == 0 || this->player == NULL);
}

bool Box::hasInsured()
{
	return this->insurance;
}

int Box::getBet()
{
	return this->bet;
}
