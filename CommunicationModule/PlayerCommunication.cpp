#include "PlayerCommunication.h"

using namespace std;

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

/**
 * Le joueur demande une carte
 * @param secondHand Entier qui vaut 1 si le joueur à "split" et demande une carte pour sa deuxième main
 *                                   0 s'il demande une carte pour sa première main ou n'a pas split
 */
void PlayerCommunication::AskToHIt(int secondHand)
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "8 %d", secondHand);
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Bet(int bet)
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

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
                throw runtime_error("Erreur de création du fichier in");
            if ((mkfifo("joueur0.out",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier out");
            this->id = id;
            sprintf(this->fifoNameIn, "joueur0.in");
            sprintf(this->fifoNameOut, "joueur0.out");
            break;
        case 1:
            if ((mkfifo("joueur1.in",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier in");
            if ((mkfifo("joueur1.out",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier out");
            this->id = id;
            sprintf(this->fifoNameIn, "joueur1.in");
            sprintf(this->fifoNameOut, "joueur1.out");
            break;
        case 2:
            if ((mkfifo("joueur2.in",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier in");
            if ((mkfifo("joueur2.out",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier out");
            this->id = id;
            sprintf(this->fifoNameIn, "joueur2.in");
            sprintf(this->fifoNameOut, "joueur2.out");
            break;
        case 3:
            if ((mkfifo("joueur3.in",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier in");
            if ((mkfifo("joueur3.out",S_IRWXU)) != 0)
                throw runtime_error("Erreur de création du fichier out");
            this->id = id;
            sprintf(this->fifoNameIn, "joueur3.in");
            sprintf(this->fifoNameOut, "joueur3.out");
            break;
        default:
            break;
    }
}

void PlayerCommunication::Double()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "7");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::EnterGame()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "6");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::LeaveGame()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "5");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::QuitMessage()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "4");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

/**
 * Lis le fichier .in du joueur
 * @return La chaine de caractères lue
 */
string PlayerCommunication::ReadFile()
{
    FILE *file = fopen(fifoNameIn,"r");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier in");

    char str[32];

    fread(str,sizeof(char),32,file);
    return (string) str;

}

void PlayerCommunication::RespondInsurance(int val)
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "%d", val);
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Split()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "1");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Stand()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "2");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}

void PlayerCommunication::Surrender()
{
    FILE *file = fopen(fifoNameOut,"w");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier out");

    char str[32];
    sprintf(str, "3");
    int nb = fwrite(str, sizeof(char), 32, file);
    fclose(file);
}