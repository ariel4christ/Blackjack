#ifndef _PLAYER_H
#define _PLAYER_H
#include "Hand.h"
#include "Participant.h"

class Player : public Participant
{
private:
	bool blackjack = false;
	bool stand = false;
	bool surrender = false;
	
protected:
	Hand *hand;
	Hand *hand2;

public:
	Player(int i, int pBalance);
	~Player();

	virtual void newHand();
	void deleteHand(Hand *h);
};

#endif