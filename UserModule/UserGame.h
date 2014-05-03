/**
 * Classe UserGame. Classe de gestion des joueurs
 */

#ifndef USERGAME_H_
#define USERGAME_H_

#include <vector>
#include "../GameModule/Player.h"
#include "../CommunicationModule/PlayerCommunication.h"
#include "../InterfaceModule/HMI.h"

class UserGame {
public:

	UserGame(int pBalance);
	virtual ~UserGame();
	/**
	 * Methode permettant au joueur courant de quitter le jeux
	 */
	void quitGame();
	/**
	 * Methode permettant au joueur courant de demarer le son jeux
	 */
	void runGame();

private:
	Player player; /** Joueur **/
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable joueurs et l'exécutable bank */
	int position;  /**< Entier. Numero du Joeur.*/
	std::string message; /**< String. Message echangé avec l'executable banque*/

	/**
	 * Methode permettant d' initialiser un tour
	 */
	void initRound();

	/**
	 * Methode permettant de faire un tour
	 */
	void runRound();

};

#endif /* USERGAME_H_ */
