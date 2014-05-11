#include "BankGame.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>  // std::random_shuffle()
#include <cstdlib>  // std::rand
#include <ctime>  // std::time

using namespace std;

// Mises minimale et maximale par défaut à respectivement 5 et 100
int BankGame::betMin = 5;
int BankGame::betMax = 100;
long BankGame::balancePlayerInit = 2000;

int BankGame::getBetMin()
{
	return BankGame::betMin;
}

void BankGame::setBetMin(int i)
{
	BankGame::betMin = i;
}

int BankGame::getBetMax()
{
	return BankGame::betMax;
}

void BankGame::setBetMax(int i)
{
	BankGame::betMax = i;
}

int BankGame::getBalancePlayerInit()
{
	return BankGame::balancePlayerInit;
}

void BankGame::setBalancePlayerInit(int i)
{
	BankGame::balancePlayerInit = i;
}


BankGame::BankGame(int bankBalance):
	bank(bankBalance)
{
}

BankGame::~BankGame()
{
	// Désallocation des cartes restantes dans deck
	this->clearDeck();

    if (!player.empty())
    {
        // Désallocation des joueurs
        for (vector<Player*>::iterator it = this->player.begin(); it != this->player.end(); it++)
        {
            delete *it;
            *it = NULL;
        }
        player.clear();
	}
	com.CleanFiles();

	cout << endl << "##################################################" << endl;
	cout << endl << "***** FIN DU JEU *****" << endl;
	cout << endl << "##################################################" << endl;
}



/***** Méthodes privées *****/

void BankGame::burnCards()
{
	if (this->deck.size() < 5)
		throw runtime_error("impossible de bruler 5 cartes");
	else for (int i = 1; i <= 5; i++)
	{
		delete *(this->deck.end());
		this->deck.pop_back();  // Supression du pointeur de la liste
	}
}

void BankGame::clearDeck()
{
	// Désallocation des cartes
	for (vector<Card*>::iterator it = this->deck.begin(); it != this->deck.end(); it++)
	{
		delete *it;
	}
	this->deck.clear();
}

void BankGame::dealCards()
{
    cout << endl << "Distribution des cartes..." << endl << endl;
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		Card* c;
		// Tirage de la 1ere carte
		c = this->hitCard();
		this->player[i]->getHand()->addCard(c);
		this->com.SendCard(this->player[i]->getId(), c->getType(), 0);
		ReceiveAck(i);

		// Tirage de la 2nd carte
		c = NULL;
		c = this->hitCard();
		this->player[i]->getHand()->addCard(c);
		this->com.SendCard(this->player[i]->getId(), c->getType(), 0);
		ReceiveAck(i);
	}

	// Tirage de la 1ere carte de la banque
	Card* c;
	c = this->hitCard();
	this->bank.newHand();
	this->bank.getHand()->addCard(c);
	this->com.SendCard(4, c->getType(), 0);  // 4 pour id banque
    ReceiveAck();

	// Tirage de la 2nd carte de la banque
	c = NULL;
	this->bank.setHiddenCard( hitCard() );
	this->bank.getHand()->addCard(new Card(NaN));
	this->com.SendCard(4, NaN, 0);  // 4 pour id banque, 2nd carte est inconnue
    ReceiveAck();
}

void BankGame::endRound(Player *p, int secondHand)
{
	PlayerHand *h;  // Main du joueur
	Hand *bh;  // Main de la banque
	if (secondHand == 0)
		h = p->getHand();
	else h = p->getHand2();
	bh = bank.getHand();

	if (h->getValue1() > 21 && h->getValue2() > 21)  // La main du joueur dépasse 21
	{
		cout << "Le Joueur " << p->getId() << " a perdu !" << endl;
		bank.increaseBalance(h->getBet());

	}
	else if (bh->getValue2() > 21 || h->getValue2() > bh->getValue2())  // La main de la banque dépasse 21 OU la main du joueur est > à celle de la banque
	{
		cout << "Le Joueur " << p->getId() << " a gagné !" << endl;
		bank.decreaseBalance(h->getBet());
		p->increaseBalance(h->getBet() * 2);  // 1*mise de gains + 1*mise prélevée au départ
		com.setBalance(p->getId(), p->getBalance());
		ReceiveAck(p->getId());
	}
	else if (h->getValue2() < bh->getValue2())  // La main du joueur est inferieur à celle de la banque
	{
		cout << "Le Joueur " << p->getId() << " a perdu !" << endl;
		bank.increaseBalance(h->getBet());
	}
	else if (h->getValue2() == bh->getValue2())  // La main du joueur == la main de la banque
	{
		cout << "Le Joueur " << p->getId() << " a fait nul !" << endl;
		p->increaseBalance(h->getBet());  // On rembourse le joueur
		com.setBalance(p->getId(), p->getBalance());
		ReceiveAck(p->getId());
	}

/*
	if (secondHand == 0)
		p->deleteHand(p->getHand());
	else p->deleteHand(p->getHand2());*/
    //delete h;
    //h = NULL;

    cout << endl;
}

