#include "Hand.h"

using namespace std;


Hand::Hand()
{

}

Hand::Hand(Card& c)
{
	Hand();
	this->hand.push_back(&c);
}

Hand::Hand(Hand& h)
{
	this->hand.clear();
	for (unsigned int i = 0; i < h.hand.size(); i++)
	{
		this->hand.push_back(h.hand[i]);
	}
}

Hand::~Hand()
{
}


int Hand::numberOfCards()
{
	return this->hand.size();
}

vector<Card*> Hand::getCards()
{
	return this->hand;
}

void Hand::addCard(Card& c)
{
	if (numberOfCards() > 22)
		throw (new exception("Main pleine"));

	this->hand.push_back(&c);
}

bool Hand::isMultiValued()
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		// Si la valeur de la main est > 11, alors la deuxième valeur de la main est > 21
		if (this->hand[i]->getType() == AS && this->getValue1() <= 11)
		{
			return true;
		}
	}

	return false;
}

int Hand::getValue1()
{
	int sum = 0;
	for (unsigned int i = 0; i < this->hand.size(); i++)
		sum += this->hand[i]->getValue();

	return sum;
}

int Hand::getValue2()
{
	if (this->isMultiValued() == false)
		throw (new exception("Hand has only ONE value"));

	else return this->getValue1() + 10;
}

bool Hand::isBlackjack()
{
	if (this->numberOfCards() == 2 && this->getValue1() == 21)
		return true;

	return false;
}

bool Hand::hasAs()
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (this->hand[i]->getType() == AS) 
			return true;
	}
}

/* Je ne vois plus très bien à quoi sert cette fonction*/
void Hand::deleteHand()
{
	this->hand.clear();
	this->~Hand();
}
