#include "Player.h"

Player::Player(int i, int pBalance) :
	Participant(i, pBalance)
{
}

void Player::newHand()
{
	if (this->hand == NULL)
		hand = new Hand();
	else hand2 = new Hand();
}

void Player::deleteHand(Hand *h)
{
	h->deleteHand();
	h = NULL;
}