Card* BankGame::hitCard()
{
	Card *c;
	c = this->deck.back();
	this->deck.pop_back();

	return c;
}

void BankGame::initRound()
{
	if (deck.size() <= player.size() * betMax * 2)
		this->newDeck();  // Nouveau deck

	this->com.RoundStart();

	cout << endl << "##################################################" << endl;
	cout << endl << "***** NOUVEAU TOUR *****" << endl << "Attente des mises : " << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
        int id = this->player[i]->getId();
		cout << "\t\t" << "Joueur " << player[i]->getId() << " ?" << endl;

		string str = this->com.ReadFile(id);

		player[i]->setBlackjack(false);
		player[i]->setInsurance(false);
		player[i]->setSurrender(false);

		if (player[i]->getHand() != NULL)
            player[i]->setHand(NULL);
        if (player[i]->getHand2() != NULL)
            player[i]->setHand2(NULL);

		int id_message, bet;
		sscanf(str.c_str(), "%d ", &id_message);
		if (id_message == 9)
		{
            sscanf(str.c_str(), "%d %d", &id_message, &bet);
			this->player[i]->newHand(bet);  // Nouvelle main
			this->player[i]->decreaseBalance(bet);  // Diminution solde

			this->com.setBet(id, bet);
			ReceiveAck(i);
		}
		else if (id_message == 4)
		{
			quitePlayer(player[i]);
		}
//		else if (id_message == 10) {}
		else throw runtime_error("erreur lors de la détermination de la mise");
	}

	this->dealCards();  // Distribution des cartes initiales
	cout << "##################################################" << endl;
	this->interface.printGameState(getPlayers(), getBank());
}

int BankGame::insurance()
{
	cout << endl << "##################################################" << endl;
	cout << "Demande d'assurance" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (!player[i]->getBlackjack())  // Le joueur ne fait pas blackjack
		{
			cout << "\t\t" << "Joueur " << player[i]->getId() << " ?..." << endl;

			int id = this->player[i]->getId();
			this->com.AskInsurance(id);
			string str = com.ReadFile(id);
			int id_message, idPlayer;
			sscanf(str.c_str(), "%d ", &id_message);

			switch (id_message)
			{
			case 0:
				break;
			case 4:
                sscanf(str.c_str(), "%d %d", &id_message, &idPlayer);
                if (idPlayer == id)
                    quitePlayer(player[i]);
				break;
			case 1:
				player[i]->decreaseBalance(player[i]->getHand()->getBet() / 2);
				bank.increaseBalance(player[i]->getHand()->getBet() / 2);
				com.setBalance(id, player[i]->getBalance());
				ReceiveAck(i);
				break;
			default:
				throw runtime_error("Message assurance incorrect !");
				break;
			}
		}
	}

	cout << "##################################################" << endl;
	interface.printGameState(getPlayers(), getBank());
	cout << endl << "##################################################" << endl;

	if (bank.isBankBlackjack())  // La banque fait blackjack
	{
		bank.getHand()->getCard(1)->setType(bank.getHiddenCard()->getType());
		cout << "La Banque fait Blackjack" << endl << "*** Les assurances payent ! ***" << endl;
		interface.printGameState(getPlayers(), getBank());

		for (unsigned int i = 0; i < this->player.size(); i++)
		{
			if (player[i]->hasInsurance())  // Le joueur a pris une assurance
			{
				bank.decreaseBalance(player[i]->getHand()->getBet() / 2);  // Diminution solde banque
				player[i]->increaseBalance( (int) floor(player[i]->getHand()->getBet()*1.5) );  // Augmentation solde joueur
				com.setBalance(player[i]->getId(), player[i]->getBalance());  // Mise à jour solde exe joueur
				ReceiveAck(i);
			}
			else if (player[i]->getBlackjack())  // Le joueur a aussi fait blackjack (et donc pas d'assurance demandée)
			{
				player[i]->increaseBalance(player[i]->getHand()->getBet());  // Augmentaion solde joueur : on le rembourse
				com.setBalance(player[i]->getId(), player[i]->getBalance());  // Mise à jour solde exe joueur
				ReceiveAck(i);

			}

//			player[i]->deleteHand(player[i]->getHand());  // Desallocation main joueur
            player[i]->setHand(NULL);

		}

		com.EndRound();
		bank.deleteHand();
		delete bank.getHiddenCard();
		bank.setHiddenCard(NULL);

		cout << "LE TOUR EST FINI" << endl;
		cout << endl << "##################################################" << endl;

		return 0;  // Le tour est fini
	}

	else
	{
		cout << "La Banque ne fait pas Blackjack" << endl << "Les assurance sont perdues !" << endl;
		cout << "##################################################" << endl;

		return 1;  // Le tour continu
	}
}

