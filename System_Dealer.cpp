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

System_Dealer::System_Dealer() : System()
{
	this->initiate();
}

void System_Dealer::initiate()
{
	
}

int System_Dealer::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (dealer->getValue() && canSplit && canDoubleDown){}
	return (player->getValue() < 17) ? DRAW : STAND;
}
