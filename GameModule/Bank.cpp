#include "Bank.h"

using namespace std;

Bank::Bank(int bankBalance) :
	Participant(bankBalance),
	hiddenCard(NULL)
{
}

Bank::~Bank()
{
	this->hand->deleteHand();
	delete hand;
}

void Bank::newHand()
{
	if (this->hand != NULL)
		this->hand = new Hand();
	else throw runtime_error("Main déjà existante");
}

void Bank::deleteHand()
{
	this->hand->deleteHand();
	this->hand = NULL;
}

bool Bank::isBankBlackjack()
{
	if (hand->numberOfCards() == 2 && (hand->getCard(0)->getValue() + hiddenCard->getValue()) == 21)
		return true;

	return false;
}