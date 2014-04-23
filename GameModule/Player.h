#ifndef _PLAYER_H
#define _PLAYER_H
#include "Hand.h"

class Player
{
private:
	bool blackjack = false;
	bool stand = false;
	bool surrender = false;
	
protected:
	Hand hand;
	Hand hand2;
};

#endif