/*
 * HMI.cpp
 */

#include "HMI.h"

using namespace std;

HMI::HMI() {
	// TODO Auto-generated constructor stub

}

HMI::~HMI() {
	// TODO Auto-generated destructor stub
}

int HMI::getBet()
{
	int bet;
	do{
		cout<<"Faites votre pari"<< endl;
		cin>>bet;

		if(cin.fail())// valeur recu en cosole n'est pas un entier
			cout<<"Veuillez inserer un pari entier"<<endl;
	}
	while(cin.fail());

	return bet;
}

void HMI::PrintGameState(Player &p, bool hit, bool split, bool doubler, bool stay)
{
	cout << "#########################" << endl << endl;
	cout << "Mise : $ " << p.getHand()->getBet() << endl << endl;

	std::vector<Card*> cards = p.getHand()->getCards();
	cout << "Cartes : ";
    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        cout << (*it)->getStringRepresentation() << " ";
    }
    cout << endl;

    if (p.getHand2() != NULL)
    {
    	cout << "Main 2 : " << endl << "====" << endl;
    	cout << "Mise : $ " << p.getHand2()->getBet() << endl << endl;

		std::vector<Card*> cards2 = p.getHand2()->getCards();
		cout << "Cartes : ";
	    for (vector<Card*>::iterator it = cards2.begin(); it != cards2.end(); it++)
	    {
	        cout << (*it)->getStringRepresentation() << " ";
	    }
	    cout << endl;
    }

    // On affiche les messages qu'il faut
    if (hit) cout << "Demander carte ? (C)" << endl;
    if (split) cout << "Split ? (P)" << endl;
    if (doubler) cout << "Doubler ? (D)" << endl;
    if (stay) cout << "Rester ? (R)" << endl;
    cout << "Abandonner la main" << endl;
    cout << "Abandonner la main ET quitter le jeu" << endl;
}
