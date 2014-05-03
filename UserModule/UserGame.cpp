/*
 * UserGame.cpp
 *
 */

#include "UserGame.h"

UserGame::UserGame(int pBalance):player(0,0){
	this->myHand = this->player.getHand();
	this->com = new PlayerCommunication();
	this->player = new Player(this->com.CheckFiles(),pBalance);
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

		// si le joueur a ete ajoutee par le module bank
		if(this->id_message == 10){
			this->initRound();
			this->runRound();
		}
	}
	else this->quitGame();

}

void UserGame::initRound()
{
	int bet,num_joueur,betValue;
	//initialisations
	this->player.setBlackjack(false);
	this->player.setSurrender(false);
	this->player.deleteHand(this->myHand);
	this->myHand = NULL;

	bet = this->ihm.getBet();
	this->com.Bet(bet);

}

void UserGame::quitGame()
{
	this->player.deleteHand();
	this->com.QuitMessage();
}

void UserGame::runRound()
{
	while(true){
		this->message = this->com.ReadFile();
		sscanf(this->message, "%d %s", &this->id_message,this->reste);

		switch(this->id_message){
		case 1:
			if()
					break;
		case 2:
					break;
		case 3:
					break;
		case 4:
					break;
		case 5:
					break;
		case 6:
					break;
		case 7:
					break;
		case 8:
					break;
		case 9:
					break;
		case 10:
					break;
		case 11:
					break;
		case 12:
					break;
		case 13:
					break;
		}

		if(this->id_message == 6 && num_joueur == this->player.getId())
			this->player.decreaseBalance(betValue);

		/* ajout des deux cartes a la main du joueur */

		int typeCard;

		for(int i(0); i<2; i++)
		{
			this->com.ReadFile();
			sscanf(this->message, "%d %d %d %s", &this->id_message, &num_joueur, &typeCard, this->reste);

			if(this->id_message == 4 && num_joueur == this->player.getId())
				myHand->addCard(new Card(static_cast<EType>(typeCard)));
		}

		 /* reception des cartes de la banque*/
		this->com.ReadFile();
		sscanf(this->message, "%d %d %d %s", &this->id_message, &num_joueur, &typeCard, this->reste);

		if(this->id_message == 4 && num_joueur == this->player.getId())
			bankCard = new Card(static_cast<EType>(typeCard));
	this->myHand->isBlackjack();
	/* affichage de l'etat du jeu */
	this->ihm.PrintGameState(this->player,true,true,true,true);
	this->ihm.askAction();


}






