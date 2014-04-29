#include "Bank.h"

using namespace std;

Bank::Bank(int bankBalance) :
	Participant(0, bankBalance)
{
}

Bank::~Bank()
{
}

void Bank::newHand()
{
	if (this->hand != NULL)
		this->hand = new Hand();
	else throw new exception("Main déjà existante");
}

void Bank::deleteHand()
{
	this->hand->deleteHand();
	this->hand = NULL;
}