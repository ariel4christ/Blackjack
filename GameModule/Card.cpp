#include "Card.h"

// Initialisation par défaut de la variable statique sID
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

Card::Card(const Card& c)
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

char* getStringRepresentation()
{
	switch (this->type)
	{
		case AS:
			return "|A|";
			break;
		case TWO:
			return "|2|";
			break;
		case THREE:
			return "|3|";
			break;
		case FOUR:
			return "|4|";
			break;
		case FIVE:
			return "|5|";
			break;
		case SIX:
			return "|6|";
			break;
		case SEVEN:
			return "|7|";
			break;
		case EIGHT:
			return "|8|";
			break;
		case NINE:
			return "|9|";
			break;
		case TEN:
			return "|10|";
			break;
		case JACK:
			return "|J|";
			break;
		case QUEEN:
			return "|Q|";
			break;
		case KING:
			return "|K|";
			break;
	}
}