#include "Player.h"

using namespace std;

Player::Player(int i, int pBalance) :
Participant(pBalance),
blackjack(false),
surrender(false),
insurance(false),
id(i)
{
	this->hand = NULL;
	this->hand2 = NULL;
}

Player::~Player()
{
	this->hand->deleteHand();
	this->hand2->deleteHand();
	delete hand;
	hand = NULL;
	delete hand2;
	hand2 = NULL;
}

void Player::newHand()
{
	if (this->hand == NULL)
		hand = new PlayerHand();
	else hand2 = new PlayerHand();
}

void Player::newHand(int i)
{
	if (this->hand == NULL)
		hand = new PlayerHand(i);
	else hand2 = new PlayerHand(i);
}

void Player::deleteHand(Hand *h)
{
	h->deleteHand();
	delete h;
	h = NULL;
}

void Player::Stand(PlayerHand *h)
{
	if (h != this->hand && h != this->hand2)
		throw runtime_error("La main en paramètre n'est pas celle du joueur");

	h->setStand(true);
}

void Player::Surrender(PlayerHand *h)
{
	if (h != this->hand && h != this->hand2)
		throw runtime_error("La main en paramètre n'est pas celle du joueur");

	this->increaseBalance(h->getBet() / 2);
	h->deleteHand();
	delete h;
	h = NULL;

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

void Player::setHand(PlayerHand *h)
{
	this->hand->deleteHand();
	this->hand = h;
}

void Player::setHand2(PlayerHand *h)
{
	this->hand2->deleteHand();
	this->hand2 = h;
}