void BankGame::newDeck()
{
	this->clearDeck();

	// 24 = 6 paquets * 4 fois la cartes dans un paquet
	// 24*13 = 312
	for (int j = 0; j < 24; j++)
	{
		for (int i = 1; i <= 13; i++)
			this->deck.push_back( new Card((EType) i) );
	}
}

void BankGame::newGame()
{
	srand((unsigned) time(0));

	this->newDeck();
	this->shuffleDeck();
	this->burnCards();

	this->com.CleanFiles();

	cout << endl << "##################################################" << endl;
	cout << "EN ATTENTE DE JOUEURS" << endl;
	cout << endl << "##################################################" << endl;
	while (this->com.CheckFiles() == 0);  // Boucle tant qu'il n'y a pas de joueur

	newPlayer();
}

void BankGame::newPlayer()
{
	static int b = 0;
	int c = this->com.CheckFiles();
	if (b != c)
	{
		for (int i = 0; i < 4; i++)
		{
			if ( (c & (1 << i)) && (!(b & (1 << i))) )
			{
				this->player.push_back(new Player(i, balancePlayerInit));

				string str = com.ReadFile(i);
				int id_message;
				sscanf(str.c_str(), "%d", &id_message);
				if (id_message != 6)
					throw runtime_error("Message d'entee joueur incorrect");
				else
				{
					com.PlayerEntered(i);
					ReceiveAck(i);

					com.setBalance(i, balancePlayerInit);
                    ReceiveAck(i);
				}
			}
		}
	}
	b = c;
}

int BankGame::playerAction(Player *p, int secondHand)
{
    cout << "Demande d'action au Joueur " << p->getId() << " \tMain " << secondHand + 1 << endl;
	int id = p->getId();

	com.AskAction(id, secondHand);

	string str = com.ReadFile(id);
	int id_message;
	int secHand;
	sscanf(str.c_str(), "%d ", &id_message);

	PlayerHand *h;
	switch (id_message)
	{
	case 1:  // Split
        sscanf(str.c_str(), "%d %d", &id_message, &secHand);
        if (secondHand != secHand)
            throw runtime_error("Erreur de main dans le choix de l'action");

		if (p->getHand()->isPair() && p->getHand2() == NULL && secHand == 0)
		{
			com.validSplit(id);

			p->newHand();
			p->getHand2()->setBet(p->getHand()->getBet());
			p->decreaseBalance(p->getHand2()->getBet());
			p->getHand()->trandferSecondCard(p->getHand2());

			Card *c = hitCard();
			p->getHand()->addCard(c);
			c = hitCard();
			p->getHand2()->addCard(c);

			com.setHand(id, *p->getHand(), 0);
			com.setHand(id, *p->getHand2(), 1);
		}
		else
			throw runtime_error("Split non autorisé");
		break;

	case 2:  // Stand
        sscanf(str.c_str(), "%d %d", &id_message, &secHand);
        if (secondHand != secHand)
            throw runtime_error("Erreur de main dans le choix de l'action");

		if (secHand == 0)
			h = p->getHand();
		else h = p->getHand2();

		if (h != NULL)
		{
			h->setStand(true);
			com.validStand(id, secHand);
		}
		break;

	case 3:  // Surrender
        sscanf(str.c_str(), "%d %d", &id_message, &secHand);
        if (secondHand != secHand)
            throw runtime_error("Erreur de main dans le choix de l'action");

		if (secHand == 0)
			h = p->getHand();
		else h = p->getHand2();

		if (!h->getStand() && h->getValue1() <= 21)
		{
			bank.increaseBalance(h->getBet() / 2);
			p->Surrender(h);
			com.validSurrender(id);

			if (secHand == 0)
                p->setHand(NULL);
            else p->setHand2(NULL);

			if (p->getHand() == NULL && p->getHand2() == NULL)
				p->setSurrender(true);
		}
		break;

	case 4:  // Quit
		if(quitePlayer(p) == 0)
            return 0;
		break;

	case 7:  // Double
		if (p->getHand()->numberOfCards() == 2 && p->getHand2() == NULL)
		{
			Card* c = hitCard();
			p->getHand()->addCard(c);
			com.SendCard(id, c->getType(), 0);

			int bet = p->getHand()->getBet();
			p->decreaseBalance(bet);
			p->getHand()->setBet(2*bet);
			com.setBet( id, 2 * bet );  // Mise à jour mise
			ReceiveAck(id);
			com.setBalance(id, p->getBalance());  // Mise à jour solde
			ReceiveAck(id);
			// La joueur stand
			p->getHand()->setStand(true);
			com.validStand(id, secHand);
		}
		else
			throw runtime_error("Double impossible");
		break;

	case 8:  // Hit
        sscanf(str.c_str(), "%d %d", &id_message, &secHand);
        if (secondHand != secHand)
            throw runtime_error("Erreur de main dans le choix de l'action");

		if (secHand == 0)
			h = p->getHand();
		else if (p->getHand2() != NULL)
			h = p->getHand2();
		else
			throw runtime_error("Le joueur n'a pas de deuxième main");

		if (h->getValue1() <= 21)
		{
			Card *c = hitCard();
			h->addCard(c);
			com.SendCard(id, c->getType(), secHand);
			ReceiveAck(id);
		}
		break;

	default:
		throw runtime_error("Action non autorisée ou non définie");
		break;
	}

	interface.printGameState(getPlayers(), getBank());
	return 1;
}

