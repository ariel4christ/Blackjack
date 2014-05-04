/*
 * UserGame.cpp
 *
 */

#include "UserGame.h"

UserGame::UserGame(int pBalance):player(0,0){
	this->myHand = this->player.getHand();
	this->com = PlayerCommunication();
	this->player = Player(this->com.CheckFiles(),pBalance);
}

UserGame::~UserGame() {
	// TODO Auto-generated destructor stub
}

void UserGame::runGame()
{
	if(this->player.getId()!= -1){
		this->com.EnterGame();
		this->initRound();
		this->runRound();
	}
	else this->quitGame();

}

void UserGame::initRound()
{

	//initialisations
	this->player.setBlackjack(false);
	this->player.setSurrender(false);
	this->player.deleteHand(this->myHand);
	this->myHand = NULL;

	int bet;
	bet = this->ihm.getBet();
	this->com.Bet(bet);

}

void UserGame::quitGame()
{
	this->player.deleteHand(this->myHand);
	this->com.QuitMessage();
}

void UserGame::runRound()
{
	int num_joueur,typeCard,argent;

	while(true){

		this->message = this->com.ReadFile();
		sscanf(this->message.c_str(), "%d %s", &this->id_message, this->reste);

		switch(this->id_message){
		case 1:
			if(this->ihm.insurrance()) this->com.RespondInsurance(1);
			else this->com.RespondInsurance(0);
					break;
		case 2:
		case 3: this->initRound();
					break;
		case 4:
			sscanf(this->message.c_str(), "%d %d %d %s", &this->id_message, &num_joueur, &typeCard, this->reste);
			if(num_joueur == this->player.getId()){
				this->myHand->addCard(new Card(static_cast<EType>(typeCard)));
			}
					break;
		case 5:
			int balance;
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &balance);
			if(num_joueur == this->player.getId()){
				this->player.setBalance(balance);
			}
					break;
		case 6:
			int bet;
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &bet);
			if(num_joueur == this->player.getId()){
				this->myHand->setBet(bet);
			}
					break;
		case 7:
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId()){
				this->player.Stand(this->myHand);
			}
					break;
		case 8:
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId()){
				this->player.Surrender(this->myHand);
			}
					break;
		case 9:
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId()){
				this->quitGame();
			}
					break;
		case 10:
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId()){
				this->com.CreateFiles(this->player.getId());
			}
					break;
		case 11:
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur,&argent);
			if(num_joueur == this->player.getId()){
				this->player.increaseBalance(argent);
			}
					break;
		case 12:
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur,&argent);
			if(num_joueur == this->player.getId()){
				this->player.decreaseBalance(argent);
			}
					break;
		case 13:
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId()){
				/* a finir*/
				this->myHand->setHand();
			}
					break;
		}
	/* affichage de l'etat du jeu */
	this->ihm.PrintGameState(this->player,true,true,true,true);
	this->ihm.askAction();


}






