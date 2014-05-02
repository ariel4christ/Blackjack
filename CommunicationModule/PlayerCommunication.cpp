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
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "8");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Bet(int bet)
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "9 %d", bet);
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
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
            this->id = id;
            this->fifoNameIn = "joueur0.in";
            this->fifoNameOut = "joueur0.out";
            break;
        case 1:
            if ((mkfifo("joueur1.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur1.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            this->id = id;
            this->fifoNameIn = "joueur1.in";
            this->fifoNameOut = "joueur1.out";
            break;
        case 2:
            if ((mkfifo("joueur2.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur2.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            this->id = id;
            this->fifoNameIn = "joueur2.in";
            this->fifoNameOut = "joueur2.out";
            break;
        case 3:
            if ((mkfifo("joueur3.in",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier in");
            if ((mkfifo("joueur3.out",S_IRWXU)) != 0)
                throw std::Exception("Erreur de création du fichier out");
            this->id = id;
            this->fifoNameIn = "joueur3.in";
            this->fifoNameOut = "joueur3.out";
            break;
        default:
            break;
    }
}

void PlayerCommunication::Double()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "7");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::EnterGame()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "6");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::LeaveGame()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "5");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::QuitMessage()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "4");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

/**
 * Lis le fichier .in du joueur
 * @return La chaine de caractères lue
 */
char* PlayerCommunication::ReadFile()
{
    FILE *file = fopen(fifoNameIn,"r");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier in");

    char str[32];

    fread(str,sizeof(char),32,file);
    return str;

}

void PlayerCommunication::RespondInsurance(int val)
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "%d", val);
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}
}

void PlayerCommunication::Split()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "1");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Stand()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "2");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Surrender()
{
    FILE *file = fopen(fifoname,"w");
    if (file == (FILE *) NULL)
        throw std::Exception("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "3");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}