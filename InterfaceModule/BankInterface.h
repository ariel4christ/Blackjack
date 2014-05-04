#ifndef _BANKINTERFACE_H
#define _BANKINTERFACE_H

#include "../GameModule/Player.h"
#include "../GameModule/Hand.h"
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include <vector>
#include <iostream>

class BankInterface
{
public:
    void printGameState(std::vector<Player*> &players, Bank &bank);
};

#endif