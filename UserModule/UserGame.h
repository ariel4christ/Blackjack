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
	/**
	 * Constructeur de Usergame
	 */
	UserGame();
	/**
	 * Destructeur de UserGame
	 */
	virtual ~UserGame();
	/**
	 * Methode permettant au joueur courant de quitter le jeux
	 */
	void quitGame();
	/**
	 * Methode permettant au joueur courant de demarer son jeux
	 */
	void runGame();

private:
	int betMin;  /**< Entier. Mise minimale.*/
	int betMax;  /**< Entier. Mise maximale.*/

	Player player; /**< Player. Joueur courant **/
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable joueurs et l'exécutable bank */
	std::string message; /**< string. Stocke le message reçu*/
	HMI ihm; /**<HMI. Objet permettant la communication entre le joueur humain et le module joueur*/

	/**
	 * Methode permettant d' initialiser un tour
	 */
	void initRound();

	/**
	 * Methode permettant de faire un tour
	 */
	void runRound();

	/**
	 * Methode permettant de demander des actions au joueur en fontion de l'etat de sa(ses) main(s)
	 */
	void choseAction(PlayerHand* myhand);

};

#endif /* USERGAME_H_ */
