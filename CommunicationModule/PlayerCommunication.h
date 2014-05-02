#ifndef _BANKCOMMUNICATION_H
#define _BANKCOMMUNICATION_H

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

    void AskToHIt();
    void Bet();
    int CheckFiles();
    void CreateFiles();
    void Double();
    void EnterGame();
    void LeaveGame();
    void QuitMessage();
    char* ReadFile();
    void RespondInsurance();
    void Split();
    void Stand();
    void Surrender();
};

#endif