#include "Hand.h"

using namespace std;


Hand::Hand()
{
}

Hand::Hand(Card& c)
{
	Hand();
	this->cards.push_back(&c);
}

Hand::Hand(const Hand& h)
{
	this->cards.clear();
	for (unsigned int i = 0; i < h.cards.size(); i++)
	{
		this->cards.push_back(h.cards[i]);
	}
}

Hand::~Hand()
{
}


int Hand::numberOfCards()
{
	return this->cards.size();
}

vector<Card*>& Hand::getCards()
{
	return this->cards;
}

void Hand::addCard(Card *c)
{
	if (this->numberOfCards() > 22)
		throw (new exception("Main pleine"));

	this->cards.push_back(c);
}

bool Hand::isMultiValued()
{
	for (unsigned int i = 0; i < this->cards.size(); i++)
	{
		// Si la valeur de la main est > 11, alors la deuxième valeur de la main est > 21
		if (this->cards[i]->getType() == AS && this->getValue1() <= 11)
			return true;
	}

	return false;
}

int Hand::getValue1()
{
	int sum = 0;
	for (unsigned int i = 0; i < this->cards.size(); i++)
		sum += this->cards[i]->getValue();

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
	for (unsigned int i = 0; i < this->cards.size(); i++)
	{
		if (this->cards[i]->getType() == AS)
			return true;
	}

	return false;
}

void Hand::deleteHand()
{
	for (vector<Card*>::iterator it = this->cards.begin(); it != this->cards.end(); it++)
	{
		delete *it;  // Est-ce que ça marche ici ???
	}
	this->cards.clear();
	this->~Hand();
}

void Hand::setHand(const Hand& h)
{
	for (vector<Card*>::iterator it = this->cards.begin(); it != this->cards.end(); it++)
	{
		delete *it;  // Est-ce que ça marche ici ???
	}
	this->cards.clear();
	for (unsigned int i = 0; i < h.cards.size(); i++)
	{
		this->cards.push_back(h.cards[i]);
	}
}