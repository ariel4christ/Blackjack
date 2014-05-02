#ifndef _BANKCOMMUNICATION_H
#define _BANKCOMMUNICATION_H

class BankCommunication
{
public:
    void AskInsurance();
    void CheckFiles();
    void CleanFiles();
    void CreditPlayer();
    void DebitPlayer();
    void EndRound();
    void HasQuit();
    void PlayerEntered();
    void PlayerLeft();
    void ReadFile();
    void RemoveFile();
    void RoundStart();
    void SendCard();
    void setBalance();
    void setBet();
    void setHand();
    void validStand();
    void validSurrender();
};

#endif