#ifndef _BANKCOMMUNICATION_H
#define _BANKCOMMUNICATION_H

class PlayerCommunication
{

private:
    int id;

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
    void ReadFile();
    void RespondInsurance();
    void Split();
    void Stand();
    void Surrender();
};

#endif