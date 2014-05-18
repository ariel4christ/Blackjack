/**
 * BankGame.cpp
 * @author Christophe HUBERT
 */

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

long BankGame::getBalancePlayerInit()
{
	return BankGame::balancePlayerInit;
}

void BankGame::setBalancePlayerInit(int i)
{
	BankGame::balancePlayerInit = i;
}


BankGame::BankGame(long bankInit):
	bank(bankInit)
{
}

BankGame::BankGame(int min, int max, long playerInit, long bankInit) :
    bank(bankInit)
{
    BankGame::setBetMin(min);
    BankGame::setBetMax(max);
    BankGame::setBalancePlayerInit(playerInit);
}

BankGame::~BankGame()
{
	// Désallocation des cartes restantes dans deck
	this->clearDeck();

    if (bank.getHand() != 0)
        bank.setHand(NULL);
    if (bank.getHiddenCard() != NULL)
        bank.setHiddenCard(NULL);

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
	BankInterface::center_output("******* FIN DU JEU *******", 50);
	cout << endl << "##################################################" << endl << endl;
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
		this->com.SendCard(this->player[i]->getId(), c->getType(), 0, player);
		com.ReceiveAck(this->player);

		// Tirage de la 2nd carte
		c = NULL;
		c = this->hitCard();
		this->player[i]->getHand()->addCard(c);
		this->com.SendCard(this->player[i]->getId(), c->getType(), 0, player);
		com.ReceiveAck(this->player);
	}

	// Tirage de la 1ere carte de la banque
	Card* c;
	c = this->hitCard();
	this->bank.newHand();
	this->bank.getHand()->addCard(c);
	this->com.SendCard(4, c->getType(), 0, player);  // 4 pour id banque
    com.ReceiveAck(this->player);

	// Tirage de la 2nd carte de la banque
	c = NULL;
	this->bank.setHiddenCard( hitCard() );
	this->bank.getHand()->addCard(new Card(NaN));
	this->com.SendCard(4, NaN, 0, player);  // 4 pour id banque, 2nd carte est inconnue
    com.ReceiveAck(this->player);
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
		cout << "Joueur " << p->getId() << " a perdu." << endl;
		bank.increaseBalance(h->getBet());

	}
	else if (bh->getValue2() > 21 || h->getValue2() > bh->getValue2())  // La main de la banque dépasse 21 OU la main du joueur est > à celle de la banque
	{
		cout << "Joueur " << p->getId() << " a gagné !" << endl;
		bank.decreaseBalance(h->getBet());
		p->increaseBalance(h->getBet() * 2);  // 1*mise de gains + 1*mise prélevée au départ
		com.setBalance(p->getId(), p->getBalance());
		com.ReceiveAck(p->getId());
	}
	else if (h->getValue2() < bh->getValue2())  // La main du joueur est inferieur à celle de la banque
	{
		cout << "Joueur " << p->getId() << " a perdu." << endl;
		bank.increaseBalance(h->getBet());
	}
	else if (h->getValue2() == bh->getValue2())  // La main du joueur == la main de la banque
	{
		cout << "Le Joueur " << p->getId() << " a fait nul." << endl;
		p->increaseBalance(h->getBet());  // On rembourse le joueur
		com.setBalance(p->getId(), p->getBalance());
		com.ReceiveAck(p->getId());
	}
}

Card* BankGame::hitCard()
{
	Card *c;
	c = this->deck.back();
	this->deck.pop_back();

	return c;
}

int BankGame::initRound()
{
    if (bank.getBalance() < 2 * betMax * player.size())
    {
        for (unsigned int i = 0 ; i < this->player.size() ; ++i)
            quitePlayer(player[i]);

        cout << endl << "##################################################" << endl << endl;
        BankInterface::center_output("~~~ La Banque n'a plus assez d'argent pour continuer ~~~", 50);
        BankInterface::center_output("~~~ Le Casino est obligé de fermer :( ~~~", 50);
        cout << endl << "##################################################" << endl << endl;

        return 0;
    }

	if (deck.size() <= (player.size() + 1) * 22)
	{
		this->newDeck();  // Nouveau deck
		this->shuffleDeck();
		this->burnCards();
    }

	cout << endl << "##################################################" << endl;
	BankInterface::center_output("***** NOUVEAU TOUR *****", 50);
	cout << endl << "~ Attente des mises : " << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		int id = this->player[i]->getId();
		this->com.RoundStart(id);
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
			com.ReceiveAck(id);
		}
		else if (id_message == 4)
		{
			if(quitePlayer(player[i]) == 0)
                return 0;  // Le jeu est fini car il n'y a plus de joueur
            else i--;
		}
		else throw runtime_error("erreur lors de la détermination de la mise");
	}

	this->dealCards();  // Distribution des cartes initiales
	cout << "##################################################" << endl;
	this->interface.printGameState(getPlayers(), getBank());

	return 1;
}

