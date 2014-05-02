#include "BankGame.h"
#include <algorithm>  // std::random_shuffle()

using namespace std;

// Mises minimale et maximale par d�faut � respectivement 5 et 100
int BankGame::betMin = 5;
int BankGame::betMax = 100;
int BankGame::balancePlayerInit = 2000;

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
	// D�sallocation des cartes restantes dans deck
	this->clearDeck();

	// D�sallocation des joueurs
	for (vector<Player*>::iterator it = this->player.begin(); it != this->player.end(); it++)
	{
		(*it)->~Player();  // Est-ce que �a marche ici ???
		delete *it;
	}
}


void BankGame::burnCards()
{
	if (this->deck.size() < 5)
		throw new exception("impossible de bruler 5 cartes");
	else for (int i = 1; i <= 5; i++)
	{
		delete *(this->deck.end());  // D�sallocation ???
		this->deck.pop_back();  // Supression du pointeur de la liste
	}
}

void BankGame::clearDeck()
{
	// D�sallocation des cartes
	for (vector<Card*>::iterator it = this->deck.begin(); it != this->deck.end(); it++)
	{
		delete *it;  // Est-ce que �a marche ici ???
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
		//this->com.SendCard(/* id joueur, main, carte */);

		// Tirage de la 2nd carte
		c = NULL;
		c = this->hitCard();
		this->player[i]->getHand()->addCard(c);
		//this->com.SendCard(/* id joueur, main, carte */);
	}

	// Tirage de la 1ere carte de la banque
	this->bank.getHand()->addCard(this->hitCard());

	// Tirage de la 2nd carte de la banque
	this->bank.getHand()->addCard(this->hitCard());

}

Card* BankGame::hitCard()
{
	Card *c;
	c = this->deck.back();
	this->deck.pop_back();

	return c;
}

void BankGame::newDeck()
{
	this->clearDeck();
	
	// 24 = 6 paquets * 4 fois la cartes dans un paquet
	// 24*13 = 312
	for (int j = 0; j < 24; j++)
	{
		for (int i = 1; i <= 13; i++)
			this->deck.push_back(new Card((EType)i));
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
