/*
 * UserGame.cpp
 *
 */

#include "UserGame.h"

UserGame::UserGame(int pBalance):player(this->com.CheckFiles(),pBalance){

}

UserGame::~UserGame() {
	// TODO Auto-generated destructor stub
}

void UserGame::runGame()
{
	if(this->player.getId()!= -1){
		this->com.CreateFiles(this->player.getId());
		this->com.EnterGame();
		this->initRound();
		this->runRound();
	}

}

void UserGame::initRound()
{
	this->messagethis->com.ReadFile();

}

void UserGame::quitGame()
{

}

void UserGame::runRound()
{
}






