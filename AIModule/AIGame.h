/**
 * Classe AIGame.
 */

#ifndef _AIGAME_H
#define _AIGAME_H

#include <vector>
#include <stdexcept>
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include "../GameModule/Player.h"
#include "../CommunicationModule/PlayerCommunication.h"
#include "../InterfaceModule/AI.h"

class AIGame
{
public:

	AIGame();
	virtual ~AIGame();
	void runGame();

private:

	std::vector<int> previousBets; /**< vector<int>. Liste des differentes mises au cours du jeu par l'IA */
	std::vector<Card> listOfCards; /**< vector<Card>. Liste de toutes les cartes qui on été jouées au cours du jeux */
	std::vector<Player> players;/**< vector<Player>. Liste de tous les joueurs du jeux à la position 0 ,'est l'IA, le reste les joueurs humains */
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable IA et l'exécutable bank */
	AI aiInterface; /**< AI. Objet permettant l'affichages des differentes étapes de calcul de l'IA */
	Bank *banque; /**< Bank. Objet bank permetant d'avoir toutes les informations sur la banque necessaire pour le calcul des probabilités*/

	/**
	 * Permet de quitter le jeu
	 */
	void quitGame();

	/**
	 * Permets de jouer un tour
	 */
	void runRound();

	/**
	 * Permet de choisir l'action appropriée à faire
	 */
	void chooseAction();

	/**
	 * Permet de vider la liste des joueurs humains
	 */
	void emptyPlayerList();

};

#endif
