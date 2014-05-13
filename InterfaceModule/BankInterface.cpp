/**
 * BankInterface.cpp
 * @author Thomas MAINGUY
 */

#include "BankInterface.h"

using namespace std;


void BankInterface::printGameState(std::vector<Player*> &players, Bank &bank)
{
    cout << "##################################################" << endl << endl;

    for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
    {
        cout << "Joueur " << (*it)->getId() << "  :   ";

        if ((*it)->getHand() != NULL)
        {
            cout << "$ " << (*it)->getHand()->getBet();

            std::vector<Card*> cards = (*it)->getHand()->getCards();
            cout << "\t";
            for (vector<Card*>::iterator it2 = cards.begin(); it2 != cards.end(); it2++)
            {
                cout << (*it2)->getStringRepresentation() << " ";
            }
            cout << "   " << (*it)->getHand()->getValue2();
            if ((*it)->getHand()->getValue2() != (*it)->getHand()->getValue1())
                cout << " / " << (*it)->getHand()->getValue1();
            cout << endl;
        }

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
            cout << "   " << (*it)->getHand()->getValue2();
            if ((*it)->getHand()->getValue2() != (*it)->getHand()->getValue1())
                cout << " / " << (*it)->getHand()->getValue1();
            cout << endl;
        }

        else if ((*it)->getHand() == NULL)
            cout << "Le joueur a abandonné le tour." << endl;

        cout << endl;
    }


    cout << "Banque    :\t\t";

    std::vector<Card*> cards = bank.getHand()->getCards();

    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
        cout << (*it)->getStringRepresentation() << " ";

    cout << "   " << bank.getHand()->getValue2() << endl << endl;
    cout << "##################################################" << endl << endl;
}
