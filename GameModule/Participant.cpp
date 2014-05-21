/**
 * Participant.cpp
 * @author Christophe HUBERT
 */

#include "Participant.h"

void Participant::decreaseBalance(int i)
{
	this->balance -= i;
}

void Participant::increaseBalance(int i)
{
	this->balance += i;
}

Participant::Participant(int b) :
		balance(b)
{
}

Participant::~Participant()
{
}
