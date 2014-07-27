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
#include "../headers/Box.h"
#include "../headers/Game.h"

GlobalCount count;
int Box::_stats[21][10];
bool fffffffffff = false;

int main()
{
	srand(getMilliTime());
	
	int result = 0, nbPlays = 0;
	long int totalHandsPlayed = 0;
	double average = 0;
	
	Game game(new Shoe(NB_DECKS), 5, 500, 7);
	
	while (++nbPlays)
	{
		game.init(new Shoe(NB_DECKS), 5, 500, 7);
		game.addPlayer(new Player((char*) "Don Self", 1000, 5, new System_TenCount()));
		game.addPlayer(new Player((char*) "The Player Who Never Busts", -1, 5, new System_ThePlayerWhoNeverBusts()));
		game.addPlayer(new Player((char*) "Mimic The Dealer", -1, 5, new System_Dealer()));
		game.addPlayer(new Player((char*) "The Random Player", -1, 5, new System_RandomPlayer()));
		result = game.play();
		totalHandsPlayed += (long int) result;
		if (result != 2000001 || result != 500001)
		{
			average = ((double) (average * (nbPlays-1) + result)) / ((double) nbPlays);
		}
		char message[100];
		sprintf(message, "Don Self died in %9d hands, average is %5.0f, total %5d %03d %03d\n", result, average, (int) ((totalHandsPlayed-totalHandsPlayed % 1000000) / 1000000), (int) ((totalHandsPlayed % 1000000) / 1000), (int) (totalHandsPlayed % 1000));
		if (result == 2000001 || result == 500001)
		{
			sprintf(message, "Don Self survived %9d hands, won a lot of money !\n", result);
			printColor(C_GREEN, message);
		}
		else if (true || result > 100000)
		{
			printColor(C_RED, message);
		}
		else if (result > 50000)
		{
			printColor(C_BLUE, message);
		}
		else
		{
			printf("%s", message);
		}
		
		if (STATUS) break;
		
	}
	
	return 1;
}
