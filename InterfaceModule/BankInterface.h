#ifndef _BANKINTERFACE_H
#define _BANKINTERFACE_H

#include "Interface.h"
#include "../GameModule/Player.h"
#include "../GameModule/Hand.h"
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include <vector>

class BankInterface : public Interface
{
    void PrintGameState(std::vector<Player*> players, Bank bank);
};

#endif