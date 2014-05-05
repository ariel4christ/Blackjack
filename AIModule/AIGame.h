/**
 * Classe AIGame.
 */

#ifndef _AIGAME_H
#define _AIGAME_H

#include <vector>
#include <string>
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
	Card bankCard; /**< Bank. Objet bankCard permetant d'enregistrer la carte de la banque necessaire pour le calcul des probabilités*/
	std::string message; /**< string. message recu de la banque */
	PlayerHand *hand1,*hand2; /**<PlayerHand. les mains de l'IA */
	int id_message; /**< Entier. Code d'identification du message*/

	/**
	 * Permet de quitter le jeu
	 */
	void quitGame();

	/**
	 * Permets de jouer un tour
	 */
	bool runRound();

	/**
	 * Permet de choisir l'action appropriée à faire
	 * @params myhand la main sur laquelle sera appliquée l'action à faire
	 */
	void chooseAction(PlayerHand* myhand);

	/**
	 * Permet de vider la liste des joueurs humains
	 */
	void emptyPlayerList();

};

#endif
