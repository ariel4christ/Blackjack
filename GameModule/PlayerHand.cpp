#include "PlayerHand.h"

PlayerHand::PlayerHand(int i) :
Hand(),
bet(i)
stand(false)
{
}

PlayerHand::PlayerHand(Card &c, int i) :
Hand(c),
bet(i)
{
}

PlayerHand::PlayerHand(const Hand &h, int i) :
Hand(h),
bet(i)
{
}

PlayerHand::~PlayerHand()
{
}

int PlayerHand::getBet()
{
	return this->bet;
}

void PlayerHand::setBet(int bet)
{
	this->bet = bet;
}

void PlayerHand::doubleBet()
{
	this->bet *= 2;
}

bool PlayerHand::getStand()
{
	return this->stand;
}

void PlayerHand::setStand(bool b)
{
	this->stand = b;
}
