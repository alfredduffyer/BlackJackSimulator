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
#include "Game.h"

GlobalCount count;

int main()
{
	srand(time(NULL));
	
	Player* self = new Player((char*) "Don Self", 200, 5, new System_BasicStrategy());
	
	puts("Instanciating Game...");
	Game game(new Shoe(1), 5, 500, 7);
	
	puts("Adding main player...");
	game.addPlayer(self);
	puts("Adding a BS player...");
	game.addPlayer(new Player((char*) "Michel", -1, 5, new System_BasicStrategy()));
	puts("Adding another BS player...");
	game.addPlayer(new Player((char*) "Paul", -1, 5, new System_BasicStrategy()));
	puts("Adding another BS player...");
	game.addPlayer(new Player((char*) "Bartangue", -1, 5, new System_BasicStrategy()));
	
	puts("Playing...");
	game.play();
	
	return 1;
}
