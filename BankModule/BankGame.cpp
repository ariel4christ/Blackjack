#include "BankGame.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>  // std::random_shuffle()

using namespace std;

// Mises minimale et maximale par dÃ©faut Ã© respectivement 5 et 100
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
	bank(Bank::Bank(bankBalance))
{
	this->newDeck();
}

BankGame::~BankGame()
{
	// DÃ©sallocation des cartes restantes dans deck
	this->clearDeck();

	// DÃ©sallocation des joueurs
	for (vector<Player*>::iterator it = this->player.begin(); it != this->player.end(); it++)
	{
		(*it)->~Player();  // Est-ce que Ã©a marche ici ???
		delete *it;
	}
}



/***** MÃ©thodes privÃ©es *****/

void BankGame::newPlayer()
{
	int c = this->com.CheckFiles();
	if (c != 0)
	{

	}
}

void BankGame::burnCards()
{
	if (this->deck.size() < 5)
		throw runtime_error("impossible de bruler 5 cartes");
	else for (int i = 1; i <= 5; i++)
	{
		delete *(this->deck.end());  // DÃ©sallocation ???
		this->deck.pop_back();  // Supression du pointeur de la liste
	}
}

void BankGame::clearDeck()
{
	// DÃ©sallocation des cartes
	for (vector<Card*>::iterator it = this->deck.begin(); it != this->deck.end(); it++)
	{
		delete *it;  // Est-ce que Ã©a marche ici ???
	}
	this->deck.clear();
}

void BankGame::dealCards()
{
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		Card* c;
		// Tirage de la 1ere carte
		c = this->hitCard();
		this->player[i]->getHand()->addCard(c);
		this->com.SendCard(this->player[i]->getId(), c->getType(), 0);

		// Tirage de la 2nd carte
		c = NULL;
		c = this->hitCard();
		this->player[i]->getHand()->addCard(c);
		this->com.SendCard(this->player[i]->getId(), c->getType(), 0);
	}

	// Tirage de la 1ere carte de la banque
	Card* c = this->hitCard();
	this->bank.getHand()->addCard(c);
	this->com.SendCard(4, c->getType(), 0);  // 4 pour id banque

	// Tirage de la 2nd carte de la banque
	c = NULL;
	this->bank.setHiddenCard( hitCard() );
	this->bank.getHand()->addCard(new Card(NaN));
	this->com.SendCard(4, NaN, 0);  // 4 pour id banque, 2nd carte est inconnue
	
}

void BankGame::endRound(Player *p, int secondHand)
{
	PlayerHand *h;  // Main du joueur
	Hand *bh;  // Main de la banque
	if (secondHand == 0)
		h = p->getHand();
	else h = p->getHand2();
	bh = bank.getHand();

	if (h->getValue1() > 21 && h->getValue2 > 21)  // La main du joueur dépasse 21
	{
		bank.increaseBalance(h->getBet());
		h->deleteHand();
		delete h;
	}
	else if (bh->getValue2() > 21 || h->getValue2() > bh->getValue2())  // La main de la banque dépasse 21 OU la main du joueur est > à celle de la banque
	{
		bank.decreaseBalance(h->getBet());
		p->increaseBalance(h->getBet() * 2);  // 1*mise de gains + 1*mise prélevée au départ
		com.setBalance(p->getId(), p->getBalance());
	}
	else if (h->getValue2() < bh->getValue2())  // La main du joueur est inferieur à celle de la banque
	{
		bank.increaseBalance(h->getBet());
	}
	else if (h->getValue2() == bh->getValue2())  // La main du joueur == la main de la banque
	{
		p->increaseBalance(h->getBet());  // On rembourse le joueur
		com.setBalance(p->getId(), p->getBalance());
	}
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
	this->newPlayer();  // VÃ©rification des nouveaux joueurs


	if (deck.size() <= player.size() * betMax * 2)
		this->newDeck();  // Nouveau deck

	this->com.RoundStart();
	cout << endl << "** Nouveau Tour : attente des mises... **" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		int id = this->player[i]->getId();

		string str = this->com.ReadFile(id);
		int id_message, bet;
		sscanf(str.c_str(), "%d %d", &id_message, &bet);

		this->player[i]->newHand(bet);  // Nouvelle main
		this->player[i]->decreaseBalance(bet);  // Diminution solde

		this->com.setBet(id, bet);
	}

	this->dealCards();  // Distribution des cartes initiales
}

