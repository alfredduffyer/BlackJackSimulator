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
	
	if (boxIndex >= 0)
	{
		this->boxes[boxIndex].add(card.value);
		printf(" [%d] gets a %d, total is now %d (%s)\n", boxIndex, card.value, this->boxes[boxIndex].getValue(), this->boxes[boxIndex].getName());
		return this->boxes[boxIndex];
	}
	else
	{
		this->dealerBox->add(card.value);
		printf(" DDD gets a %d, total is now %d (%s)\n", card.value, this->dealerBox->getValue(), this->dealerBox->getName());
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
		if (box.getValue() == 0)break;
		//printf("With %d, box %d makes the decision to %d\n", box.getValue(), boxIndex, decision);
		
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
			//puts("Splitting that");
			break;
		}
	}
}

void Game::pay()
{
	int i = 0, status = 0;
	
	for (i = this->nbBoxes - 1 ; i >= 0 ; i--)
	{
		if (this->boxes[i].isFree())
		{
			continue;
		}
		
		status = this->boxes[i].getHand()->beats(this->dealerBox->getHand());
		
		printf(" [%d] has %d against %d, status is %d (%s)\n", i, this->boxes[i].getValue(), this->dealerBox->getValue(), status, this->boxes[i].getName());
		
		if (status == 0)
		{
			this->boxes[i].tie();
		}
		if (status == 1)
		{
			this->boxes[i].win();
		}
		
	}
	
	
}

void Game::play()
{
	while (1)
	{
		puts("Initializing shoe...");
		this->initShoe();
		
		while (!this->shoe->isTheEnd())
		{
			puts("Initializing turn...");
			this->initTurn();
			
			puts("-Betting...");
			this->bet();
			puts("Dealing first wave...");
			this->deal();
			
			puts("Dealing second wave...");
			this->decisions();
			
			puts("Paying players...");
			this->pay();
			
			printf("\n%d cards played, going to %d.\n\n", this->shoe->getIndex(), this->shoe->getLimit());
			sleep(1);
		}
	}
}

