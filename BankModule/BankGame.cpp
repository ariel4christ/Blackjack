#include "BankGame.h"
#include <iostream>
#include <string>
#include <algorithm>  // std::random_shuffle()

using namespace std;

// Mises minimale et maximale par défaut é respectivement 5 et 100
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
	// Désallocation des cartes restantes dans deck
	this->clearDeck();

	// Désallocation des joueurs
	for (vector<Player*>::iterator it = this->player.begin(); it != this->player.end(); it++)
	{
		(*it)->~Player();  // Est-ce que éa marche ici ???
		delete *it;
	}
}



/***** Méthodes privées *****/

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
		delete *(this->deck.end());  // Désallocation ???
		this->deck.pop_back();  // Supression du pointeur de la liste
	}
}

void BankGame::clearDeck()
{
	// Désallocation des cartes
	for (vector<Card*>::iterator it = this->deck.begin(); it != this->deck.end(); it++)
	{
		delete *it;  // Est-ce que éa marche ici ???
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

Card* BankGame::hitCard()
{
	Card *c;
	c = this->deck.back();
	this->deck.pop_back();

	return c;
}

void BankGame::initRound()
{
	this->newPlayer();  // Vérification des nouveaux joueurs


	if (deck.size() <= player.size() * betMax * 2)
		this->newDeck();  // Nouveau deck

	this->com.RoundStart();
	cout << endl << "** Nouveau Tour : attente des mises... **" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		int id = this->player[i]->getId();

		string str = this->com.ReadFile(id);
		int id_message, bet;
		sscanf(str.c_str, "%d %d", &id_message, bet);

		this->player[i]->newHand(bet);  // Nouvelle main
		this->player[i]->decreaseBalance(bet);  // Diminution solde

		this->com.setBet(id, bet);
	}

	this->dealCards();  // Distribution des cartes initiales
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
	// D�termination des blackjack pour chaque joueur
	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getHand()->isBlackjack())  // Le joueur fait blackjack
		{
			player[i]->setBlackjack(true);
			/*** MESSAGE BLACKJACK VERS JOUEUR ***/
		}
	}

	/***** Assurance *****/
	if (bank.getHand()->hasAs())
	{
		cout << endl << "La Banque a un AS" << endl;
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
			for (unsigned int i = 0; i < this->player.size(); i++)
			{
				if (player[i]->hasInsurance())
				{
					bank.decreaseBalance(player[i]->getHand()->getBet() / 2);
					player[i]->increaseBalance(player[i]->getHand()->getBet()*1.5);
					com.setBalance(player[i]->getId(), player[i]->getBalance());
					player[i]->deleteHand();
				}
				else
				{
					player[i]->increaseBalance(player[i]->getHand()->getBet());
				}
			}
		}
	}
	/***** Fin Assurance *****/


	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (player[i]->getBlackjack())  // Le joueur fait blackjack
		{
			if (bank.isBankBlackjack())  // La banque fait aussi blackjack
			{
				player[i]->getHand()->setStand(true);
			}
		}
	}
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
