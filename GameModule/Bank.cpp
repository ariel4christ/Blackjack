#include "Bank.h"

using namespace std;

Bank::Bank(int bankBalance) :
	Participant(bankBalance),
	hiddenCard(NULL)
{
    this->hand = NULL;
}

Bank::~Bank()
{
	this->hand->deleteHand();
	delete hand;
}

void Bank::newHand()
{
	if (this->hand == NULL)
	{
		this->hand = new Hand();
		this->hand->getCards().clear();
    }
	else throw runtime_error("Main déjà existante");
}

void Bank::deleteHand()
{
	this->hand->deleteHand();
	delete this->hand;
	this->hand = NULL;
}

bool Bank::isBankBlackjack()
{
	if (hand->numberOfCards() == 2 && (hand->getCard(0)->getValue() + hiddenCard->getValue()) == 21)
		return true;

	return false;
}
