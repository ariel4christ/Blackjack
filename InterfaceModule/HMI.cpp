/**
 * HMI.cpp
 * @author Thomas MAINGUY
 * @author Ariel NONO
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
	do {
		cout << "> Entrez votre mise ente $" << UserGame::getBetMin() << " et $" << UserGame::getBetMax() << " :" << endl;
		cin>>bet;

		if (cin.fail()) // Valeur recue en console n'est pas un entier
        {
			cout << "### Veuillez entrer une mise entière SVP ###" << endl;
            cin.clear();
            cin.ignore(999,'\n');
        }
	}
	while (cin.fail() || bet < UserGame::getBetMin() || bet > UserGame::getBetMax());

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
	cout << "JOUEUR " << p.getId() << endl;
	cout << "Solde : $ " << p.getBalance() << endl << endl;
	cout << "Main 1 :" << endl << "Mise : $ " << p.getHand()->getBet() << endl << endl;

	std::vector<Card*> cards = p.getHand()->getCards();
	cout << "Cartes : ";
    for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        cout << (*it)->getStringRepresentation() << " ";
    }
    cout << "Valeur : " << p.getHand()->getValue2();
    if (p.getHand()->getValue2() != p.getHand()->getValue1())
        cout << " / " << p.getHand()->getValue1();
    cout << endl << endl;

    if (p.getHand2() != NULL)
    {
    	cout << "====" << endl << "Main 2 : " <<  endl;
    	cout << "\tMise : $ " << p.getHand2()->getBet() << endl << endl;

		std::vector<Card*> cards2 = p.getHand2()->getCards();
		cout << "\tCartes : ";
	    for (vector<Card*>::iterator it = cards2.begin(); it != cards2.end(); it++)
	    {
	        cout << (*it)->getStringRepresentation() << " ";
	    }
	    cout << "Valeur : " << p.getHand2()->getValue2();
	    if (p.getHand2()->getValue2() != p.getHand2()->getValue1())
            cout << " / " << p.getHand2()->getValue1();
	    cout << endl << endl;
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
    if (doubler) possibleChoices[2] = 'D'; else possibleChoices[2] = ' ';
    if (stay) possibleChoices[3] = 'R'; else possibleChoices[3] = ' ';
    possibleChoices[4] = 'A';
    possibleChoices[5] = 'Q';

    do
    {
        cout << endl << "> Entrez la lettre correspondant à votre décision : ";
        response = '\0';
        cin >> response;
        if (cin.fail()) cout << "### Erreur, veuillez recommencez ###" << endl;
    } while (cin.fail() || response == ' ' ||
            (response != possibleChoices[0] && response != possibleChoices[1]
            && response != possibleChoices[2] && response != possibleChoices[3]
            && response != possibleChoices[4] && response != possibleChoices[5]));

    return response;
}

bool HMI::insurrance(Player &player)
{
    char response;
    cout << endl << "> La première carte de la banque est un AS." << endl << "> La banque peut faire Blackjack !" << endl;

    if(player.getBalance() < (int) player.getHand()->getBet() / 2)
        return false;

    cout << "# Voulez-vous prendre une assurance ? O/N" << endl;
    do
    {
        cin >> response;
        if (cin.fail()) cout << "### Erreur, veuillez recommencez ###" << endl;
    } while (cin.fail() || (response != 'O' && response != 'N'));

    return (response == 'O') ? true : false;
}

void HMI::PrintEndRound(Player &p)
{
    cout << endl << "#########################" << endl << endl;
    cout << "Fin du Tour. Les résulats sont affichés dans la banque." << endl;
    cout << "Nouveau solde : $" << p.getBalance() << endl << endl;
    cout << "Début du tour suivant..." << endl << endl;
    cout << "#########################" << endl << endl;
}
