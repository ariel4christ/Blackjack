#ifndef _BANKCOMMUNICATION_H
#define _BANKCOMMUNICATION_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdexcept>
#include <string>

class PlayerCommunication
{

private:
    int id;
    char fifoNameIn[11];
    char fifoNameOut[12];

public:
    PlayerCommunication();
    PlayerCommunication(const PlayerCommunication &b);
    PlayerCommunication& operator=(const PlayerCommunication &b);
    ~PlayerCommunication();

    void AskToHIt(int secondHand);
    void Bet(int bet);
    int CheckFiles();
    void CreateFiles(int id);
    void Double();
    void EnterGame();
    void QuitMessage();
    std::string ReadFile();
    void RespondInsurance(int val);
    void Split();
    void Stand();
    void Surrender();
};

#endif