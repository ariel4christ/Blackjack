#include "Hand.h"
#include <stdexcept>

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
		throw runtime_error("Hand has only ONE value"));

	else return this->getValue1() + 10;
}

vector<Card*>& Hand::getCards()
{
	return this->cards;
}

void Hand::addCard(Card *c)
{
	if (this->numberOfCards() > 22)
		throw runtime_error("Main pleine"));

	this->cards.push_back(c);
}


bool Hand::isMultiValued()
{
	for (unsigned int i = 0; i < this->cards.size(); i++)
	{
		// Si la valeur de la main est > 11, alors la deuxiçme valeur de la main est > 21
		if (this->cards[i]->getType() == AS && this->getValue1() <= 11)
			return true;
	}

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

bool Hand::isBlackjack()
{
	if (this->numberOfCards() == 2 && this->getValue1() == 21)
		return true;

	return false;
}

bool Hand::isPair()
{
	return this->cards[0]->getType() == this->cards[1]->getType();
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

void Hand::trandferSecondCard(Hand *h)
{
	if (this->numberOfCards() != 2)
		throw runtime_error("Impossible : Nombre de cartes incorrecte");

	h->addCard(this->cards[1]);
	this->cards.pop_back();
}
