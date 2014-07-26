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
#include <string.h>

extern GlobalCount count;

Game::Game(Shoe* shoe)
{
	this->init(shoe, 5, 500, 7);
}

Game::Game(Shoe* shoe, int min, int max)
{
	this->init(shoe, min, max, 7);
}

Game::Game(Shoe* shoe, int min, int max, int nbBoxes)
{
	this->init(shoe, min, max, nbBoxes);
}

Game::~Game()
{
	
}

void Game::init(Shoe* shoe, int min, int max, int nbBoxes)
{
	this->shoe = shoe;
	this->min = min;
	this->max = max;
	this->nbBoxes = nbBoxes;
	this->nbPlayers = 0;
	
	this->players = (Player**) malloc(this->nbBoxes * sizeof(Player*));
	this->boxes = (Box*) malloc(this->nbBoxes * sizeof(Box));
	
	this->dealer = new Player((char*) "Dealer", -1, -1, new System_Dealer());
	this->dealerBox = new Box();
}

int Game::addPlayer(Player* player)
{
	this->players[this->nbPlayers] = player;
	return this->nbPlayers++;
}

int Game::removePlayer()
{
	return --this->nbPlayers;
}

void Game::resetBoxes()
{
	int i = 0;
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		this->boxes[i].reset();
	}
	this->dealerBox->reset();
}


void Game::initShoe()
{
	this->shoe->reset();
}

void Game::initTurn()
{
	this->resetBoxes();
	this->dealerBox->take(this->dealer, 0);
}

int Game::howManyHands(bool counter)
{
	if (counter)
	{
		int total = PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5 + PLAYING_6 + PLAYING_7 + PLAYING_8 + PLAYING_9 + PLAYING_10;
		int rand = random(1, total);
		
		if (rand <= PLAYING_1) return 1;
		if (rand <= PLAYING_1 + PLAYING_2) return 2;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3) return 3;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4) return 4;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5) return 5;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5 + PLAYING_6) return 6;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5 + PLAYING_6 + PLAYING_7) return 7;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5 + PLAYING_6 + PLAYING_7 + PLAYING_8) return 8;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5 + PLAYING_6 + PLAYING_7 + PLAYING_8 + PLAYING_9) return 9;
		if (rand <= PLAYING_1 + PLAYING_2 + PLAYING_3 + PLAYING_4 + PLAYING_5 + PLAYING_6 + PLAYING_7 + PLAYING_8 + PLAYING_9 + PLAYING_10) return 10;
		return 1;
	}
	
	if (random(1, 100) > GAME_PLAYING) return 0;
	return (random(1, 100) <= PLAYING_ON_TWO_BOXES) ? 2 : 1;
}

void Game::bet()
{
	int i = 0, j = 0, k = 0, handsnumber = this->howManyHands(true), currentBox = 0;
	
	for (i = 0 ; i < handsnumber ; i++)
	{
		currentBox = (this->nbBoxes/2 + i) % this->nbBoxes;
		
		if (this->boxes[currentBox].isFree())
		{
			this->boxes[currentBox].take(this->players[0], this->players[0]->bet());
		}
	}
	
	currentBox = random(0, this->nbBoxes-1);
	
	for (i = 1 ; i < this->nbPlayers ; i++)
	{
		handsnumber = this->howManyHands(false);
		
		for (j = 0 ; j < handsnumber ; j++)
		{
			for (k = 0 ; k < 3 ; k++)
			{
				if (this->boxes[currentBox].isFree())
				{
					this->boxes[currentBox].take(this->players[i], this->players[i]->bet());
					break;
				}
				currentBox = (currentBox + (this->nbBoxes / 2 + 1)) % this->nbBoxes;
			}
		}
	}
	
	if (DEBUG)
	{
		for (i = 0 ; i < this->nbBoxes ; i++)
		{
			printf(" [%d] total bet is %d", i, this->boxes[i].getBet());
			if (!this->boxes[i].isFree())
			{
				printf(" (%s)", this->boxes[i].getName());
			}
			puts("");
		}
	}
	
}

