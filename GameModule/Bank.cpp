/**
 * Bank.cpp
 * @author Christophe HUBERT
 */

#include "Bank.h"

using namespace std;

Bank::Bank(int bankBalance) :
		Participant(bankBalance), hiddenCard(NULL)
{
	this->hand = NULL;
}

Bank::~Bank()
{
	if (this->getHand() != NULL)
		this->setHand(NULL);
}

void Bank::newHand()
{
	if (this->hand == NULL)
	{
		this->hand = new Hand();
		this->hand->getCards().clear();
	}
	else
		throw runtime_error("Main déjà existante");
}

void Bank::deleteHand()
{
	this->hand->deleteHand();
	delete this->hand;
	this->hand = NULL;
}

bool Bank::isBankBlackjack()
{
	Hand tmp;
	tmp.addCard(this->hand->getCard(0));
	tmp.addCard(this->hiddenCard);

	if (hand->numberOfCards() == 2 && tmp.getValue2() == 21)
		return true;

	return false;
}
