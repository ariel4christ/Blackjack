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

	BankCommunication com;  /**< BankCommunication. Objet permettant la communication entre l'exécutable Bank et les exécutables joueurs.*/
	BankInterface interface;  /**< BankInterface. Objet réalisant les interaction entre le programme et l'utilisateur.*/


public:

	/**
	 * Méthode statique retournant la mise minimale autorisée.
	 */
	static int getBetMin();

	/**
	 * Méthode statique retournant la mise maximale autorisée.
	 */
	static int getBetMax();

	/**
	 * Méthode statique retournant le solde initial d'un joueur.
	 */
	static int getBalancePlayerInit();

	/**
	 * Méthode statique déterminant la mise minimale autorisée.
	 * @param i Nouvelle mise minimale autorisée.
	 */
	static void setBetMin(int i);

	/**
	 * Méthode statique déterminant la mise maximale autorisée.
	 * @param i Nouvelle mise maximale autorisée.
	 */
	static void setBetMax(int i);

	/**
	 * Méthode statique déterminant le solde initial d'un joueur.
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
	 * Méthode A IMPLEMENTER...
	 */
	void runGame();


private:

	/**
	 * Méthode supprimant les 5 premières cartes du deck.
	 * Lance une exception si il y a moins de 5 cartes dans le deck.
	 */
	void burnCards();

	/**
	 * Méthode désallouant toutes les cartes du deck. Deck est vidé.
	 */
	void clearDeck();

	/**
	 * Méthode distribuant les deux premières cartes à tous les joueurs et à la banque.
	 */
	void dealCards();

	/**
	 * Tire une carte du deck et renvoie son pointeur.
	 * @return Pointeur vers la carte tirée du deck.
	 */
	Card* hitCard();

	/**
	 * Méthode qui initialise un tour : accueil des nouveaux joueurs, demande des mises et distribution des cartes.
	 */
	void initRound();

	/**
	 * Méthode créant un nouveau deck (sabot) neuf. Il contient 312 cartes (24 de chaque EType) non mélangées.
	 * @see Card::Card()
	 */
	void newDeck();

	void newGame();

	void newPlayer();

	void runRound();

	/**
	 * Méthode de battage (tri aléatoire) des cartes du deck.
	 * @see std::random_suffle()
	 */
	void shuffleDeck();

};

#endif