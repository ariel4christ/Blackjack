#ifndef _BANK_H
#define _BANK_H
#include "Participant.h"
#include "Hand.h"

class Bank : public Participant
{
private:
	Hand hand;
};

#endif