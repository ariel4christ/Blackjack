/**
 * Classe BankGame. Classe de gestion du jeu, exécutable banque.
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

	BankCommunication com; /**< BankCommunication. Objet permettant la communication entre l'exécutable Bank et les exécutables joueurs.*/
	BankInterface interface; /**< BankInterface. Objet réalisant les interaction entre le programme et l'utilisateur.*/

public:

	/**
	 * Getteur de bank.
	 * @return  Référence de l'objet bank.
	 */
	inline Bank& getBank() { return this->bank; }

	/**
	 * Getteur de player.
	 * @return  Référence du vecteur des joueurs.
	 */
	inline std::vector<Player*>& getPlayers() { return this->player; }

	/**
	 * Méthode retournant l'attribut com par référence.
	 * @return  BankCommunication   Référence de com.
	 */
	inline BankCommunication& getCom() { return this->com; }
	
	/**
	 * Méthode statique retournant la mise minimale autorisée.
	 * @return  Entier  Mise min.
	 */
	static int getBetMin();

	/**
	 * Méthode statique retournant la mise maximale autorisée.
	 * @return  Entier  Mise min.
	 */
	static int getBetMax();

	/**
	 * Méthode statique retournant le solde initial d'un joueur.
	 * @return  Entier long     Solde initial d'un joueur.
	 */
	static long getBalancePlayerInit();

	/**
	 * Méthode statique déterminant la mise minimale autorisée.
	 * @param   i   Nouvelle mise minimale autorisée.
	 */
	static void setBetMin(int i);

	/**
	 * Méthode statique déterminant la mise maximale autorisée.
	 * @param   i   Nouvelle mise maximale autorisée.
	 */
	static void setBetMax(int i);

	/**
	 * Méthode statique déterminant le solde initial d'un joueur.
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
	 * Méthode qui gere les tours de jeu.
	 * @return 0 lorsqu'il n'y a plus de joueur dans le jeu.
	 */
	int runGame();

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
	 * Gestion de la fin d'un tour. Calcule si la main du joueur en paramètre a gagné ou perdu.
	 * @see Participant::increaseBalance()
	 * @see Participant::decreaseBalance()
	 * @see BankCommunication::setBalance()
	 * @param   p           Pointeur vers le joueur pour lequel on étudie la finalité de sa fin.
	 * @param   secondHand  Entier à 0 si c'est la première main du joueur, 1 et c'est la deuxième main.
	 */
	void endRound(Player *p, int secondHand);

	/**
	 * Tire une carte du deck et renvoie son pointeur.
	 * @return  Pointeur vers la carte tirée du deck.
	 */
	Card* hitCard();

	/**
	 * Méthode qui initialise un tour : accueil des nouveaux joueurs, demande des mises et distribution des cartes.
	 * @return  0 si le jeu est fini car il n'y a plus de joueur, 1 sinon.
	 */
	int initRound();

	/**
	 * Méthode gérant la partie assurance
	 * @return	0	Le tour est fini
	 1	Le tour n'est pas fini.
	 */
	int insurance();

	/**
	 * Méthode créant un nouveau deck (sabot) neuf. Il contient 312 cartes (24 de chaque EType) non mélangées.
	 * @see Card::Card()
	 */
	void newDeck();

	/**
	 * Méthode l'initialisation du jeu.
	 * @see newDeck()
	 * @see shuffleDeck()
	 * @see burnCards()
	 * @see BankCommunication::ChechFiles()
	 */
	void newGame();

	/**
	 * Méthode incluant les nouveaux joueurs dans le jeu.
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
	 * Methode gerant la suppression d'un joueur du jeu. Desalloue le joueur en paramètre. Fini le jeu s'il n'y a plus de joueur.
	 * @see Player::~Player()
	 * @see BankCommunication::HasQuit()
	 * @param   p   Pointeur vers le joueur qui quitte le jeu.
	 * @return  0   si le jeu est fini car il n'y a plus de joueur, 1 sinon.
	 */
	int quitPlayer(Player *p);

	/**
	 * Methode gerant le deroulement d'un tour.
	 * @return  1   le tour s'est fini sans probleme, 0 si le jeu est terminé.
	 */
	int runRound();

	/**
	 * Méthode de battage (tri aléatoire) des cartes du deck.
	 * @see std::random_suffle()
	 */
	void shuffleDeck();
};

#endif
