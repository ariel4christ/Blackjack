/*
 * UserGame.cpp
 *
 */

#include "UserGame.h"

UserGame::UserGame() : player(0,0), com()
{
	int id = this->com.CheckFiles();

	if (id == -1)
		exit(-1);

	this->com.CreateFiles(id);
	this->player = Player(id,0);
}

UserGame::~UserGame() {

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
	this->player.deleteHand(this->myHand1);
	this->player.deleteHand(this->myHand2);
	this->player.setInsurance(false);
	this->myHand1 = NULL;
	this->myHand2 = NULL;

	int bet;
	bet = this->ihm.getBet();
	this->com.Bet(bet);
	this->myHand1 = this->player.getHand();
	this->myHand2 = this->player.getHand2();

}

void UserGame::quitGame()
{
	this->player.deleteHand(this->myHand1);
	this->player.deleteHand(this->myHand2);
	this->~UserGame();
	exit(1);
}

void UserGame::runRound()
{
	int num_joueur,typeCard,typeCard2,argent,main;
	bool quit = false;

	while(!quit)
	{

		this->message = this->com.ReadFile();
		sscanf(this->message.c_str(), "%d", &this->id_message);

		switch(this->id_message)
		{

		case 1:// AskInsurance receive
			if(this->ihm.insurrance())
				this->com.RespondInsurance(1);
			else this->com.RespondInsurance(0);
			break;

		case 2: // EndRound receive
			this->player.deleteHand(this->player.getHand());
			this->player.deleteHand(this->player.getHand2());
			break;

		case 3: // RoundStart receive
			this->initRound();
			break;

		case 4: // SendCard receive
			sscanf(this->message.c_str(), "%d %d %d %d", &this->id_message, &num_joueur, &typeCard, &main);

			if(num_joueur == this->player.getId())
			{
				if(!main)
					this->myHand1->addCard(new Card(static_cast<EType>(typeCard)));
				else this->myHand2->addCard(new Card(static_cast<EType>(typeCard)));
			}
			break;

		case 5: // SetBalance receive
			int balance;
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &balance);
			if(num_joueur == this->player.getId())
			{
				this->player.setBalance(balance);
			}
			break;

		case 6: // SetBet receive
			int bet;
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &bet);
			if(num_joueur == this->player.getId())
			{
				this->myHand1->setBet(bet);
			}
			break;

		case 7:	// ValidStand receive
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &main);
			if(num_joueur == this->player.getId())
			{
				if(!main) this->player.Stand(this->myHand1);
				else this->player.Stand(this->myHand2);
			}
			break;

		case 8: // ValidSurrender receive
			sscanf(this->message.c_str(), "%d %d %d ", &this->id_message, &num_joueur, &main);
			if(num_joueur == this->player.getId())
			{
				if(!main) this->player.Surrender(this->myHand1);
				else this->player.Surrender(this->myHand2);
			}
			break;

		case 9: // HasQuit receive
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId())
			{
				quit = true;
			}
			break;

		case 10: // PlayerEntered receive
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId())
			{
				// que doit t'on mettre ici?
			}
			break;

		case 11: // CreditPlayer receive
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur,&argent);
			if(num_joueur == this->player.getId())
			{
				this->player.increaseBalance(argent);
			}
			break;

		case 12: // DebitPlayer receive
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur,&argent);
			if(num_joueur == this->player.getId())
			{
				this->player.decreaseBalance(argent);
			}
			break;

		case 13: // SetHand receive
			sscanf(this->message.c_str(), "%d %d %d %d %d ", &this->id_message, &num_joueur, &main, &typeCard, &typeCard2);
			if(num_joueur == this->player.getId())
			{
				/* construction d'une main a partir des cartes recues*/
				Hand hand;

				hand.addCard(new Card(static_cast<EType>(typeCard)));
				hand.addCard(new Card(static_cast<EType>(typeCard2)));

				if(!main) this->myHand1->setHand(hand);
				else  this->myHand2->setHand(hand);

			}
			break;

		case 14: // ValidSplit receive
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->player.getId())
			{
				this->player.newHand();
			}
			break;

		case 15: // AskAction receive
			sscanf(this->message.c_str(), "%d %d %d ", &this->id_message, &num_joueur, &main);
			if(num_joueur == this->player.getId())
			{
				if(!main) this->choseAction(myHand1);
				else this->choseAction(myHand2);
			}
			break;

		}
	}

	this->com.RemoveFiles(this->player.getId());
}

void UserGame::choseAction(PlayerHand *myhand)
{
	bool spliter = false;
	bool doubler = false;
	bool hit = false;
	bool stand = true;
	char reponse;

	if(this->myHand1->isPair() && this->myHand2 == NULL) spliter = true;
	if(this->myHand1->numberOfCards() == 2 && this->myHand2 == NULL) doubler = true;
	if(myhand->getValue1() <= 21) hit = true;

	/* affichage de l'etat du jeu */
	this->ihm.PrintGameState(this->player,hit,spliter,doubler,stand);

	/* recois la reponse*/
	reponse = this->ihm.askAction(hit,spliter,doubler,stand);

	/* valeur permetant de connaitre la main sur laquelle seront appliquées les actions */
	int value;

	if(myhand == this->myHand1) value = 0;
	else value = 1;

	switch(reponse)
	{
	case 'C': // Demander carte

		this->com.AskToHIt(value);
			break;

	case 'P': // Split

		this->com.Split(value);
			break;

	case 'D': // Doubler

		this->com.Double();
			break;

	case 'R': // Rester

		this->com.Stand(value);
			break;

	case 'A': // Abandonner la main

		this->com.Surrender(value);
			break;

	case 'Q': // Abandonner la main ET quitter le jeu

		this->com.QuitMessage();
			break;
	}

}








