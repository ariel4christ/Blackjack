/**
 * BankCommunication.cpp
 * @author Thomas MAINGUY
 */

#include "BankCommunication.h"
#include "../BankModule/BankGame.h"

using namespace std;

/**
 * La banque propose une assurance à un joueur
 * @param player l'id du joueur
 */
void BankCommunication::AskInsurance(int player)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%d.in", player);
    FILE *file = fopen(fifoNameIn,"w");
    if (file == (FILE*) NULL)
        perror("Erreur ouverture fichier .in lors de AskInsurance");
    else
    {
        char str[32];
        sprintf(str, "1");
        fwrite(str, sizeof(char), 32, file);
        fclose(file);
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

/**
 * La banque crédite un joueur
 * @param player l'id du joueur à créditer
 * @param money  la somme d'argent à créditer
 */
void BankCommunication::CreditPlayer(int player, int money)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de CreditPlayer");
        else
        {
            char str[32];
            sprintf(str, "11 %1d %d ", player, money);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * La banque débite un joueur
 * @param player l'id du joueur à débiter
 * @param money  la somme d'argent à débiter
 */
void BankCommunication::DebitPlayer(int player, int money)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de DebitPlayer");
        else
        {
            char str[32];
            sprintf(str, "12 %1d %d ", player, money);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * La banque prévient les joueurs de la fin du round
 */
void BankCommunication::EndRound(vector<Player*> &p)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (vector<Player*>::iterator it = p.begin() ; it != p.end() ; ++it)
    {
        sprintf(fifoNameIn, "joueur%d.in", (*it)->getId());

        if (access(fifoNameIn, R_OK) == 0)
        {
            FILE *file = fopen(fifoNameIn,"w");
            if (file == (FILE*) NULL)
                perror("Erreur ouverture fichier .in lors de EndRound");
            else
            {
                char str[32];
                sprintf(str, "2 ");
                fwrite(str, sizeof(char), 32, file);
                fclose(file);
            }
        }
    }
}

/**
 * La banque prévient les joueurs de l'arrivée d'un nouveau joueur
 * @param player l'id du player qui est arrivé
 */
void BankCommunication::PlayerEntered(int id_player, vector<Player*> &player)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (vector<Player*>::iterator it = player.begin() ; it != player.end() ; ++it)
    {
        sprintf(fifoNameIn, "joueur%d.in", (*it)->getId());

        if (access(fifoNameIn, R_OK) == 0)
        {
            FILE *file = fopen(fifoNameIn,"w");
            if (file == (FILE*) NULL)
                perror("Erreur ouverture fichier .in lors de PlayerEntered");
            else
            {
                char str[32];
                sprintf(str, "10 %1d %d %d ", id_player, BankGame::getBetMin(), BankGame::getBetMax());
                fwrite(str, sizeof(char), 32, file);
                fclose(file);
            }
        }
    }
}

/**
 * La banque prévient les joueurs qu'un joueur à quitté la partie
 * @param player l'id du joueur qui est parti
 */
void BankCommunication::HasQuit(int player, vector<Player*> &p)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (vector<Player*>::iterator it = p.begin() ; it != p.end() ; ++it)
    {
        sprintf(fifoNameIn, "joueur%d.in", (*it)->getId());

        if (access(fifoNameIn, R_OK) == 0)
        {
            FILE *file = fopen(fifoNameIn,"w");
            if (file == (FILE*) NULL)
                perror("Erreur ouverture fichier in lors de HasQuit");
            else
            {
                char str[32];
                sprintf(str, "9 %d ", player);
                fwrite(str, sizeof(char), 32, file);
                fclose(file);
            }
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
        perror("Erreur d'ouverture du fichier .out lors de ReadFile");

    char str[32];
    usleep(1500);  // Attente pour une meilleur sychonisation entre les processus
    fread(str,sizeof(char),32,file);
    fclose(file);

    return (string) str;
}

/**
 * La banque prévient le joueurs qu'un tour a commencé
 * @param   id    Entier identifiant du joueur
 */
void BankCommunication::RoundStart(int id)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%d.in", id);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de RoundStart");
        else
        {
            char str[32];
            sprintf(str, "3 ");
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }

}

/**
 * Envoie une carte à un joueur
 * @param player     l'id du joeuur
 * @param t          Le type de la carte
 * @param secondHand Entier : 0 si la carte est pour sa première main, 1 si c'est pour sa deuxième main (en cas de split)
 */
