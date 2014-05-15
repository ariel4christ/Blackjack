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
int HMI::getBet(Player &p)
{
	long bet;

    cout << endl << "##################################################" << endl << endl;
    center_output("*** Nouveau Tour ***\n", 50);

	do
	{
        cout << "~ Votre solde est de $ " << p.getBalance() << "." << endl << endl;
        cout << "> Si vous souhaitez quitter le jeu, entrez Q." << endl;
		cout << "> Sinon, entrer une mise entière comprise entre $ " << UserGame::getBetMin() << " et $ " << UserGame::getBetMax() << " : ";
		char bet_str[16];
		scanf("%s", bet_str);
        cout << endl;

        if (bet_str[0] == 'Q')
            return -1;

        bet = strtol(bet_str, NULL, 10);

        if (bet == 0)
        {
            cout << "##### Veuillez entrer une mise entière SVP #####" << endl << endl;
            cin.clear();
            cin.ignore(999,'\n');
            bet = -1;  // permettera de rester dans la boucle do while
        }
        else if (bet < UserGame::getBetMin() || bet > UserGame::getBetMax())
            cout << "##### La mise doit etre entre $ " << UserGame::getBetMin() << " et $ " << UserGame::getBetMax() << " ! #####" << endl << endl;
	}
	while (bet < UserGame::getBetMin() || bet > UserGame::getBetMax());

    cout << "##################################################" << endl << endl;

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
	cout << "##################################################" << endl << endl;
	cout << "~ JOUEUR " << p.getId() << endl;
	cout << "~ Solde : $ " << p.getBalance() << endl;
	cout << "~ Main 1 :" << endl << "\tMise : $ " << p.getHand()->getBet() << endl;

	std::vector<Card*> cards = p.getHand()->getCards();
	cout << "\tCartes : ";
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
    	cout << "Main 2 : " <<  endl;
    	cout << "\tMise : $ " << p.getHand2()->getBet() << endl;

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
    if (hit) cout << "> Demander carte ? (C)" << endl;
    if (split) cout << "> Partager la main (split) ? (P)" << endl;
    if (doubler) cout << "> Doubler ? (D)" << endl;
    if (stay) cout << "> Rester ? (R)" << endl;
    cout << "> Abandonner la main? (A)" << endl;
    cout << "> Abandonner la main ET quitter le jeu? (Q)" << endl;
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
        cout << endl << "~ Entrez la lettre correspondant à votre décision : ";
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
    cout << endl << "~ La première carte de la banque est un AS." << endl << "~ La banque peut faire Blackjack !" << endl;

    if(player.getBalance() < (int) player.getHand()->getBet() / 2)
        return false;

    cout << "> Voulez-vous prendre une assurance ? O/N" << endl;
    do
    {
        cin >> response;
        if (cin.fail()) cout << "### Erreur, veuillez recommencez. Merci d'entrer O ou N ###" << endl;
    } while (cin.fail() || (response != 'O' && response != 'N'));

    return (response == 'O') ? true : false;
}

void HMI::PrintEndRound(Player &p)
{
    cout << endl << "##################################################" << endl << endl;
    cout << "Fin du Tour. Les résulats sont affichés dans la banque." << endl;
    cout << "Nouveau solde : $" << p.getBalance() << endl << endl;
    cout << "Début du tour suivant..." << endl << endl;
    cout << "##################################################" << endl << endl;
}

/**
 * Affichage de début de jeu.
 * @param id Entier contenant l'id (identifiant) du joueur.
 */
void HMI::PrintEnterGame(int id)
{
    system("clear");
    cout << "##################################################" << endl << endl;
    center_output("******* Blackjack *******", 50);
    cout << endl;
    center_output("*** Nouveau Joueur ***", 50);
    cout << endl << "~ Bienvenu, votre nom est : Joueur " << id << endl << endl;
    cout << "##################################################" << endl << endl;
}
void HMI::PrintMessage(string str)
{
    cout << "##################################################" << endl << endl;
    cout << str << endl << endl;
    cout << "##################################################" << endl << endl;
}

// numb_cols = nombre de colonnes dans la console.
// Je prends toujours 50.
void HMI::center_output(std::string str, int num_cols)
{
    // Calculate left padding
    int padding_left = (num_cols / 2) - (str.size() / 2);

    // Put padding spaces
    for(int i = 0; i < padding_left; ++i) std::cout << ' ';

    // Print the message
    std::cout << str << endl;
}