int BankGame::insurance()
{
	cout << endl << "##################################################" << endl;
	cout << "Demande d'assurance" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
		if (!player[i]->getBlackjack())  // Le joueur ne fait pas blackjack
		{
			cout << "\t\t" << "Joueur " << player[i]->getId() << " ?" << endl;

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
                {
                    if (quitePlayer(player[i]) == 0)
                    {
                        cout << endl << "##################################################" << endl;
                        return 0;  // Le jeu est fini car il n'y a plus de joueur
                    }
                }
				break;

			case 1:
				player[i]->decreaseBalance(player[i]->getHand()->getBet() / 2);
				bank.increaseBalance(player[i]->getHand()->getBet() / 2);
				com.setBalance(id, player[i]->getBalance());
				com.ReceiveAck(id);
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
		cout << "~ La Banque fait Blackjack" << endl << "*** Les assurances payent ! ***" << endl;
		interface.printGameState(getPlayers(), getBank());

		for (unsigned int i = 0; i < this->player.size(); i++)
		{
            int id = player[i]->getId();
			if (player[i]->hasInsurance())  // Le joueur a pris une assurance
			{
				bank.decreaseBalance(player[i]->getHand()->getBet() / 2);  // Diminution solde banque
				player[i]->increaseBalance( (int) floor(player[i]->getHand()->getBet()*1.5) );  // Augmentation solde joueur
				com.setBalance(id, player[i]->getBalance());  // Mise à jour solde exe joueur
				com.ReceiveAck(id);
			}
			else if (player[i]->getBlackjack())  // Le joueur a aussi fait blackjack (et donc pas d'assurance demandée)
			{
				player[i]->increaseBalance(player[i]->getHand()->getBet());  // Augmentaion solde joueur : on le rembourse
				com.setBalance(id, player[i]->getBalance());  // Mise à jour solde exe joueur
				com.ReceiveAck(id);

			}

            player[i]->setHand(NULL);

		}

		com.EndRound(player);
		com.ReceiveAck(this->player);
		bank.deleteHand();
		delete bank.getHiddenCard();
		bank.setHiddenCard(NULL);

		cout << "LE TOUR EST FINI" << endl;
		cout << endl << "##################################################" << endl;

		return 0;  // Le tour est fini
	}

	else
	{
		cout << "~ La Banque ne fait pas Blackjack" << endl << "*** Les assurance sont perdues ! ***" << endl;
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
	srand(time(NULL));

	this->newDeck();
	this->shuffleDeck();
	this->burnCards();

	system("clear");
    cout << endl << "##################################################" << endl;
	BankInterface::center_output("******* BLACKJACK *******", 50); cout << endl;
	BankInterface::center_output("Bienvenue", 50);
	cout << endl << "##################################################" << endl;

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
					com.PlayerEntered(i, player);
					com.ReceiveAck(this->player);

					com.setBalance(i, balancePlayerInit);
                    com.ReceiveAck(i);
				}
			}
		}
	}

	b = c;
}

