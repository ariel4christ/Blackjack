/**
 * UserGame.cpp
 * @author Ariel NONO
 * @author Thomas MAINGUY
 * @author Christophe HUBERT
 */

#include "UserGame.h"

using namespace std;

int UserGame::betMin = 5;
int UserGame::betMax = 100;

UserGame::UserGame() : player(0), com()
{
	int id = this->com.CheckFiles();

	if (id == -1)
		exit(-1);

	this->com.CreateFiles(id);
	this->player.setId(id);
}

UserGame::~UserGame() {
    this->ihm.PrintMessage("~ Vous avez quitté la partie !\n~ A bientot :)");
}

void UserGame::runGame()
{
    this->com.EnterGame();
	int id = this->player.getId();
    ihm.PrintEnterGame(id);

	string str = com.ReadFile();
	int id_message;
	sscanf(str.c_str(), "%d", &id_message);
	if (id_message == 10)  // Message PlayerEntered
	{
        int id_player, bet_min, bet_max;
        sscanf(str.c_str(), "%d %d %d %d", &id_message, &id_player, &bet_min, &bet_max);
        if (id == id_player)
        {
            UserGame::betMin = bet_min;
            UserGame::betMax = bet_max;
        }
        com.sendAck();
	}
	else throw runtime_error("Erreur reception message PlayerEntered");

	str = com.ReadFile();
	sscanf(str.c_str(), "%d", &id_message);
	if (id_message == 5)
	{
        int id_player, balance;
        sscanf(str.c_str(), "%d %d %d", &id_message, &id_player, &balance);
        if (id == id_player)
            player.setBalance(balance);
        com.sendAck();
	}
	else throw runtime_error("Message d'initialisation du solde joueur non recu");

	this->runRound();
	this->quitGame();
}

void UserGame::initRound()
{
	this->player.setBlackjack(false);
	this->player.setSurrender(false);
	this->player.setInsurance(false);
    if (player.getHand() != NULL)
        this->player.setHand(NULL);
    if (player.getHand2() != NULL)
        this->player.setHand2(NULL);

	int bet;

	bet = this->ihm.getBet(this->player);
	if (bet == -1)
        this->com.QuitMessage();

	this->com.Bet(bet);

}

void UserGame::quitGame()
{
    if (player.getBalance() < betMin);
        this->ihm.PrintMessage("~ Votre solde est insuffisant pour continuer.\n~ Vous avez perdu :(");
	this->player.setHand(NULL);
	this->player.setHand(NULL);
}

