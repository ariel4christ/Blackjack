#include "AIGame.h"

AIGame::AIGame()
{
	int id = this->com.CheckFiles();

		if (id == -1)
			exit(-1);

	this->players.push_back(Player(id,0)); /* joueur IA à la position 0*/
}

AIGame::~AIGame()
{
}

void AIGame::runGame()
{
	this->com.EnterGame();
	bool quit = false;
	while(!quit){
		this->emptyPlayerList();
		this->players[0].setInsurance(false);
		this->players[0].setBlackjack(false);
		this->players[0].setInsurance(false);
		this->players[0].deleteHand(this->hand1);
		this->players[0].deleteHand(this->hand2);
		this->hand1 = NULL;
		this->hand2 = NULL;
		int bet = this->aiInterface.getBet();
		this->com.Bet(bet);
		quit = this->runRound();
	}


}

bool AIGame::runRound()
{
	int num_joueur,typeCard,typeCard2,argent,main;
	bool endRound = false; /* permet de savoir si le tour est achevé */
	bool endGame = false; /* permet de savoir si le jeu est achevé */

	this->hand1 = this->players[0].getHand();
	this->hand2 = this->players[0].getHand2();

	while(!endRound)
	{

		this->message = this->com.ReadFile();
		sscanf(this->message.c_str(), "%d", &this->id_message);

		switch(this->id_message)
		{

		case 1:// AskInsurance receive
			if(this->aiInterface.insurrance())
				this->com.RespondInsurance(1);
			else this->com.RespondInsurance(0);
			break;

		case 2: // EndRound receive

		case 3: // RoundStart receive
			endRound = true;
			break;

		case 4: // SendCard receive
			sscanf(this->message.c_str(), "%d %d %d %d", &this->id_message, &num_joueur, &typeCard, &main);

			if(num_joueur == this->players[0].getId())
			{
				if(!main)
					this->hand1->addCard(new Card(static_cast<EType>(typeCard)));
				else this->hand2->addCard(new Card(static_cast<EType>(typeCard)));

			}
			this->listOfCards.push_back(Card(static_cast<EType>(typeCard))); // recupere les cartes de tous les joueurs les siennes comprises
			break;

		case 5: // SetBalance receive
			int balance;
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &balance);
			if(num_joueur == this->players[0].getId())
			{
				this->players[0].setBalance(balance);
			}
			break;

		case 6: // SetBet receive
			int bet;
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &bet);
			if(num_joueur == this->players[0].getId())
			{
				this->hand1->setBet(bet);
				this->previousBets.push_back(bet);
			}
			break;

		case 7:	// ValidStand receive
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur, &main);
			if(num_joueur == this->players[0].getId())
			{
				if(!main) this->players[0].Stand(this->hand1);
				else this->players[0].Stand(this->hand2);
			}
			break;

		case 8: // ValidSurrender receive
			sscanf(this->message.c_str(), "%d %d %d ", &this->id_message, &num_joueur, &main);
			if(num_joueur == this->players[0].getId())
			{
				if(!main) this->players[0].Surrender(this->hand1);
				else this->players[0].Surrender(this->hand2);
			}
			break;

		case 9: // HasQuit receive
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->players[0].getId())
			{
				 endGame = true;
				 endRound = true;
			}
			break;

		case 10: // PlayerEntered receive
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->players[0].getId())
			{
				this->com.CreateFiles(this->players[0].getId());
			}
			break;

		case 11: // CreditPlayer receive
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur,&argent);
			if(num_joueur == this->players[0].getId())
			{
				this->players[0].increaseBalance(argent);
			}
			break;

		case 12: // DebitPlayer receive
			sscanf(this->message.c_str(), "%d %d %d", &this->id_message, &num_joueur,&argent);
			if(num_joueur == this->players[0].getId())
			{
				this->players[0].decreaseBalance(argent);
			}
			break;

		case 13: // SetHand receive
			sscanf(this->message.c_str(), "%d %d %d %d %d ", &this->id_message, &num_joueur, &main, &typeCard, &typeCard2);
			if(num_joueur == this->players[0].getId())
			{
				/* construction d'une main a partir des cartes recues*/
				Hand hand;

				hand.addCard(new Card(static_cast<EType>(typeCard)));
				hand.addCard(new Card(static_cast<EType>(typeCard2)));

				this->listOfCards.push_back(Card(static_cast<EType>(typeCard)));
				this->listOfCards.push_back(Card(static_cast<EType>(typeCard2)));

				if(!main) this->hand1->setHand(hand);
				else  this->hand2->setHand(hand);

			}
			break;

		case 14: // ValidSplit receive
			sscanf(this->message.c_str(), "%d %d ", &this->id_message, &num_joueur);
			if(num_joueur == this->players[0].getId())
			{
				this->players[0].newHand();
			}
			break;

		case 15: // AskAction receive
			sscanf(this->message.c_str(), "%d %d %d ", &this->id_message, &num_joueur, &main);
			if(num_joueur == this->players[0].getId())
			{
				if(!main) this->chooseAction(hand1);
				else this->chooseAction(hand2);
			}
			break;
		}
	}
	return endGame;
}

void AIGame::chooseAction(PlayerHand* myhand)
{

}

void AIGame::quitGame()
{
	this->players[0].deleteHand(this->hand1);
	this->players[0].deleteHand(this->hand2);
	this->~AIGame();
	exit(1);
}

void AIGame::emptyPlayerList()
{
	int taille = this->players.size();

	for(int i(1); i<taille ; i++)
		this->players.pop_back();

}




