/**
 * Classe UserGame. Classe de gestion des joueurs
 */

#ifndef USERGAME_H_
#define USERGAME_H_

#include <vector>
#include "../GameModule/Player.h"
#include "../CommunicationModule/PlayerCommunication.h"

class UserGame {
public:
	UserGame();
	virtual ~UserGame();
private:
	Player player; /** Joueur **/
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable joueurs et l'exécutable bank */

};

#endif /* USERGAME_H_ */
