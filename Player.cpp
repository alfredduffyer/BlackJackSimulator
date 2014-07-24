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

Player::Player(char* name, double stack, int unit, System* system)
{
	this->name = (char*) malloc(sizeof(char)*(strlen(name) + 1));
	sprintf(this->name, "%s", name);
	this->name[strlen(name)] = '\0';
	this->stack = stack;
	this->unit = unit;
	this->system = system;
}

char* Player::getName()
{
	return this->name;
}

int Player::bet()
{
	return this->bet(this->system->bet());
}

int Player::bet(int bet)
{
	bet *= this->unit;
	
	if (this->stack != -1 && this->stack >= bet)
	{
		this->stack -= bet;
	}
	
	return bet;
}

void Player::win(double amount)
{
	if (this->stack == -1)
	{
		return;
	}
	this->stack += amount;
}

double Player::getStack()
{
	return this->stack;
}

int Player::getUnit()
{
	return this->unit;
}

int Player::decision(Hand* playerHand, Hand* dealerHand, bool canSplit, bool canDoubleDown)
{
	return this->system->decision(playerHand, dealerHand, canSplit, canDoubleDown);
}

Player::~Player()
{
	
}