void BankCommunication::SendCard(int player, EType t, int secondHand, vector<Player*> &p)
{
    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
     for (vector<Player*>::iterator it = p.begin() ; it != p.end() ; ++it)
    {
        sprintf(fifoNameIn, "joueur%d.in", (*it)->getId());

        if (access(fifoNameIn, R_OK) == 0)
        {
            FILE *file = fopen(fifoNameIn,"w");
            if (file == (FILE*) NULL)
                perror("Erreur ouverture fichier .in lors de SendCard");
            else
            {
                char str[32];
                sprintf(str, "4 %1d %d %1d ", player, t, secondHand);
                fwrite(str, sizeof(char), 32, file);
                fclose(file);
            }
        }
    }
}

/**
 * Modifie le solde d'un joueur
 * @param player  l'id du joueur
 * @param balance le solde
 */
void BankCommunication::setBalance(int player, int balance)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de setBalance");
        else
        {
            char str[32];
            sprintf(str, "5 %1d %d ", player, balance);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }

}

/**
 * Prévient les joueurs qu'un joueur à misé
 * @param player l'id du joueur
 * @param bet    la mise
 */
void BankCommunication::setBet(int player, int bet)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%1d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de setBet");
        else
        {
            char str[32];
            sprintf(str, "6 %1d %d ", player, bet);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Envoie là un joueur sa main
 * @param player l'id du joueur
 * @param h      la main à envoyer
 */
void BankCommunication::setHand(int player, Hand &h, int secondHand, vector<Player*> &p)
{
    std::vector<Card*> cards = h.getCards();

    char str[256];
    sprintf(str, "13 %1d %1d %d ", player, secondHand, static_cast<int>(cards.size()));


    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        sprintf(str, "%s %d ", str, (*it)->getType());
    }

    char fifoNameIn[11];

    // On envoie le message à tous les joueurs
    for (vector<Player*>::iterator it = p.begin() ; it != p.end() ; ++it)
    {
        sprintf(fifoNameIn, "joueur%d.in", (*it)->getId());

        if (access(fifoNameIn, R_OK) == 0)
        {
            FILE *file = fopen(fifoNameIn,"w");
            if (file == (FILE*) NULL)
                perror("Erreur ouverture fichier .in lors de setHand");
            else
            {
                fwrite(str, sizeof(char), 32, file);
                fclose(file);
            }
        }
    }
}

/**
 * Prévient les joueurs qu'un joueur est "resté"
 * @param player l'id du joueur
 */
void BankCommunication::validStand(int player, int secondHand)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%1d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de validStand");
        else
        {
            char str[32];
            sprintf(str, "7 %1d %1d ", player, secondHand);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Prévient les joueurs qu'un joueur à abandonné
 * @param player l'id du joueur
 */
void BankCommunication::validSurrender(int player)
{
    char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn,"w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de validSurrender");
        else
        {
            char str[32];
            sprintf(str, "8 %1d ", player);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Prévient les joueurs qu'un joueur à splite
 * @param player l'id du joueur
 */
void BankCommunication::validSplit(int player)
{
	char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%1d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn, "w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de validSplit");
        else
        {
            char str[32];
            sprintf(str, "14 %1d ", player);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Prévient les joueurs qu'un joueur à splite
 * @param player l'id du joueur
 */
void BankCommunication::AskAction(int player, int secondHand)
{
	char fifoNameIn[11];

    sprintf(fifoNameIn, "joueur%1d.in", player);

    if (access(fifoNameIn, R_OK) == 0)
    {
        FILE *file = fopen(fifoNameIn, "w");
        if (file == (FILE*) NULL)
            perror("Erreur ouverture fichier .in lors de AskAction");
        else
        {
            char str[32];
            sprintf(str, "15 %1d %1d ", player, secondHand);
            fwrite(str, sizeof(char), 32, file);
            fclose(file);
        }
    }
}

/**
 * Méthode gérant la réception des ACK envoyés par tous les joueurs.
 */
void BankCommunication::ReceiveAck(vector<Player*> &p)
{
	for (vector<Player*>::iterator it = p.begin() ; it != p.end() ; ++it)
	{
		string str = ReadFile((*it)->getId());  // Accussé de réception
		int id_message;
		sscanf(str.c_str(), "%d", &id_message);
		if (id_message != 10)
			throw runtime_error("Accusée de reception non reçu");
	}
}

/**
 * Méthode gérant la réception de l'ACK envoyé par le joueur dont l'id est en paramètre.
 * @param id Entier, identifiant du joueur où on attend un ACK.
 */
void BankCommunication::ReceiveAck(int id)
{
	string str = ReadFile(id);  // Accussé de réception
	int id_message;
	sscanf(str.c_str(), "%d", &id_message);
	if (id_message != 10)
		throw runtime_error("Accusée de reception non reçu");
}
