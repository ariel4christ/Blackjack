#ifndef _BANKGAME_H
#define _BANKGAME_H

#include <vector>
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include "../GameModule/Player.h"
#include "../CommunicationModule/BankCommunication.h"
#include "../InterfaceModule/BankInterface.h"

class BankGame
{
private:
	static int betMin;
	static int betMax;
	static int balancePlayerInit;

	std::vector<Card*> deck;
	Bank bank;
	std::vector<Player*> player;

	BankCommunication com;
	BankInterface interface;


public:
	static int getBetMin();
	static int getBetMax();
	static int getBalancePlayerInit();
	static void setBetMin(int i);
	static void setBetMax(int i);
	static void setBalancePlayerInit(int i);

	BankGame(int bankBalance);
	~BankGame();
	void runGame();
	

private:
	void burnCards();
	void newDeck();
	void shuffleDeck();
};

#endif