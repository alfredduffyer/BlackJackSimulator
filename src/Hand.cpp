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
	this->isSplitted = false;
}

int Hand::add(int value)
{
	this->size++;
	
	this->pair = (this->size == 2 && this->softValue == value);
	
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
	
	return this->getValue();
}

int Hand::getValue()
{
	return (this->value > 21) ? this->softValue : this->value;
}

int Hand::getSoftValue()
{
	return this->softValue;
}

int Hand::getSize()
{
	return this->size;
}

bool Hand::isSoft()
{
	return (this->value != this->softValue && this->value <= 21);
}

bool Hand::isNatural()
{
	return (!this->isSplitted && this->size == 2 && this->value == 21);
}

bool Hand::isPair()
{
	return this->pair;
}

bool Hand::isBusted()
{
	return this->getValue() > 21;
}

void Hand::setSplitted(bool isSplitted)
{
	this->isSplitted = isSplitted;
}

int Hand::beats(Hand* dealer)
{
	if (this->isBusted()) {
		return -1;
	}
	
	if (dealer->isBusted()) {
		return 1;
	}
	
	if (this->isNatural() && !dealer->isNatural()) {
		return 1;
	}
	
	if (dealer->isNatural() && !this->isNatural()) {
		return -1;
	}
	
	if (this->getValue() > dealer->getValue()) {
		return 1;
	}
	
	if (dealer->getValue() > this->getValue()) {
		return -1;
	}
	
	return 0;
}
