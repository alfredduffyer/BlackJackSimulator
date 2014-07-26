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
#include "../headers/Player.h"
#include "../headers/Box.h"
#include "../headers/Game.h"

GlobalCount count;
int Box::_stats[21][10];
bool fffffffffff = false;

int main()
{
	srand(getMilliTime());
	
	Player* self = new Player((char*) "Don Self", 1000, 5, new System_BasicStrategy());
	
	//puts("Instanciating Game...");
	Game game(new Shoe(1), 5, 500, 7);
	
	//puts("Adding main player...");
	game.addPlayer(self);
	//puts("Adding a BS player...");
	game.addPlayer(new Player((char*) "Michel", -1, 5, new System_BasicStrategy()));
	//puts("Adding another BS player...");
	game.addPlayer(new Player((char*) "Paul", -1, 5, new System_BasicStrategy()));
	//puts("Adding another BS player...");
	game.addPlayer(new Player((char*) "Bartangue", -1, 5, new System_BasicStrategy()));
	
	//puts("Playing...");
	game.play();
	
	return 1;
}
