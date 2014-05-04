#include "BankInterface.h"

using namespace std;

void PrintGameState(std::vector<Player*> players, Bank bank)
{
    cout << "#########################" << endl << endl;

    cout << "Cartes Banque : ";

    std::vector<Card*> cards = bank.getHand()->getCards();

    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        cout << (*it)->getStringRepresentation() << " ";
    }
    cout << endl;


    for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
    {
        cout << "Joueur " << (*it)->getId() << " : " << endl;

        cout << "Mise : $ " << (*it)->getHand()->getBet() << endl << endl;

        cards = (*it)->getHand()->getCards();
        cout << "Cartes : ";
        for (vector<Card*>::iterator it2 = cards.begin(); it2 != cards.end(); it2++)
        {
            cout << (*it2)->getStringRepresentation() << " ";
        }
        cout << endl;

        if ((*it)->getHand2() != NULL)
        {
            cout << "Main 2 : " << endl << "====" << endl;
            cout << "Mise : $ " << (*it)->getHand2()->getBet() << endl << endl;

            std::vector<Card*> cards2 = (*it)->getHand2()->getCards();
            cout << "Cartes : ";
            for (vector<Card*>::iterator it2 = cards2.begin(); it2 != cards2.end(); it2++)
            {
                cout << (*it2)->getStringRepresentation() << " ";
            }
            cout << endl;
        }
    }


}