void Game::deal()
{
	int i = 0;
	
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		this->deal(i);
	}
	
	this->deal(-1);
	
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		this->deal(i);
	}
}

Box Game::deal(int boxIndex)
{
	Card card = this->shoe->top();
	char message[100];
	
	if (boxIndex >= 0)
	{
		this->boxes[boxIndex].add(card.value);
		sprintf(message, " [%d] gets a %d, total is now %d (%s)\n", boxIndex, card.value, this->boxes[boxIndex].getValue(), this->boxes[boxIndex].getName());
		if (DEBUG)printColor(C_RED + (boxIndex % 7), message);
		return this->boxes[boxIndex];
	}
	else
	{
		this->dealerBox->add(card.value);
		if (DEBUG)printf(" DDD gets a %d, total is now %d (%s)\n", card.value, this->dealerBox->getValue(), this->dealerBox->getName());
		return *this->dealerBox;
	}
}

void Game::decisions()
{
	int i = 0;
	
	for (i = 0 ; i < this->nbBoxes ; i++)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		this->decision(this->boxes[i], i);
	}
	
	this->decision(*this->dealerBox, -1);
}

void Game::decision(Box box, int boxIndex)
{
	int decision = 0;
	
	while(!box.isNatural() && !box.isBusted() && (decision = box.decision(this->dealerBox->getHand(), true, true)) != STAND)
	{
		if (box.getValue() == 0) break;
		
		if (decision == DRAW)
		{
			box = this->deal(boxIndex);
		}
		
		if (decision == DOUBLEDOWN)
		{
			box = this->deal(boxIndex);
			break;
		}
		
		if (decision == SPLIT)
		{
			if (DEBUG)printColor(C_YELLOW, (char*) "  --> Splitting that (Skipped)\n");
			break;
		}
	}
}

void Game::pay()
{
	int i = 0, status = 0;
	char text1[100], text2[50], text3[50];
	
	for (i = this->nbBoxes - 1 ; i >= 0 ; i--)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		status = this->boxes[i].getHand()->beats(this->dealerBox->getHand());
		
		sprintf(text1, " [%d] has %d against %d, status is %d (%s)\n", i, this->boxes[i].getValue(), this->dealerBox->getValue(), status, this->boxes[i].getName());
		sprintf(text2, "  --> Had %1.1f, has now ", this->boxes[i].getStack());
		
		if (status == 0)
		{
			this->boxes[i].tie();
		}
		if (status == 1)
		{
			this->boxes[i].win();
		}
		
		sprintf(text3, "%1.1f\n", this->boxes[i].getStack());
		
		if (DEBUG && strcmp(this->boxes[i].getName(), "Don Self") == 0)
		{
			printColor(C_RED, text1);
			printColor(C_RED, text2);
			printColor(C_RED, text3);
		}
		else if (DEBUG)
		{
			printf("%s", text1);
			printf("%s", text2);
			printf("%s", text3);
		}
	}
	
	
}

void Game::play()
{
	while (1)
	{
		if (DEBUG)puts("Initializing shoe...");
		this->initShoe();
		
		while (!this->shoe->isTheEnd())
		{
			if (DEBUG)puts("Initializing turn...");
			this->initTurn();
			
			if (DEBUG)puts("-Betting...");
			this->bet();
			if (DEBUG)puts("Dealing first wave...");
			this->deal();
			
			if (DEBUG)puts("Dealing second wave...");
			this->decisions();
			
			if (DEBUG)puts("Paying players...");
			this->pay();
			
			if (DEBUG)printf("\n%d cards played, going to %d.\n\n", this->shoe->getIndex(), this->shoe->getLimit());
			
			for (int i = 0 ; i < this->nbBoxes ; i++)
			{
				if (!this->boxes[i].isFree() && strcmp(this->boxes[i].getName(), "Don Self") == 0)
				{
					printf("Don Self has now %1.1f\n", this->boxes[i].getStack());
					if (this->boxes[i].getStack() < 5)
					{
						return;
					}
					break;
				}
			}
			
			//sleep(1);
		}
	}
}

