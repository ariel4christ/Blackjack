#ifndef _PLAYERHAND_H
#define _PLAYERHAND_H
#include "Hand.h"

class PlayerHand : public Hand
{
protected:
	int bet;

public:
	PlayerHand(int i);
	~PlayerHand();

};

#endif