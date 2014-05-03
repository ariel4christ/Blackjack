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
	 * Methode permettant au joueur courant de demarer son jeux
	 */
	void runGame();
	/**
	 * Methode statique permetant d'obtenir le type d'une carte a partir de la valeur entiere associée
	 */
	static EType getType(int value);

private:
	Player player; /** Joueur **/
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable joueurs et l'exécutable bank */
	char* message; /**< char*. Stocke le message reçu*/
	char* reste;/**< char*.Stocke le reste du message (ce qu'on a pas encore lu)*/
	int id_message; /**< Entier. Code d'identification du message*/
	HMI ihm; /**<HMI. Objet permettant la communication entre le joueur humain et le module joueur*/
	Card bankCard; /**< Card.  carte de la banque*/

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
