/**
 * Classe BankGame. Classe de gestion du jeu, ex�cutable banque.
 * @author Christophe HUBERT
 */

#ifndef _BANKGAME_H
#define _BANKGAME_H

#include <vector>
#include <stdexcept>
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include "../GameModule/Player.h"
#include "../CommunicationModule/BankCommunication.h"
#include "../InterfaceModule/BankInterface.h"

class BankGame
{
private:
	static int betMin; /**< Entier. Mise minimale.*/
	static int betMax; /**< Entier. Mise maximale.*/
	static long balancePlayerInit; /**< Entier. Solde initial des joueurs.*/

	std::vector<Card*> deck; /**< vector<Card*>. Liste des cartes, sabot.*/
	Bank bank; /**< Bank Banque du jeu.*/
	std::vector<Player*> player; /**< vector<Player*>. Liste des joueurs.*/

	BankCommunication com; /**< BankCommunication. Objet permettant la communication entre l'ex�cutable Bank et les ex�cutables joueurs.*/
	BankInterface interface; /**< BankInterface. Objet r�alisant les interaction entre le programme et l'utilisateur.*/

public:

	/**
	 * Getteur de bank.
	 * @return  R�f�rence de l'objet bank.
	 */
	Bank& getBank()
	{
		return this->bank;
	}

	/**
	 * Getteur de player.
	 * @return  R�f�rence du vecteur des joueurs.
	 */
	std::vector<Player*>& getPlayers()
	{
		return this->player;
	}

	/**
	 * M�thode statique retournant la mise minimale autoris�e.
	 * @return  Entier  Mise min.
	 */
	static int getBetMin();

	/**
	 * M�thode statique retournant la mise maximale autoris�e.
	 * @return  Entier  Mise min.
	 */
	static int getBetMax();

	/**
	 * M�thode statique retournant le solde initial d'un joueur.
	 * @return  Entier long     Solde initial d'un joueur.
	 */
	static long getBalancePlayerInit();

	/**
	 * M�thode retournant l'attribut com par r�f�rence.
	 * @return  BankCommunication   R�f�rence de com.
	 */
	BankCommunication& getCom()
	{
		return this->com;
	}

	/**
	 * M�thode statique d�terminant la mise minimale autoris�e.
	 * @param   i   Nouvelle mise minimale autoris�e.
	 */
	static void setBetMin(int i);

	/**
	 * M�thode statique d�terminant la mise maximale autoris�e.
	 * @param   i   Nouvelle mise maximale autoris�e.
	 */
	static void setBetMax(int i);

	/**
	 * M�thode statique d�terminant le solde initial d'un joueur.
	 * @param   i   Nouveau solde initiale d'un joueur.
	 */
	static void setBalancePlayerInit(int i);

	/**
	 * Constructeur.
	 * @param   bankBalance Solde initiale de la banque.
	 */
	BankGame(long bankInit);

	/**
	 * Constructeur.
	 * @param   min         Mise minimale.
	 * @param   max         Mise Maximale.
	 * @param   playerInit  Solde initial des joueurs.
	 * @param   bankBalance Solde initiale de la banque.
	 */
	BankGame(int min, int max, long playerInit, long bankInit);

	/**
	 * Destructeur. Destruction de deck et de player.
	 * @see clearDeck()
	 * @see Player::~Player()
	 */
	~BankGame();

	/**
	 * M�thode qui gere les tours de jeu.
	 * @return 0 lorsqu'il n'y a plus de joueur dans le jeu.
	 */
	int runGame();

private:

	/**
	 * M�thode supprimant les 5 premi�res cartes du deck.
	 * Lance une exception si il y a moins de 5 cartes dans le deck.
	 */
	void burnCards();

	/**
	 * M�thode d�sallouant toutes les cartes du deck. Deck est vid�.
	 */
	void clearDeck();

	/**
	 * M�thode distribuant les deux premi�res cartes � tous les joueurs et � la banque.
	 */
	void dealCards();

	/**
	 * Gestion de la fin d'un tour. Calcule si la main du joueur en param�tre a gagn� ou perdu.
	 * @see Participant::increaseBalance()
	 * @see Participant::decreaseBalance()
	 * @see BankCommunication::setBalance()
	 * @param   p           Pointeur vers le joueur pour lequel on �tudie la finalit� de sa fin.
	 * @param   secondHand  Entier � 0 si c'est la premi�re main du joueur, 1 et c'est la deuxi�me main.
	 */
	void endRound(Player *p, int secondHand);

	/**
	 * Tire une carte du deck et renvoie son pointeur.
	 * @return  Pointeur vers la carte tir�e du deck.
	 */
	Card* hitCard();

	/**
	 * M�thode qui initialise un tour : accueil des nouveaux joueurs, demande des mises et distribution des cartes.
	 * @return  0 si le jeu est fini car il n'y a plus de joueur, 1 sinon.
	 */
	int initRound();

	/**
	 * M�thode g�rant la partie assurance
	 * @return	0	Le tour est fini
	 1	Le tour n'est pas fini.
	 */
	int insurance();

	/**
	 * M�thode cr�ant un nouveau deck (sabot) neuf. Il contient 312 cartes (24 de chaque EType) non m�lang�es.
	 * @see Card::Card()
	 */
	void newDeck();

	/**
	 * M�thode l'initialisation du jeu.
	 * @see newDeck()
	 * @see shuffleDeck()
	 * @see burnCards()
	 * @see BankCommunication::ChechFiles()
	 */
	void newGame();

	/**
	 * M�thode incluant les nouveaux joueurs dans le jeu.
	 */
	void newPlayer();

	/**
	 * Methode qui va traiter l'action demandee par le joueur en parametre.
	 * @see BankCommunication::ReadFile()
	 * @see BankInterface::PrintGameState()
	 * @param   p   Pointeur vers le joueur qui envoie une action.
	 * @return  0   si le jeu est fini car il n'y a plus de joueur, 1 sinon.
	 */
	int playerAction(Player *p, int secondHand);

	/**
	 * Methode gerant la suppression d'un joueur du jeu. Desalloue le joueur en param�tre. Fini le jeu s'il n'y a plus de joueur.
	 * @see Player::~Player()
	 * @see BankCommunication::HasQuit()
	 * @param   p   Pointeur vers le joueur qui quitte le jeu.
	 * @return  0   si le jeu est fini car il n'y a plus de joueur, 1 sinon.
	 */
	int quitPlayer(Player *p);

	/**
	 * Methode gerant le deroulement d'un tour.
	 * @return  1   le tour s'est fini sans probleme, 0 si le jeu est termin�.
	 */
	int runRound();

	/**
	 * M�thode de battage (tri al�atoire) des cartes du deck.
	 * @see std::random_suffle()
	 */
	void shuffleDeck();

};

#endif
