#include "AIGame.h"

AIGame::AIGame(): betMin(5), betMax(100), ia(0,0), com(),bankCard(NaN)
{
	int id = this->com.CheckFiles();

		if (id == -1)
			exit(-1);

		this->com.CreateFiles(id);
		this->ia = Player(id, 0);
}

AIGame::~AIGame()
{
}

void AIGame::runGame()
{
	this->com.EnterGame();
	bool quit = false; // variable permettant de quitter le jeu

	while(!quit){

		this->ia.setInsurance(false);
		this->ia.setBlackjack(false);
		this->ia.setInsurance(false);

		this->ia.deleteHand(this->ia.getHand());
		this->ia.deleteHand(this->ia.getHand2());

		int bet = this->aiInterface.getBet();
		this->com.Bet(bet);
		this->bankCard.setType(NaN);

		quit = this->runRound();
	}

	this->quitGame();



}

bool AIGame::runRound()
{
	int num_joueur,typeCard,typeCard2,argent,main, id_message;
	bool endRound = false; /* permet de savoir si le tour est achevé */
	bool endGame = false; /* permet de savoir si le jeu est achevé */


	while(!endRound)
	{
		this->message = this->com.ReadFile();
		sscanf(this->message.c_str(), "%d", &id_message);

		switch(id_message)
		{

		case 1:// AskInsurance receive

			if(this->aiInterface.insurrance())
				this->com.RespondInsurance(1);
			else
				this->com.RespondInsurance(0);
			break;

		case 2: // EndRound receive
			endRound = true;
			break;
		case 3: // RoundStart receive
			endRound = true;
			break;

		case 4: // SendCard receive
			sscanf(this->message.c_str(), "%d %d %d %d", &id_message, &num_joueur, &typeCard, &main);

			if(num_joueur == this->ia.getId())
			{
				if(!main)
					this->ia.getHand()->addCard(new Card(static_cast<EType>(typeCard)));
				else
					this->ia.getHand2()->addCard(new Card(static_cast<EType>(typeCard)));

			}
			else
				if( num_joueur == 0)/* reception de la carte de la banque */
					this->bankCard.setType(static_cast<EType>(typeCard));

			this->listOfCards.push_back(Card(static_cast<EType>(typeCard))); // recupere les cartes de tous les joueurs les siennes comprises
			break;

		case 5: // SetBalance receive
			int balance;

			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur, &balance);
			if(num_joueur == this->ia.getId())
			{
				this->ia.setBalance(balance);
			}
			break;

		case 6: // SetBet receive
			int bet;
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur, &bet);

			if(num_joueur == this->ia.getId())
			{
				this->ia.getHand()->setBet(bet);
				this->previousBets.push_back(bet);
			}
			break;

		case 7:	// ValidStand receive
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur, &main);
			if(num_joueur == this->ia.getId())
			{
				if(!main)
					this->ia.Stand(this->ia.getHand());
				else
					this->ia.Stand(this->ia.getHand2());
			}
			break;

		case 8: // ValidSurrender receive
			sscanf(this->message.c_str(), "%d %d %d ", &id_message, &num_joueur, &main);
			if(num_joueur == this->ia.getId())
			{
				if(!main)
					this->ia.Surrender(this->ia.getHand());
				else
					this->ia.Surrender(this->ia.getHand2());
			}
			break;

		case 9: // HasQuit receive
			sscanf(this->message.c_str(), "%d %d ", &id_message, &num_joueur);
			if(num_joueur == this->ia.getId())
			{
				 endGame = true;
				 endRound = true;
			}
			break;

		case 10: // PlayerEntered receive
			sscanf(this->message.c_str(), "%d %d %d %d", &id_message, &num_joueur, &betMin, &betMax);
			if (num_joueur == this->ia.getId())
			{
				this->betMin = betMin;
				this->betMax = betMax;
			}
			break;

		case 11: // CreditPlayer receive
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,&argent);
			if(num_joueur == this->ia.getId())
			{
				this->ia.increaseBalance(argent);
			}
			break;

		case 12: // DebitPlayer receive
			sscanf(this->message.c_str(), "%d %d %d", &id_message, &num_joueur,&argent);
			if(num_joueur == this->ia.getId())
			{
				this->ia.decreaseBalance(argent);
			}
			break;

		case 13: // SetHand receive
			sscanf(this->message.c_str(), "%d %d %d %d %d ", &id_message, &num_joueur, &main, &typeCard, &typeCard2);
			if(num_joueur == this->ia.getId())
			{
				/* construction d'une main a partir des cartes recues*/
				Hand hand;

				hand.addCard(new Card(static_cast<EType>(typeCard)));
				hand.addCard(new Card(static_cast<EType>(typeCard2)));

				this->listOfCards.push_back(Card(static_cast<EType>(typeCard)));
				this->listOfCards.push_back(Card(static_cast<EType>(typeCard2)));

				if(!main)
					this->ia.getHand()->setHand(hand);
				else
					this->ia.getHand2()->setHand(hand);

			}
			break;

		case 14: // ValidSplit receive
			sscanf(this->message.c_str(), "%d %d ", &id_message, &num_joueur);
			if(num_joueur == this->ia.getId())
			{
				this->ia.newHand();
			}
			break;

		case 15: // AskAction receive
			sscanf(this->message.c_str(), "%d %d %d ", &id_message, &num_joueur, &main);
			if(num_joueur == this->ia.getId())
			{
				if(!main)
					this->chooseAction(this->ia.getHand());
				else
					this->chooseAction(this->ia.getHand2());
			}
			break;
		}
	}
	return endGame;
}

void AIGame::chooseAction(PlayerHand* myhand) // basee sur la "basic strategy"
{
	switch(this->bankCard.getValue()){

	case 1:
		break;

	case 1:
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

	}



}

void AIGame::quitGame()
{
	this->ia.deleteHand(this->ia.getHand());
	this->ia.deleteHand(this->ia.getHand2());
	this->~AIGame();
	exit(1);
}






