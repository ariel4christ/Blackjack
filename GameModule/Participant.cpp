#include "Participant.h"


void Participant::decreaseBalance(int i)
{
	this->balance += i;
}

void Participant::increaseBalance(int i)
{
	this->balance -= i;
}