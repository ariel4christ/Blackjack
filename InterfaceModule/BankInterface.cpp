/**
 * BankInterface.cpp
 * @author Thomas MAINGUY
 */

#include "BankInterface.h"

using namespace std;

void BankInterface::printGameState(std::vector<Player*> &players, Bank &bank)
{
	cout << "##################################################" << endl << endl;

	/* Affichage des cartes des joueurs */
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		cout << "Joueur " << (*it)->getId() << "  :   ";

		// Affichage Main 1
		if ((*it)->getHand() != NULL)
		{
			cout << "$ " << (*it)->getHand()->getBet();

			std::vector<Card*> cards = (*it)->getHand()->getCards();
			cout << "\t";
			for (vector<Card*>::iterator it2 = cards.begin(); it2 != cards.end(); it2++)
			{
				cout << (*it2)->getStringRepresentation() << " ";
			}
			cout << "\t" << (*it)->getHand()->getValue2();
			if ((*it)->getHand()->getValue2() != (*it)->getHand()->getValue1())
				cout << " / " << (*it)->getHand()->getValue1();

			cout << endl;
		}

		// Affichage Main 2
		if ((*it)->getHand2() != NULL)
		{
			cout << "Joueur " << (*it)->getId() << "  :   ";
			cout << "$ " << (*it)->getHand2()->getBet();

			std::vector<Card*> cards = (*it)->getHand2()->getCards();
			cout << "\t";
			for (vector<Card*>::iterator it2 = cards.begin(); it2 != cards.end(); it2++)
			{
				cout << (*it2)->getStringRepresentation() << " ";
			}
			cout << "\t" << (*it)->getHand2()->getValue2();
			if ((*it)->getHand2()->getValue2() != (*it)->getHand2()->getValue1())
				cout << " / " << (*it)->getHand2()->getValue1();

			cout << endl;
		}

		else if ((*it)->getHand() == NULL)
			cout << "Le joueur a abandonné le tour." << endl;

		cout << endl;
	}

	/* Affichage des cartes de la banque */
	cout << "Banque    :   " << "\t\t";

	std::vector<Card*> cards = bank.getHand()->getCards();

	for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
		cout << (*it)->getStringRepresentation() << " ";

	cout << "\t" << bank.getHand()->getValue2() << endl << endl;
	cout << "##################################################" << endl << endl;
}

// numb_cols = nombre de colonnes dans la console.
// Je prends toujours 50.
void BankInterface::center_output(std::string str, int num_cols)
{
	// Calculate left padding
	int padding_left = (num_cols / 2) - (str.size() / 2);

	// Put padding spaces
	for (int i = 0; i < padding_left; ++i)
		std::cout << ' ';

	// Print the message
	std::cout << str << endl;
}
