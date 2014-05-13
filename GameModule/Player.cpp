/**
 * Player.cpp
 * @author Christophe HUBERT
 */

#include "Player.h"

using namespace std;

Player::Player(int i, int pBalance) :
Participant(pBalance),
id(i),
blackjack(false),
insurance(false),
surrender(false)
{
	this->hand = NULL;
	this->hand2 = NULL;
}

Player::Player(int pBalance):
Participant(pBalance),
id(0),
blackjack(false),
insurance(false),
surrender(false)
{
	this->hand = NULL;
	this->hand2 = NULL;
}

Player::~Player()
{
    if (this->hand != NULL)
    {
        this->hand->deleteHand();
        delete hand;
    }
    if (this->hand2 != NULL)
    {
        this->hand2->deleteHand();
        delete hand2;
	}
}

void Player::newHand()
{
	if (this->hand == NULL)
	{
		this->hand = new PlayerHand();
		this->hand->getCards().clear();
    }
	else
	{
        this->hand2 = new PlayerHand();
        this->hand2->getCards().clear();
    }
}

void Player::newHand(int i)
{
	if (this->hand == NULL)
	{
		this->hand = new PlayerHand(i);
		this->hand->getCards().clear();
    }
	else
	{
        hand2 = new PlayerHand(i);
        this->hand2->getCards().clear();
    }
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
    if (this->hand != NULL)  // Pas de désallocation si le pointeur est à NULL
        this->hand->deleteHand();

	this->hand = h;
}

void Player::setHand2(PlayerHand *h)
{
    if (this->hand2 != NULL)  // Pas de désallocation si le pointeur est à NULL
        this->hand2->deleteHand();

	this->hand2 = h;
}
