#ifndef _BANKCOMMUNICATION_H
#define _BANKCOMMUNICATION_H

#include "../GameModule/Card.h"
#include "../GameModule/Hand.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdexcept>
#include <string>

class BankCommunication
{
public:
    void AskInsurance(int player);
    int CheckFiles();
    void CleanFiles();
    void CreditPlayer(int player, int money);
    void DebitPlayer(int player, int money);
    void EndRound();
    void PlayerEntered(int player);
    void HasQuit(int player);
    std::string ReadFile(int id);
    void RoundStart();
    void SendCard(int player, EType t, int secondHand);
    void setBalance(int player, int balance);
    void setBet(int player, int bet);
    void setHand(int player, Hand &h);
    void validStand(int player);
    void validSurrender(int player);
};

#endif