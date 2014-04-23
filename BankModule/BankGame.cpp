#include "BankGame.h"

// Mises minimale et maximale par défaut à respectivement 5 et 100
int BankGame::betMin = 5;
int BankGame::betMax = 100;


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
