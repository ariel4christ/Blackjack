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
		this->com.ReadFile();
			sscanf(this->message, "%d %s", &this->id_message, this->reste);

		if(this->id_message == 10){ // si le joueur a ete ajoutee par le module bank
			this->initRound();
			this->runRound();
		}
	}

}

void UserGame::initRound()
{
	int bet,num_joueur,betValue;

	this->player.setBlackjack(false);
	this->player.setSurrender(false);

	bet = this->ihm.getBet();
	this->com.Bet(bet);

	this->com.ReadFile();
	sscanf(this->message, "%d %d %d", &this->id_message, &num_joueur, &betValue);

	if(this->id_message == 6 && num_joueur == this->player.getId())
		this->player.decreaseBalance(betValue);

}

void UserGame::quitGame()
{

}

void UserGame::runRound()
{
	this->com.ReadFile();
	sscanf(this->message, "%d %d %d %s", &this->id_message, &num_joueur, &typeCard, this->reste);




}






