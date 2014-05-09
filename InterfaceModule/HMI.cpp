/*
 * HMI.cpp
 */

#include "HMI.h"
#include "../UserModule/UserGame.h"

using namespace std;
/**
 * Demande au joueur la somme qu'il veut parier
 */
int HMI::getBet()
{
	int bet;
	do{
		cout << "Entrez vorte mise ente " << UserGame::getBetMin() << " et " << UserGame::getBetMax() << " :" << endl;
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
    cout << "Abandonner la main? (A)" << endl;
    cout << "Abandonner la main ET quitter le jeu? (Q)" << endl;
}

/**
 * Récupère l'action que le joueur souhaite faire
 * @param  hit     le joueur peut hit ?
 * @param  split   le joueur peut split ?
 * @param  doubler le joueur peut doubler ?
 * @param  stay    le joueur peut stay ?
 * @return         le caractère correspondant à l'action voulue par le joueur
 */
char HMI::askAction(bool hit, bool split, bool doubler, bool stay)
{
    char response;

    char possibleChoices[6];

    if (hit) possibleChoices[0] = 'C'; else possibleChoices[0] = ' ';
    if (split) possibleChoices[1] = 'P'; else possibleChoices[1] = ' ';
    if (doubler) possibleChoices[2] = 'S'; else possibleChoices[2] = ' ';
    if (stay) possibleChoices[3] = 'R'; else possibleChoices[3] = ' ';
    possibleChoices[4] = 'A';
    possibleChoices[5] = 'Q';

    do
    {
        cin >> response;
        if (cin.fail()) cout << "Erreur, veuillez recommencez" << endl;
    } while (cin.fail() || response == ' ' || (response != possibleChoices[0] && response != possibleChoices[1] && response != possibleChoices[2] && response != possibleChoices[3] && response != possibleChoices[4] && response != possibleChoices[5]));

    return response;
}

bool HMI::insurrance()
{
    char response;

    cout << "Voulez-vous prendre une assurance ? O/N" << endl;
    do
    {
        cin >> response;
        if (cin.fail()) cout << "Erreur, veuillez recommencez" << endl;
    } while (cin.fail() || (response != 'O' && response != 'N'));

    return (response == 'O') ? true : false;
}
