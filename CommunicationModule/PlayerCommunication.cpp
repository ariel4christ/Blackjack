#include "PlayerCommunication.h"
#include <unistd.h>


PlayerCommunication::PlayerCommunication()
{

}

PlayerCommunication::PlayerCommunication(const PlayerCommunication &b)
{

}

PlayerCommunication& PlayerCommunication::operator=(const PlayerCommunication &b)
{

}

PlayerCommunication::~PlayerCommunication()
{

}

void PlayerCommunication::AskToHIt()
{

}

void PlayerCommunication::Bet()
{

}

/**
 * Vérifie si il y a une place libre pour jouer
 * @return -1 si pas de place, le numéro de la place libre sinon
 */
int PlayerCommunication::CheckFiles()
{
    if (access("joueur0.in", R_OK) == 0)
        return 0;
    if (access("joueur1.in", R_OK) == 0)
        return 1;
    if (access("joueur2.in", R_OK) == 0)
        return 2;
    if (access("joueur3.in", R_OK) == 0)
        return 3;
}

void PlayerCommunication::CreateFiles(int id)
{
    switch (id)
    {
        case 0:
            if ((mkfifo("joueur0.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur0.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            break;
        case 1:
            if ((mkfifo("joueur1.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur1.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            break;
        case 2:
            if ((mkfifo("joueur2.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur2.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            break;
        case 3:
            if ((mkfifo("joueur3.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur3.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            break;
        default:
            break;
    }
}

void PlayerCommunication::Double()
{

}

void PlayerCommunication::EnterGame()
{

}

void PlayerCommunication::LeaveGame()
{

}

void PlayerCommunication::QuitMessage()
{

}

void PlayerCommunication::ReadFile()
{

}

void PlayerCommunication::RespondInsurance()
{

}

void PlayerCommunication::Split()
{

}

void PlayerCommunication::Stand()
{

}

void PlayerCommunication::Surrender()
{

}