int BankGame::quitePlayer(Player *p)
{
	int id = p->getId();
	com.HasQuit(id);

	delete p;
	p = NULL;

    cout << player.size() << endl;
    if (this->player.size() > 1)
    {
        // Suppression du joueur de la liste des joueurs
        vector<Player*> tmp;
        for (unsigned int i = 0 ; i < player.size() ; i++)
        {
            if (player[i] != NULL)  // Si le pointeur != NULL alors on le stock dans le vecteur tmp
                tmp.push_back(player[i]);
        }
        this->player = tmp;  // Mise à jour de player, le joueur qui a quitté le jeu n'est plus dans le vecteur
        return 1;
    }

    // Il n'y a qu'un joueur qui vient de quitter le jeu : FIN DU JEU
	else
	{
        this->player.clear();
		return 0;
    }

}

int BankGame::runGame()
{
    int i = 1;
	this->newGame();
	this->newPlayer();  // Vérification des nouveaux joueurs
	while (i && !player.empty())
	{
		initRound();
		i = runRound();
		newPlayer();
	}
		return 0;
}

int BankGame::runRound()
{
	// Détermination des blackjack pour chaque joueur
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getHand()->isBlackjack())  // Le joueur fait blackjack
			player[i]->setBlackjack(true);
	}

	/***** Assurance *****/
	if (bank.getHand()->hasAs())
	{
		cout << endl << "##################################################" << endl;
		cout << "La Banque a un AS" << endl;
		cout << "##################################################" << endl;
		if (this->insurance() == 0)
			return 1; // Le tour est fini
	}

	/***** Traitement du cas "un joueur fait blackjack" *****/
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getBlackjack())  // Le joueur fait blackjack
		{
			if (bank.isBankBlackjack())  // La banque fait aussi blackjack
			{
				bank.getHand()->getCard(1)->setType(bank.getHiddenCard()->getType());
				cout << endl << "##################################################" << endl;
				cout << "La Banque fait Blackjack" << endl;
				cout << "##################################################" << endl;
				interface.printGameState(getPlayers(), getBank());
				player[i]->getHand()->setStand(true);  // Le joueur stand
			}

			else  // La banque ne fait pas blackjack
			{
				cout << endl << "##################################################" << endl;
				cout << "La Banque ne fait pas Blackjack" << endl;
				cout << "##################################################" << endl;
				bank.decreaseBalance( (int) floor(player[i]->getHand()->getBet()*1.5) );
				player[i]->increaseBalance((int) floor(player[i]->getHand()->getBet()*2.5) );  // Augmentation du solde : 1,5* mise de gains + 1*mise d�j� pr�lev�e
				com.setBalance(player[i]->getId(), player[i]->getBalance());
                ReceiveAck(i);
				player[i]->deleteHand(player[i]->getHand());
				player[i]->setHand(NULL);
			}
		}
	}
	/***** Fin cas "un joueur fait blackjack" *****/

	/***** Demandes d'actions aux joueurs *****/
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (!this->player[i]->getBlackjack())  // Le joueur n'a pas fait blackjack
		{
			// Boucle d'actions sur la main 1
			while (!player[i]->getHand()->getStand() && !player[i]->getSurrender() && player[i]->getHand() != NULL)
			{
				if (playerAction(player[i], 0) == 0)
                    return 0; // Fin du jeu

				if (player[i]->getHand()->getValue1() >= 21)  // Si la valeur basse de la main est >= 21, le joueur est oblig� de s'arreter.
				{
					player[i]->getHand()->setStand(true);
					com.validStand(player[i]->getId(), 0);
					interface.printGameState(getPlayers(), getBank());
				}
			}

			// Boucle d'actions sur la main 2
			while (player[i]->getHand2() != NULL && !player[i]->getHand2()->getStand() && !player[i]->getSurrender())
			{
				playerAction(player[i], 1);
				if (player[i]->getHand2()->getValue1() >= 21)  // Si la valeur basse de la main est >= 21, le joueur est obligé de s'arreter.
				{
					player[i]->getHand2()->setStand(true);
					com.validStand(player[i]->getId(), 1);
					interface.printGameState(getPlayers(), getBank());
				}
			}
		}
	}
	/***** Fin des demandes d'actions aux joueurs *****/


	/***** Tirage des cartes de la banque *****/
	Card *c = bank.getHand()->getCard(1);
	c->setType(bank.getHiddenCard()->getType());  // On met à jour la carte cachée avec son vrai type
	delete bank.getHiddenCard();  // Désallocation de la carte cachée
	bank.setHiddenCard(NULL);
	com.SendCard(4, c->getType(), 0);
	interface.printGameState(getPlayers(), getBank());

	cout << endl << "##################################################" << endl;
	cout << "La banque tire à 16 et s'arrete à 17." << endl;
	cout << "##################################################" << endl;

	while (bank.getHand()->getValue2() < 17 || bank.getHand()->getValue1() < 17)
	{
		c = NULL;
		c = hitCard();
		bank.getHand()->addCard(c);
		com.SendCard(4, c->getType(), 0);
	}

	interface.printGameState(getPlayers(), getBank());
	/***** Fin du tirage des cartes de la banque *****/

	/***** Fin du tour : verif des mises *****/

    cout << endl << "##################################################" << endl << endl;
	cout << "FIN DU TOUR : RESULTATS" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getHand() != NULL)
			endRound(player[i], 0);
		if (player[i]->getHand2() != NULL)
			endRound(player[i], 1);

        if (player[i]->getBalance() < getBetMin())
        {
            cout << endl << "Votre solde est insuffisant pour continuer Joueur" << i;
            cout << ". Vous avez perdu!" << endl;
            this->quitePlayer(player[i]);
        }
	}

    cout << "##################################################" << endl << endl;


	com.EndRound();

    // Désallocation mains joueurs
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
        ReceiveAck(i);
        if (player[i]->getHand() != NULL)
            //player[i]->deleteHand(player[i]->getHand());
            player[i]->setHand(NULL);

        if (player[i]->getHand2() != NULL)
            //player[i]->deleteHand(player[i]->getHand2());
            player[i]->setHand2(NULL);
	}

	// Désallocation main banque
	if (bank.getHand() != NULL)
	{
        bank.deleteHand();
    }

	return 1;
}

void BankGame::shuffleDeck()
{
	random_shuffle(this->deck.begin(), this->deck.end());
}

void BankGame::ReceiveAck()
{
    for (unsigned int i = 0 ; i < this->player.size() ; ++i)
    {
        string str = com.ReadFile(i);  // Accussé de réception
        int id_message;
        sscanf(str.c_str(), "%d", &id_message);
        if (id_message != 10)
        	throw runtime_error("Accusée de reception non reçu");
    }
}

void BankGame::ReceiveAck(int i)
{
    string str = com.ReadFile(i);  // Accussé de réception
    int id_message;
    sscanf(str.c_str(), "%d", &id_message);
    if (id_message != 10)
       throw runtime_error("Accusée de reception non reçu");
}
