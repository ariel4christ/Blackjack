/**
 * Hand.cpp
 * @author Christophe HUBERT
 */

#include "Hand.h"
#include <stdexcept>

using namespace std;

Hand::Hand()
{
	this->cards.clear();
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
		return this->getValue1();

	else
		return this->getValue1() + 10;
}

vector<Card*>& Hand::getCards()
{
	return this->cards;
}

Card* Hand::getCard(unsigned int i)
{
	if (i >= this->cards.size())
		throw runtime_error("Impossible d'accéder à cette carte de la main");
	else
		return this->cards[i];
}

void Hand::addCard(Card *c)
{
	if (this->numberOfCards() > 22)
		throw runtime_error("Main pleine");

	this->cards.push_back(c);
}

bool Hand::isMultiValued()
{
	for (unsigned int i = 0; i < this->cards.size(); i++)
	{
		// Si la valeur de la main est > 11, alors la deuxieme valeur de la main est > 21
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
	if (this->numberOfCards() == 2 && (this->getValue2() == 21 || this->getValue1() == 21))
		return true;

	return false;
}

bool Hand::isPair()
{
	if (this->cards[0]->getType() == this->cards[1]->getType() && this->numberOfCards() == 2)
		return true;
	else
		return false;
}

void Hand::deleteHand()
{
	if (!this->cards.empty())
	{
		//for (vector<Card*>::iterator it = this->cards.begin(); it != this->cards.end(); it++)
		for (unsigned int i = 0; i < cards.size(); ++i)
		{
			delete cards[i];
			cards[i] = NULL;
		}
		this->cards.clear();
	}
}

void Hand::setHand(const Hand& h)
{
	for (vector<Card*>::iterator it = this->cards.begin(); it != this->cards.end(); it++)
	{
		delete *it;
		*it = NULL;
	}
	this->cards.clear();
	for (unsigned int i = 0; i < h.cards.size(); i++)
	{
		this->cards.push_back(h.cards[i]);
	}
}

void Hand::setHand(Hand* h)
{
	for (vector<Card*>::iterator it = this->cards.begin(); it != this->cards.end(); it++)
	{
		delete *it;
		*it = NULL;
	}
	this->cards.clear();

	this->cards = h->cards;
}

void Hand::trandferSecondCard(Hand *h)
{
	if (this->numberOfCards() != 2)
		throw runtime_error("Impossible : Nombre de cartes incorrecte");

	h->addCard(this->cards[1]);
	this->cards.pop_back();
}