int BankGame::playerAction(Player *p, int secondHand)
{
    cout << "> Demande d'action au Joueur " << p->getId() << " pour sa main " << secondHand + 1 << endl;
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
            com.ReceiveAck(id);

            p->newHand();
            p->getHand2()->setBet(p->getHand()->getBet());
            p->decreaseBalance(p->getHand2()->getBet());
            p->getHand()->trandferSecondCard(p->getHand2());

            Card *c = hitCard();
            p->getHand()->addCard(c);
            c = hitCard();
            p->getHand2()->addCard(c);

            com.setHand(id, *p->getHand(), 0, this->player);
            com.ReceiveAck(this->player);
            com.setHand(id, *p->getHand2(), 1, this->player);
            com.ReceiveAck(this->player);
        }
        else throw runtime_error("Split non autorisé");
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
            com.ReceiveAck(id);
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
			com.ReceiveAck(id);

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
        else return -1;
		break;

	case 7:  // Double
		if (p->getHand()->numberOfCards() == 2 && p->getHand2() == NULL)
		{
			Card* c = hitCard();
			p->getHand()->addCard(c);
			com.SendCard(id, c->getType(), 0, this->player);  // Envoie de la carte
            com.ReceiveAck(this->player);

			int bet = p->getHand()->getBet();
			p->decreaseBalance(bet);
			p->getHand()->setBet(2*bet);
			com.setBet(id, 2 * bet);  // Mise à jour mise
			com.ReceiveAck(id);
			com.setBalance(id, p->getBalance());  // Mise à jour solde
			com.ReceiveAck(id);

			// Le joueur stand obligatoirement
			p->getHand()->setStand(true);
			com.validStand(id, 0);
			com.ReceiveAck(id);
		}
		else throw runtime_error("Double impossible");
		break;

	case 8:  // Hit
        sscanf(str.c_str(), "%d %d", &id_message, &secHand);
        if (secondHand != secHand)
            throw runtime_error("Erreur de main dans le choix de l'action");

		if (secHand == 0)
			h = p->getHand();
		else if (p->getHand2() != NULL)
			h = p->getHand2();
		else throw runtime_error("Le joueur n'a pas de deuxième main");

		if (h->getValue1() <= 21)
		{
			Card *c = hitCard();
			h->addCard(c);
			com.SendCard(id, c->getType(), secHand, this->player);
			com.ReceiveAck(this->player);
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
	com.HasQuit(id, this->player);
	com.ReceiveAck(this->player);

	if (p->getHand() != NULL)
            p->setHand(NULL);
	if (p->getHand2() != NULL)
            p->setHand2(NULL);

    for (unsigned int i = 0 ; i < this->player.size() ; i++)
    {
        if (this->player[i] == p)
        {
            delete this->player[i];
            this->player[i] = NULL;
        }
    }

    cout << "~~~~~ Le Joueur " << id << " a quitté le jeu ! ~~~~~" << endl << endl;

	if (this->player.size() > 1)
	{
        // Suppression du joueur de la liste des joueurs
        vector<Player*> tmp;
		for (unsigned int i = 0 ; i < this->player.size() ; i++)
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
	this->newGame();
	this->newPlayer();  // Vérification des nouveaux joueurs
	while (!player.empty())
	{
		if (initRound() == 0) return 0;
		if (runRound() == 0) return 0;
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
		cout << "~ La Banque a un AS" << endl;
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
				interface.printGameState(getPlayers(), getBank());
				player[i]->getHand()->setStand(true);  // Le joueur stand
			}

			else  // La banque ne fait pas blackjack
			{
				bank.decreaseBalance( (int) floor(player[i]->getHand()->getBet()*1.5) );
				player[i]->increaseBalance((int) floor(player[i]->getHand()->getBet()*2.5) );  // Augmentation du solde : 1,5* mise de gains + 1*mise d�j� pr�lev�e
				com.setBalance(player[i]->getId(), player[i]->getBalance());
                com.ReceiveAck(player[i]->getId());
				player[i]->setHand(NULL);
			}
		}
	}
	/***** Fin cas "un joueur fait blackjack" *****/

	/***** Demandes d'actions aux joueurs *****/
	for (unsigned int j = 0; j < this->player.size(); ++j)
	{
		if (this->player[j] != NULL && !this->player[j]->getBlackjack())  // Le joueur n'a pas fait blackjack
		{
            int returnPlayerAction;
			// Boucle d'actions sur la main 1
			while (player[j]->getHand() != NULL && !player[j]->getHand()->getStand() && !player[j]->getSurrender())
			{
				returnPlayerAction = this->playerAction(player[j], 0);
				if (returnPlayerAction == -1)
				{
                    j--;
					break;  // Le joueur a quitté le jeu donc le joueur n'existe plus dans le vecteur
                }
                else if (returnPlayerAction == 0)
                    return 0;  // Fin du jeu

				else if (!player[j]->getSurrender() && player[j]->getHand() != NULL && player[j]->getHand()->getValue1() >= 21)  // Si la valeur basse de la main est >= 21, le joueur est obligé de s'arreter.
				{
					this->player[j]->getHand()->setStand(true);
					this->com.validStand(player[j]->getId(), 0);
					this->com.ReceiveAck(player[j]->getId());
				}
			}

			// Boucle d'actions sur la main 2
			while (returnPlayerAction != -1 && player[j]->getHand2() != NULL && !player[j]->getHand2()->getStand() && !player[j]->getSurrender())
			{
				if (this->playerAction(player[j], 1) == 0);
                    return 0;  // Fin du jeu

				if (player[j]->getHand() != NULL && player[j]->getHand2()->getValue1() >= 21)  // Si la valeur basse de la main est >= 21, le joueur est obligé de s'arreter.
				{
					this->player[j]->getHand2()->setStand(true);
					this->com.validStand(this->player[j]->getId(), 1);
					this->com.ReceiveAck(this->player[j]->getId());
				}
			}
		}
	}
	/***** Fin des demandes d'actions aux joueurs *****/


	/***** Tirage des cartes de la banque *****/
	Card *c = bank.getHand()->getCard(1);
	c->setType(bank.getHiddenCard()->getType());  // On met à jour la carte cachée avec son vrai type
	delete bank.getHiddenCard();  // Désallocation de la carte cachée
	this->bank.setHiddenCard(NULL);
	this->com.SendCard(4, c->getType(), 0, this->player);
	this->com.ReceiveAck(this->player);
	this->interface.printGameState(getPlayers(), getBank());

	cout << endl << "##################################################" << endl;
	cout << "La banque tire à 16 et s'arrete à 17." << endl;
	cout << "##################################################" << endl;

	while (bank.getHand()->getValue2() < 17 || bank.getHand()->getValue1() < 17)
	{
		c = NULL;
		c = hitCard();
		bank.getHand()->addCard(c);
		com.SendCard(4, c->getType(), 0, this->player);
		com.ReceiveAck(this->player);
	}

	interface.printGameState(getPlayers(), getBank());
	/***** Fin du tirage des cartes de la banque *****/

	/***** Fin du tour : verif des mises *****/

	cout << endl << "##################################################" << endl << endl;
	cout << "FIN DU TOUR : RESULTATS" << endl;

	for (unsigned int i = 0; i < this->player.size(); i++)
	{
        cout << endl;
		if (player[i]->getHand() != NULL)
			endRound(player[i], 0);
		if (player[i]->getHand2() != NULL)
			endRound(player[i], 1);

        if (player[i]->getBlackjack())
            cout << "Joueur " << player[i]->getId() << " a fait Blackjack !" << endl;
        else if (player[i]->getSurrender())
            cout << "Joueur " << player[i]->getId() << " a abandonné le tour." << endl;

        if (player[i]->getBalance() < getBetMin())
		{
		    cout << endl << "~ Votre solde est insuffisant pour continuer Joueur" << i;
            BankInterface::center_output("*** Vous devez quitter le jeu ***", 50);
		    if (quitePlayer(player[i]) == 0);
		        return 0;  // Le jeu est fini car il n'y a plus de joueur
		}
	}

	cout << endl << "Le solde de la Banque est de $ " << bank.getBalance() << endl << endl;
	cout << "##################################################" << endl << endl;

	com.EndRound(this->player);



	// Désallocation mains joueurs
	for (unsigned int i = 0; i < this->player.size(); ++i)
	{
		com.ReceiveAck(player[i]->getId());
		if (player[i]->getHand() != NULL)
            player[i]->setHand(NULL);

		if (player[i]->getHand2() != NULL)
            player[i]->setHand2(NULL);
	}

	// Désallocation main banque
	if (bank.getHand() != NULL)
        	bank.setHand(NULL);

	return 1;
}

void BankGame::shuffleDeck()
{
	random_shuffle(this->deck.begin(), this->deck.end());
}
