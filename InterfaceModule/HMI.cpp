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

/**
 * Affiche l'état du jeu en fonction du jeu et des actions possibles pour le joueur
 * @param p       le joueur
 * @param hit     le joueur peut hit ?
 * @param split   le joueur peut split ?
 * @param doubler le joueur peut doubler ?
 * @param stay    le joueur peut stay ?
 */
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

/**
 * Récupère l'action que le joueur souhaite faire
 * @param  hit     le joueur peut hit ?
 * @param  split   le joueur peut split ?
 * @param  doubler le joueur peut doubler ?
 * @param  stay    le joueur peut stay ?
 * @return         le caractère correspondant à l'action voulue par le joueur
 */
char askAction(bool hit, bool split, bool doubler, bool stay);
{
    char response;

    char possibleChoices[4];

    if (hit) possibleChoices[0] = 'C' else possibleChoices[0] = ' ';
    if (split) possibleChoices[1] = 'P' else possibleChoices[1] = ' ';
    if (doubler) possibleChoices[2] = 'S' else possibleChoices[2] = ' ';
    if (stay) possibleChoices[3] = 'R' else possibleChoices[3] = ' ';

    do
    {
        cin >> response;
        if (cin.fail()) cout << "Erreur, veuillez recommencez" << endl;
    } while (cin.fail() || response == ' ' || (response != possibleChoices[0] && response != possibleChoices[1] && response != possibleChoices[2] && response != possibleChoices[3]))

    return response;
}