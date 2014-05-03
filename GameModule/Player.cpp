#include "Player.h"

Player::Player(int i, int pBalance) : blackjack(false),surrender(false)
	Participant(i, pBalance)
{
}

Player::~Player()
{
	this->hand->deleteHand();
	this->hand2->deleteHand();
	delete hand;
	delete hand2;
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

void Player::Stand(PlayerHand *h)
{
	if (h != this->hand && h != this->hand2)
		throw new std::exception("La main en paramètre n'est pas celle du joueur");

	h->setStand(true);
}

void Player::Surrender(PlayerHand *h)
{
	if (h != this->hand && h != this->hand2)
		throw new std::exception("La main en paramètre n'est pas celle du joueur");

	this->increaseBalance(h->getBet() / 2);
	h->deleteHand();
	delete h;

	if (this->hand == NULL && this->hand2 == NULL)
		this->setSurrender(true);
}

bool Player::getBlackjack()
{
	return this->blackjack;
}

void Player::setBlackjack(bool b)
{
	this->blackjack = b;
}

bool Player::getSurrender()
{
	return this->surrender;
}

void Player::setSurrender(bool b)
{
	this->surrender = b;
}
