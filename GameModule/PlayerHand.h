#ifndef _PLAYERHAND_H
#define _PLAYERHAND_H
#include "Player.h"

class PlayerHand : public Player
{
protected:
	int bet;

public:
	virtual bool isBlackjack();
};

#endif