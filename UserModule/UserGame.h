/**
 * Classe UserGame. Classe de gestion des joueurs, exécutable User (joueur humain).
 * @author Ariel NONO
 * @author Thomas MAINGUY
 * @author Christophe HUBERT
 */

#ifndef USERGAME_H_
#define USERGAME_H_

#include <vector>
#include "../GameModule/Player.h"
#include "../CommunicationModule/PlayerCommunication.h"
#include "../InterfaceModule/HMI.h"

class UserGame
{
public:

	/**
	 * Constructeur de Usergame.
	 */
	UserGame();

	/**
	 * Destructeur de UserGame.
	 */
	virtual ~UserGame();

	/**
	 * Methode permettant au joueur courant de quitter le jeux.
	 */
	void quitGame();

	/**
	 * Methode gèrant le déroulement du jeux.
	 */
	void runGame();

	/**
	 * Getter de la communication
	 * @return Référence de l'objet com
	 */
	PlayerCommunication& getCom()
	{
		return this->com;
	}

	/**
	 * Getter de player
	 * @return Référence de player
	 */
	Player& getPlayer()
	{
		return this->player;
	}

	/**
	 * Méthode statique retournant la mise minimale autorisée.
	 * @return  Entier  Mise min.
	 */
	static int getBetMin()
	{
		return UserGame::betMin;
	}

	/**
	 * Méthode statique retournant la mise maximale autorisée.
	 * @return  Entier  Mise min.
	 */
	static int getBetMax()
	{
		return UserGame::betMax;
	}

	/**
	 * Méthode statique déterminant la mise minimale autorisée.
	 * @param   i   Nouvelle mise minimale autorisée.
	 */
	static void setBetMin(int i)
	{
		betMin = i;
	}

	/**
	 * Méthode statique déterminant la mise maximale autorisée.
	 * @param   i   Nouvelle mise maximale autorisée.
	 */
	static void setBetMax(int i)
	{
		betMax = i;
	}

private:
	static int betMin; /**< Entier. Mise minimale.*/
	static int betMax; /**< Entier. Mise maximale.*/

	Player player; /**< Player. Joueur courant. */
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable joueurs et l'exécutable bank. */
	std::string message; /**< string. Stocke le message reçu. */
	HMI ihm; /**< HMI. Objet permettant la communication entre le joueur humain et le module joueur. */

	/**
	 * Méthode d'initialisation d'un tour.
	 */
	void initRound();

	/**
	 * Méthode qui gère le déroulement d'un tour.
	 */
	void runRound();

	/**
	 * Méthode permettant de demander une action au joueur en fontion de l'état du jeu.
	 * @param   myHand  Pointeur vers la main pour laquelle on demande une action.
	 * @param   secHand Entier, vaut 0 si action sur main 1 et 1 si action sur main 2.
	 */
	void chooseAction(PlayerHand* myhand, int secHand);

	/**
	 * Méthode qui gère la fin d'un tour
	 */
	void endRound();

};

#endif /* USERGAME_H_ */