void UserGame::runRound()
{
	int num_joueur, typeCard, typeCard2, argent, main, betMin = 0, betMax = 0;
	bool quit = false;
	int id = this->player.getId();

	while(!quit)
	{
        string str;
        int id_message;
		str = this->com.ReadFile();
		sscanf(str.c_str(), "%d", &id_message);

		switch(id_message)
		{

		case 1:// AskInsurance receive
			if (this->ihm.insurrance(this->player))
			{
				this->com.RespondInsurance(1);
				this->player.decreaseBalance(this->player.getHand()->getBet() / 2);
			}
			else
				this->com.RespondInsurance(0);
			break;

		case 2: // EndRound receive
            this->endRound();
            com.sendAck();
			break;

		case 3: // RoundStart receive
			this->initRound();
			break;

		case 4: // SendCard receive
			sscanf(str.c_str(), "%d %d %d %d", &id_message, &num_joueur, &typeCard, &main);

			if (num_joueur == id)
			{
				if (!main)
					this->player.getHand()->addCard(new Card(static_cast<EType>(typeCard)));
				else
                    this->player.getHand2()->addCard(new Card(static_cast<EType>(typeCard)));

                if (this->player.getHand()->isBlackjack() && this->player.getHand2() == NULL)
                    ihm.PrintMessage("~ BRAVO, vous faites Blackjack !\n~ Attendez la fin du tour...");
			}

			this->com.sendAck();
			break;

		case 5: // SetBalance receive
			int balance;
			sscanf(str.c_str(), "%d %d %d", &id_message, &num_joueur, &balance);
			if (num_joueur == id)
			{
				this->player.setBalance(balance);
			}
			this->com.sendAck();
			break;

		case 6: // SetBet receive
			int bet;
			sscanf(str.c_str(), "%d %d %d", &id_message, &num_joueur, &bet);
			if (num_joueur == id)
			{
                if (player.getHand() == NULL)
                    this->player.newHand(bet);
                this->player.decreaseBalance(bet);
			}
			this->com.sendAck();
			break;

		case 7:	// ValidStand receive
			sscanf(str.c_str(), "%d %1d %1d", &id_message, &num_joueur, &main);
			if (num_joueur == id)
			{
				if (main == 0)
					this->player.Stand(this->player.getHand());
				else if (main == 1)
					this->player.Stand(this->player.getHand2());
                else throw runtime_error("erreur numero de main dans validStand");
			}
			this->com.sendAck();
			break;

		case 8: // ValidSurrender receive
			sscanf(str.c_str(), "%d %d %d", &id_message, &num_joueur, &main);
			if (num_joueur == id)
			{
				if (!main)
					this->player.Surrender(this->player.getHand());
				else
					this->player.Surrender(this->player.getHand2());
			}
			this->com.sendAck();
			break;

		case 9: // HasQuit receive
			sscanf(str.c_str(), "%d %d", &id_message, &num_joueur);
			if (num_joueur == id)
			{
				quit = true;
			}
			else
                cout << "~~~~~ Le joueur " << num_joueur << " a quitté le jeu. ~~~~~" << endl << endl;
			com.sendAck();
			break;

		case 10: // PlayerEntered receive
			sscanf(str.c_str(), "%d %d %d %d", &id_message, &num_joueur, &betMin, &betMax);
			if (num_joueur == id)
			{
				this->betMin = betMin;
				this->betMax = betMax;
			}
			com.sendAck();
			break;

		case 11: // CreditPlayer receive
			sscanf(str.c_str(), "%d %d %d", &id_message, &num_joueur,&argent);
			if (num_joueur == id)
			{
				this->player.increaseBalance(argent);
			}
			break;

		case 12: // DebitPlayer receive
			sscanf(str.c_str(), "%d %d %d", &id_message, &num_joueur,&argent);
			if(num_joueur == id)
			{
				this->player.decreaseBalance(argent);
			}
			break;

		case 13: // SetHand receive
			int sizeHand;
			sscanf(str.c_str(), "%d %d %d %d %d %d", &id_message, &num_joueur, &main, &sizeHand, &typeCard, &typeCard2);
			if (num_joueur == id)
			{
				// Construction d'une main a partir des cartes recues
				Hand *hand = new Hand();

				hand->addCard(new Card(static_cast<EType>(typeCard)));
				hand->addCard(new Card(static_cast<EType>(typeCard2)));

				if (!main)
					this->player.getHand()->setHand(*hand);
				else
					this->player.getHand2()->setHand(*hand);
			}
			this->com.sendAck();
			break;

		case 14: // ValidSplit receive
			sscanf(str.c_str(), "%d %d ", &id_message, &num_joueur);
			if (num_joueur == id)
			{
				this->player.newHand();
				this->player.getHand2()->setBet(this->player.getHand()->getBet());
            	this->player.decreaseBalance(this->player.getHand2()->getBet());
			}
			com.sendAck();
			break;

		case 15: // AskAction receive
			sscanf(str.c_str(), "%d %d %d ", &id_message, &num_joueur, &main);
			if (num_joueur == id)
			{
				if (!main)
					this->chooseAction(this->player.getHand(), 0);
				else
					this->chooseAction(this->player.getHand2(), 1);
			}
			break;

        default :
			throw runtime_error("Erreur id message runGame()");
            break;
		}
	}

	this->com.RemoveFiles(id);
}

void UserGame::chooseAction(PlayerHand *myhand, int secHand)
{
	bool spliter = false;
	bool doubler = false;
	bool hit = false;
	bool stand = true;
	char reponse;


	if (this->player.getHand()->isPair() && this->player.getHand2() == NULL
        && this->player.getBalance() >= this->player.getHand()->getBet())
            spliter = true;

	if (this->player.getHand()->numberOfCards() == 2 && this->player.getHand2() == NULL
        && this->player.getBalance() >= this->player.getHand()->getBet())
            doubler = true;

	if (myhand->getValue1() <= 21)
		hit = true;

	/* affichage de l'etat du jeu */
	this->ihm.PrintGameState(this->player, hit, spliter, doubler, stand);

	/* recoit la reponse*/
	reponse = this->ihm.askAction(hit, spliter, doubler, stand, secHand);

	/* valeur permetant de connaitre la main sur laquelle seront appliquées les actions */
	int value;

	if (myhand == this->player.getHand())
		value = 0;
	else
		value = 1;

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


void UserGame::endRound()
{
    this->ihm.PrintEndRound(player);

    if (getPlayer().getHand() != NULL)
        this->getPlayer().setHand(NULL);
    if (getPlayer().getHand2() != NULL)
        this->getPlayer().setHand2(NULL);
}





