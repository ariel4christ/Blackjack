#ifndef _PLAYERHAND_H
#define _PLAYERHAND_H
#include "Hand.h"

class PlayerHand : public Hand
{
protected:
	int bet;

public:
	virtual bool isBlackjack();
};

#endif