/**
 * BankInterface.cpp
 * @author Thomas MAINGUY
 */

#include "BankInterface.h"

using namespace std;

void BankInterface::printGameState(std::vector<Player*> &players, Bank &bank)
{
    cout << "#########################" << endl << endl;

    cout << "Cartes Banque : ";

    std::vector<Card*> cards = bank.getHand()->getCards();

    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        cout << (*it)->getStringRepresentation() << " ";
    }
    cout << "Valeur : " << bank.getHand()->getValue2();
    cout << endl;


    for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
    {
        cout << "Joueur " << (*it)->getId() << " : " << endl;

        if ((*it)->getHand() != NULL)
        {
            cout << "\t Mise : $ " << (*it)->getHand()->getBet() << endl;

            cards = (*it)->getHand()->getCards();
            cout << "\t Cartes : ";
            for (vector<Card*>::iterator it2 = cards.begin(); it2 != cards.end(); it2++)
            {
                cout << (*it2)->getStringRepresentation() << " ";
            }
            cout << "Valeur : " << (*it)->getHand()->getValue2();
            if ((*it)->getHand()->getValue2() != (*it)->getHand()->getValue1())
                cout << " / " << (*it)->getHand()->getValue1();
            cout << endl;
        }

        if ((*it)->getHand2() != NULL)
        {
            cout << "\t Main 2 : " << endl << "====" << endl;
            cout << "\t Mise : $ " << (*it)->getHand2()->getBet() << endl << endl;

            std::vector<Card*> cards2 = (*it)->getHand2()->getCards();
            cout << "\t Cartes : ";
            for (vector<Card*>::iterator it2 = cards2.begin(); it2 != cards2.end(); it2++)
            {
                cout << (*it2)->getStringRepresentation() << " ";
            }
            cout << "Valeur : " << (*it)->getHand()->getValue2();
            if ((*it)->getHand()->getValue2() != (*it)->getHand()->getValue1())
                cout << " / " << (*it)->getHand()->getValue1();
            cout << endl;
        }
        else if ((*it)->getHand() == NULL)
        {
            cout << "Le joueur a abandonné tour." << endl << endl;
        }
    }


}
