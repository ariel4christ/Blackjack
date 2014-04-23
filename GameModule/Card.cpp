#include "Card.h"

int Card::sId = 0;

Card::Card(EType t)
{
	this->sId++;
	this->id = this->sId;
	this->type = t;
}

Card::~Card()
{
}

Card::Card(Card& c)
{
	this->sId++;
	this->id = this->sId;
	this->type = c.type;
}

Card& Card::operator=(Card& c)
{
	this->type = c.type;
	return *this;
}

int Card::getValue()
{
	return (int) this->type;
}