#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/Card.h"
#include "../headers/GlobalCount.h"
#include "../headers/Hand.h"
#include "../headers/Shoe.h"
#include "../headers/System.h"
#include "../headers/System_BasicStrategy.h"
#include "../headers/System_Dealer.h"
#include "../headers/System_RandomPlayer.h"
#include "../headers/System_ThePlayerWhoNeverBusts.h"
#include "../headers/System_SimplePointCount.h"
#include "../headers/System_FullPointCount.h"
#include "../headers/System_TenCount.h"
#include "../headers/Player.h"

Player::Player(char* name, double stack, int unit, System* system)
{
	this->name = (char*) malloc(sizeof(char)*(strlen(name) + 1));
	sprintf(this->name, "%s", name);
	this->name[strlen(name)] = '\0';
	this->stack = stack;
	this->unit = unit;
	this->system = system;
}

int Player::howManyHands(int maxHands)
{
	return this->system->howManyHands(maxHands);
}

char* Player::getName()
{
	return this->name;
}

int Player::bet()
{
	return this->bet(this->system->bet());
}

bool Player::insure(double amount)
{
	return (this->stack >= amount && this->system->insure());
}

int Player::bet(int bet)
{
	bet *= this->unit;
	
	if (this->stack == -1)
	{
		return bet;
	}
	
	if (this->stack >= bet)
	{
		this->stack -= bet;
		return bet;
	}
	
	return 0;
}

int Player::betAmount(int bet)
{
	return this->bet(bet / this->unit);
}

void Player::betInsurance(double amount)
{
	this->stack -= amount;
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