int BankGame::insurance()
{
	cout << "Demande d'assurance" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (!player[i]->getBlackjack())  // Le joueur ne fait pas blackjack
		{
			int id = this->player[i]->getId();
			this->com.AskInsurance(id);
			string str = com.ReadFile(id);
			int response = stoi(str);

			switch (response)
			{
			case 0:
				break;
			case 4:
				quitePlayer(player[i]);
				break;
			case 1:
				player[i]->decreaseBalance(player[i]->getHand()->getBet() / 2);
				bank.increaseBalance(player[i]->getHand()->getBet() / 2);
				com.setBalance(id, player[i]->getBalance());
				break;
			default:
				throw runtime_error("Message incorrect !");
				break;
			}
		}
	}

	interface.printGameState();

	if (bank.isBankBlackjack())  // La banque fait blackjack
	{
		bank.getHand()->getCard(1)->setType(bank.getHiddenCard()->getType());
		cout << "*** La Banque fait Blackjack ***" << endl;
		interface.printGameState();

		for (unsigned int i = 0; i < this->player.size(); i++)
		{
			if (player[i]->hasInsurance())  // Le joueur a pris une assurance
			{
				bank.decreaseBalance(player[i]->getHand()->getBet() / 2);  // Diminution solde banque
				player[i]->increaseBalance( (int) floor(player[i]->getHand()->getBet()*1.5) );  // Augmentation solde joueur
				com.setBalance(player[i]->getId(), player[i]->getBalance());  // Mise à jour solde exe joueur
				player[i]->deleteHand(player[i]->getHand());  // Desallocation main joueur
			}
			else if (player[i]->getBlackjack())  // Le joueur a aussi fait blackjack et donc pas d'assurance demandée
			{
				player[i]->increaseBalance(player[i]->getHand()->getBet());  // Augmentaion solde joueur
				com.setBalance(player[i]->getId(), player[i]->getBalance());  // Mise à jour solde exe joueur
				player[i]->deleteHand(player[i]->getHand());  // Desallocation main joueur
			}
			else
				player[i]->deleteHand(player[i]->getHand());  // Les autres cas, on désalloue la main directement

			com.EndRound();
		}

		bank.deleteHand();
		delete bank.getHiddenCard();

		return 0;  // Le tour est fini
	}

	else
	{
		cout << "*** La Banque ne fait pas Blackjack ***" << endl;
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
	this->newDeck();
	this->shuffleDeck();
	this->burnCards();

	this->com.CleanFiles();

	while (this->com.CheckFiles() == 0)
		interface.printMessage(/* "En attente de joueurs" */);
}

void BankGame::playerAction(Player *p, int secondHand)
{
	int id = p->getId();

	com.AskAction(id, secondHand);
		
	string str = com.ReadFile(id);
	int id_message;
	int secHand;
	sscanf(str.c_str(), "%d %d", &id_message, &secHand);

	if (secondHand != secHand)
		throw runtime_error("Erreur de main dans le choix de l'action");

	switch (id_message)
	{
	case 1:  // Split
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
		PlayerHand *h;
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
		PlayerHand *h;
		if (secHand == 0)
			h = p->getHand();
		else h = p->getHand2();

		if (!h->getStand() && h->getValue1() <= 21)
		{
			bank.increaseBalance(h->getBet() / 2);
			p->Surrender(h);
			com.validSurrender(id);
			if (p->getHand() == NULL && p->getHand2() == NULL)
				p->setSurrender(true);
		}
		break;

	case 4:  // Quit
		p->~Player();
		com.HasQuit(id);
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
			com.setBalance(id, p->getBalance());  // Mise à jour solde
			// La joueur stand
			h->setStand(true);
			com.validStand(id, secHand);
		}
		else 
			throw runtime_error("Double impossible");
		break;

	case 8:  // Hit
		PlayerHand *h;
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
		}
		break;

	default:
		throw runtime_error("Action non autorisée");
		break;
	}

	interface.printGameState();
}

void BankGame::quitePlayer(Player *p)
{
	int id = p->getId();
	p->~Player();
	delete p;
	com.HasQuit(id);

	// Il n'y a plus de joueur : FIN DU JEU
	if (this->player.empty())
		this->~BankGame();
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
		cout << endl << "La Banque a un AS" << endl;
		if (this->insurance() == 0)
			return 0; // Le tour est fini
	}
	
	/***** Traitement du cas "un joueur fait blackjack" *****/
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getBlackjack())  // Le joueur fait blackjack
		{
			if (bank.isBankBlackjack())  // La banque fait aussi blackjack
			{
				bank.getHand()->getCard(1)->setType(bank.getHiddenCard()->getType());
				cout << "*** La Banque fait Blackjack ***" << endl;
				interface.printGameState();
				player[i]->getHand()->setStand(true);  // Le joueur stand
			}

			else  // La banque ne fait pas blackjack
			{
				cout << "*** La Banque ne fait pas Blackjack ***" << endl;
				bank.decreaseBalance( (int) floor(player[i]->getHand()->getBet()*1.5) );
				player[i]->increaseBalance((int) floor(player[i]->getHand()->getBet()*2.5) );  // Augmentation du solde : 1,5* mise de gains + 1*mise déjà prélevée
				com.setBalance(player[i]->getId(), player[i]->getBalance());

				player[i]->getHand()->deleteHand();
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
				playerAction(player[i], 0);
				if (player[i]->getHand()->getValue1() >= 21)  // Si la valeur basse de la main est >= 21, le joueur est obligé de s'arreter.
				{
					player[i]->getHand()->setStand(true);
					com.validStand(player[i]->getId(), 0);
					interface.printGameState();
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
					interface.printGameState();
				}
			}
		}
	}
	/***** Fin des demandes d'actions aux joueurs *****/


	/***** Tirage des cartes de la banque *****/
	while (bank.getHand()->getValue2 < 17 || bank.getHand()->getValue1 < 17)
	{
		Card* c = hitCard();
		bank.getHand()->addCard(c);
		com.SendCard(4, c->getType(), 0);
	}
	/***** Fin du tirage des cartes de la banque *****/

	/***** Fin du tour : verif des mises *****/
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getHand() != NULL)
			endRound(player[i], 0);
		if (player[i]->getHand2() != NULL)
			endRound(player[i], 1);
	}
	com.EndRound();

	return 0;
}

void BankGame::shuffleDeck()
{
	/*
	!!! A METTRE AU DEBUT DU MAIN DE L'EXECUTABLE BANQUE !!!
	#include <cstdlib>  // std::rand
	#include <ctime>  // std::time
	srand((unsigned) time(0));
	*/
	random_shuffle(this->deck.begin(), this->deck.end());
}
