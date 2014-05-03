#include "BankCommunication.h"

using namespace std;

void BankCommunication::AskInsurance()
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "1");
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Vérifie quelles places de joueurs sont occupées
 * @return Un entier qui permet de déterminer quelles places sont occupées
 */
int BankCommunication::CheckFiles()
{
    int result = 0;

    if (access("joueur0.in", R_OK) == 0 && access("joueur0.out", R_OK) == 0)
        result |= (1 << 0);
    if (access("joueur1.in", R_OK) == 0 && access("joueur1.out", R_OK) == 0)
        result |= (1 << 1);
    if (access("joueur2.in", R_OK) == 0 && access("joueur2.out", R_OK) == 0)
        result |= (1 << 2);
    if (access("joueur3.in", R_OK) == 0 && access("joueur3.out", R_OK) == 0)
        result |= (1 << 3);

    return result;
}

/**
 * Supprime tous les fichiers .in et .out qui existent dans le dossier courant
 */
void BankCommunication::CleanFiles()
{
    remove("joueur0.in");
    remove("joueur1.in");
    remove("joueur2.in");
    remove("joueur3.in");
    remove("joueur0.out");
    remove("joueur1.out");
    remove("joueur2.out");
    remove("joueur3.out");
}

void BankCommunication::CreditPlayer(int player, int money)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "11 %d %d", player, money);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::DebitPlayer(int player, int money)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "12 %d %d", player, money);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::EndRound()
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "2");
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::PlayerEntered(int player)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "10 %d", player);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::HasQuit(int player)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "9 %d", player);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Lis le fichier du joueur ayant l'id passé en paramètre
 * @param  id L'id du joueur dont il faut lire le fichier
 * @return    La chaine de caractères lue
 */
string BankCommunication::ReadFile(int id)
{
    char fileName[12];
    switch (id)
    {
        case 0:
            sprintf(fileName, "joueur0.out");
            break;
        case 1:
            sprintf(fileName, "joueur1.out");
            break;
        case 2:
            sprintf(fileName, "joueur2.out");
            break;
        case 3:
            sprintf(fileName, "joueur3.out");
            break;
        default:
            break;
    }

    FILE *file = fopen(fileName,"r");
    if (file == (FILE *) NULL)
        throw runtime_error("Erreur d'ouverture du fichier in");

    char str[32];

    fread(str,sizeof(char),32,file);
    return (string) str;
}

void BankCommunication::RoundStart()
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "3");
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::SendCard(int player, EType t, int secondHand)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "4 %d %d %d", player, t, secondHand);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::setBalance(int player, int balance)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "5 %d %d", player, balance);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::setBet(int player, int bet)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "6 %d %d", player, bet);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::setHand(int player, Hand &h)
{
    std::vector<Card*> cards = h.getCards();

    char str[256];
    sprintf(str, "13 %d %d", player, static_cast<int>(cards.size()));


    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        sprintf(str, "%s %d", str, (*it)->getType());
    }

    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::validStand(int player)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "7 %d", player);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

void BankCommunication::validSurrender(int player)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (int i = 0 ; i < 4 ; i++)
    {
        sprintf(fifoNameIn, "joueur%d.in", i);
        FILE *file = fopen(fifoNameIn,"w");
        if (file != (FILE *) NULL)
        {
            char str[32];
            sprintf(str, "8 %d", player);
            int nb = fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}
