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
