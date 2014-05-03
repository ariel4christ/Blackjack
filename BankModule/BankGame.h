/**
 * Classe BankGame. Classe de gestion du jeu.
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
	static int betMin;  /**< Entier. Mise minimale.*/
	static int betMax;  /**< Entier. Mise maximale.*/
	static int balancePlayerInit;  /**< Entier. Solde initial des joueurs.*/

	std::vector<Card*> deck;  /**< vector<Card*>. Liste des cartes, sabot.*/
	Bank bank;  /**< Bank Banque du jeu.*/
	std::vector<Player*> player;  /**< vector<Player*>. Liste des joueurs.*/

	BankCommunication com;  /**< BankCommunication. Objet permettant la communication entre l'ex�cutable Bank et les ex�cutables joueurs.*/
	BankInterface interface;  /**< BankInterface. Objet r�alisant les interaction entre le programme et l'utilisateur.*/


public:

	/**
	 * M�thode statique retournant la mise minimale autoris�e.
	 */
	static int getBetMin();

	/**
	 * M�thode statique retournant la mise maximale autoris�e.
	 */
	static int getBetMax();

	/**
	 * M�thode statique retournant le solde initial d'un joueur.
	 */
	static int getBalancePlayerInit();

	/**
	 * M�thode statique d�terminant la mise minimale autoris�e.
	 * @param i Nouvelle mise minimale autoris�e.
	 */
	static void setBetMin(int i);

	/**
	 * M�thode statique d�terminant la mise maximale autoris�e.
	 * @param i Nouvelle mise maximale autoris�e.
	 */
	static void setBetMax(int i);

	/**
	 * M�thode statique d�terminant le solde initial d'un joueur.
	 * @param i Nouveau solde initiale d'un joueur.
	 */
	static void setBalancePlayerInit(int i);

	/**
	 * Constructeur.
	 * @param bankBalance Solde initiale de la banque.
	 */
	BankGame(int bankBalance);

	/**
	 * Destructeur. Destruction de deck et de player.
	 * @see clearDeck()
	 * @see Player::~Player()
	 */
	~BankGame();

	/**
	 * M�thode A IMPLEMENTER...
	 */
	void runGame();


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
	 * Tire une carte du deck et renvoie son pointeur.
	 * @return Pointeur vers la carte tir�e du deck.
	 */
	Card* hitCard();

	/**
	 * M�thode qui initialise un tour : accueil des nouveaux joueurs, demande des mises et distribution des cartes.
	 */
	void initRound();

	/**
	 * M�thode cr�ant un nouveau deck (sabot) neuf. Il contient 312 cartes (24 de chaque EType) non m�lang�es.
	 * @see Card::Card()
	 */
	void newDeck();

	void newGame();

	void newPlayer();

	void runRound();

	/**
	 * M�thode de battage (tri al�atoire) des cartes du deck.
	 * @see std::random_suffle()
	 */
	void shuffleDeck();

};

#endif