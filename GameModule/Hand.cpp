#include "Hand.h"

Hand::Hand() : index(-1)
{
}

Hand::Hand(Card& c) : index(0)
{
	this->hand[index] = &c;
}

Hand::Hand(Hand& h)
{
	this->index = h.index;
	for (int i = 0; i <= index; i++)
	{
		this->hand[i] = h.hand[i];
	}
}

Hand::~Hand()
{

}


int Hand::numberOfCards()
{
	return index + 1;
}

void Hand::addCard(Card& c)
{
	if (numberOfCards() > 22)
		throw ("Main pleine");

	index++;
	this->hand[index] = &c;
}