#include "Participant.h"

void Participant::decreaseBalance(int i)
{
	this->balance += i;
}

void Participant::increaseBalance(int i)
{
	this->balance -= i;
}

Participant::Participant(int i, int b) :
id(i),
balance(b)
{
}

Participant::~Participant()
{
}
