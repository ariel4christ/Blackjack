#ifndef _BANKGAME_H
#define _BANKGAME_H

class BankGame
{
private:
	static int betMin;
	static int betMax;

public:
	static int getBetMin();
	static int getBetMax();
	static void setBetMin(int i);
	static void setBetMax(int i);
};

#endif