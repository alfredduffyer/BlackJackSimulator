#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/_config.h"
#include "../headers/functions.h"
#include "../headers/print.h"
#include "../headers/Card.h"
#include "../headers/GlobalCount.h"
#include "../headers/Hand.h"

Hand::Hand()
{
	this->reset();
}

void Hand::reset()
{
	this->value = 0;
	this->softValue = 0;
	this->size = 0;
	this->pair = false;
}

int Hand::add(int value)
{
	this->size++;
	if (this->size == 2 && this->softValue == value)
	{
		this->pair = true;
	}
	else
	{
		this->pair = false;
	}
	if (value == 1)
	{
		this->value += (this->value + 11 > 21) ? 1 : 11;
		this->softValue += 1;
	}
	else
	{
		this->value += value;
		this->softValue += value;
	}
	
	return this->value;
}

bool Hand::isSoft()
{
	return (this->value != this->softValue && this->value <= 21);
}

bool Hand::isNatural()
{
	return (this->value == 21 && this->size == 2);
}

bool Hand::isBusted()
{
	return this->value > 21;
}

bool Hand::isPair()
{
	return this->pair;
}

int Hand::beats(Hand* dealer)
{
	if (this->isBusted())
	{
		return -1;
	}
	
	if (dealer->isBusted())
	{
		return 1;
	}
	
	if (this->isNatural() && !dealer->isNatural())
	{
		return 1;
	}
	
	if (dealer->isNatural() && !this->isNatural())
	{
		return -1;
	}
	
	if (this->value > dealer->value)
	{
		return 1;
	}
	
	if (dealer->value > this->value)
	{
		return -1;
	}
	
	return 0;
	
}

int Hand::getValue()
{
	return this->value;
}

int Hand::getSoftValue()
{
	return this->softValue;
}

int Hand::getSize()
{
	return this->size;
}


