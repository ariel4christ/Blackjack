#include "BankGame.h"

using namespace std;

// Mises minimale et maximale par défaut à respectivement 5 et 100
int BankGame::betMin = 5;
int BankGame::betMax = 100;
int BankGame::balancePlayerInit = 2000;

int BankGame::getBetMin()
{
	return BankGame::betMin;
}

void BankGame::setBetMin(int i)
{
	BankGame::betMin = i;
}

int BankGame::getBetMax()
{
	return BankGame::betMax;
}

void BankGame::setBetMax(int i)
{
	BankGame::betMax = i;
}

int BankGame::getBalancePlayerInit()
{
	return BankGame::balancePlayerInit;
}

void BankGame::setBalancePlayerInit(int i)
{
	BankGame::balancePlayerInit = i;
}


BankGame::BankGame(int bankBalance):
	bank(Bank::Bank(bankBalance))
{
	this->newDeck();
}

void BankGame::burnCards()
{

}

void BankGame::newDeck()
{
	this->deck.clear();
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 0; j < 4; j++)
			this->deck.push_back(new Card((EType)i));
	}
}

void BankGame::shuffleDeck()
{
	random_shuffle(this->deck.begin(), this->deck.end());
}