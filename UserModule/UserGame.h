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

	PlayerCommunication& getCom()
	{
		return this->com;
	}

	Player& getPlayer()
	{
		return this->player;
	}

	static int getBetMin()
	{
		return UserGame::betMin;
	}
	static int getBetMax()
	{
		return UserGame::betMax;
	}

	static void setBetMin(int i)
	{
		betMin = i;
	}
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

	void endRound();

};

#endif /* USERGAME_H_ */
