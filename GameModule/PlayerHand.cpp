#include "PlayerHand.h"

PlayerHand::PlayerHand(int i) :
Hand(),
bet(i)
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