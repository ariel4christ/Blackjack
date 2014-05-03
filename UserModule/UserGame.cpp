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

	this->initRound();
	this->runRound();

}

void UserGame::initRound()
{

}

void UserGame::quitGame()
{

}

void UserGame::runRound()
{
}






