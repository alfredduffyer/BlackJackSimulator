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
#include "../headers/System_RandomPlayer.h"

System_RandomPlayer::System_RandomPlayer() : System()
{
	this->initiate();
}

void System_RandomPlayer::initiate()
{
	
}

int System_RandomPlayer::decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown)
{
	if (dealer->getValue() && canSplit && canDoubleDown){}
	return (player->getValue() < 17) ? DRAW : STAND;
}
