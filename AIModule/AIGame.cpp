#include "AIGame.h"

AIGame::AIGame()
{
	int id = this->com.CheckFiles();

		if (id == -1)
			exit(-1);

	this->com.CreateFiles(id);
	this->players.push_back(Player(id,0)); /* joueur IA à la position 0*/
}

AIGame::~AIGame()
{
}

void AIGame::runGame()
{
	this->com.EnterGame();
	bool quit;
	while(!quit){

	}


}

void AIGame::runRound()
{
}

void AIGame::chooseAction()
{
}

void AIGame::quitGame()
{
}

void AIGame::emptyPlayerList()
{
}




