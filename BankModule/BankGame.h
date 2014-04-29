#ifndef _BANKGAME_H
#define _BANKGAME_H

#include <vector>
#include <algorithm>
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include "../GameModule/Player.h"

class BankGame
{
private:
	std::vector<Card*> deck;
	static int betMin;
	static int betMax;
	static int balancePlayerInit;
	Bank bank;
	std::vector<Player*> player;

public:
	static int getBetMin();
	static int getBetMax();
	static int getBalancePlayerInit();
	static void setBetMin(int i);
	static void setBetMax(int i);
	static void setBalancePlayerInit(int i);

	BankGame(int bankBalance);
	void runGame();
	

private:
	void burnCards();
	void newDeck();
	void shuffleDeck();
};

#endif