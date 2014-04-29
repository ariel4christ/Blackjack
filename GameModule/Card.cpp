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
	switch (this->type)
	{
	case AS:
		return 1;
	case TWO:
		return 2;
	case THREE:
		return 3;
	case FOUR:
		return 4;
	case FIVE:
		return 5;
	case SIX:
		return 6;
	case SEVEN:
		return 7;
	case EIGHT:
		return 8;
	case NINE:
		return 9;
	case TEN:
		return 10;
	case JACK:
		return 10;
	case QUEEN:
		return 10;
	case KING:
		return 10;
	}
}

EType Card::getType()
{
	return this->type;
}
