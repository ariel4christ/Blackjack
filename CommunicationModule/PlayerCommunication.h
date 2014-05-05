/**
 * PlayerCommunication.h
 * @author Thomas MAINGUY
 */

 #ifndef _PLAYERCOMMUNICATION_H
#define _PLAYERCOMMUNICATION_H

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
    void AskToHIt(int secondHand);
    void Bet(int bet);
    int CheckFiles();
    void CreateFiles(int id);
    void RemoveFiles(int id);
    void Double();
    void EnterGame();
    void QuitMessage();
    std::string ReadFile();
    void RespondInsurance(int val);
    void Split(int secondHand);
    void Stand(int secondHand);
    void Surrender(int secondHand);
};

#endif
