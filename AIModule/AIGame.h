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

	std::vector<int> previousBets;
	std::vector<Card> listOfCards;
	std::vector<Player> players;
	PlayerCommunication com;
	AI aiInterface;

	void quitGame();
	void runRound();
	void chooseAction();

};

#endif
