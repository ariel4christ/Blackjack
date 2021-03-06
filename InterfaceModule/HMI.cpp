/**
 * HMI.cpp
 * @author Thomas MAINGUY
 * @author Ariel NONO
 * @author Christophe HUBERT
 */

#include "HMI.h"
#include "../UserModule/UserGame.h"

using namespace std;

/**
 * Demande au joueur la somme qu'il veut parier
 * @param   p       Référence vers Player, joueur à qui une mise est demandée.
 * @return  Entier  Mise du joueur.
 */
int HMI::getBet(Player &p)
{
	long bet;

	cout << endl << "##################################################" << endl << endl;
	center_output("*** Nouveau Tour ***", 50);
	cout << endl << "##################################################" << endl << endl;
	cout << endl;

	do
	{
		cout << "~ Votre solde est de $ " << p.getBalance() << "." << endl << endl;
		cout << "> Si vous souhaitez quitter le jeu, entrez Q." << endl;
		cout << "> Sinon, entrez une mise entière comprise entre $ " << UserGame::getBetMin() << " et $ "
				<< UserGame::getBetMax() << " : ";
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
			cin.ignore(999, '\n');
			bet = -1;  // permettera de rester dans la boucle do while
		}
		else if (bet < UserGame::getBetMin() || bet > UserGame::getBetMax())
			cout << "##### La mise doit etre entre $ " << UserGame::getBetMin() << " et $ " << UserGame::getBetMax()
					<< " ! #####" << endl << endl;
		else if (p.getBalance() < bet)
			cout << "### Impossible : vous n'avez que $ " << p.getBalance() << " ###" << endl << endl;
	} while (bet < UserGame::getBetMin() || bet > UserGame::getBetMax() || bet > p.getBalance());

	cout << "##################################################" << endl << endl;
	cout << "~ Attente de la Banque..." << endl << endl;

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

	vector<Card*> cards = p.getHand()->getCards();

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
		cout << "~ Main 2 : " << endl;
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
	if (hit)
		cout << "> Demander carte ? (C)" << endl;
	if (split)
		cout << "> Partager la main (split) ? (P)" << endl;
	if (doubler)
		cout << "> Doubler ? (D)" << endl;
	if (stay)
		cout << "> Rester ? (R)" << endl;
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
char HMI::askAction(bool hit, bool split, bool doubler, bool stay, int secHand)
{
	char response;

	char possibleChoices[6];

	if (hit)
		possibleChoices[0] = 'C';
	else
		possibleChoices[0] = ' ';
	if (split)
		possibleChoices[1] = 'P';
	else
		possibleChoices[1] = ' ';
	if (doubler)
		possibleChoices[2] = 'D';
	else
		possibleChoices[2] = ' ';
	if (stay)
		possibleChoices[3] = 'R';
	else
		possibleChoices[3] = ' ';
	possibleChoices[4] = 'A';
	possibleChoices[5] = 'Q';

	do
	{
		cout << endl << "> Entrez la lettre correspondant à votre décision ";
		if (secHand == 0)
			cout << "pour la main 1 : ";
		else if (secHand == 1)
			cout << "pour la main 2 : ";
		else
			throw runtime_error("Erreur dans le numero de main HMI::AskAction");

		response = '\0';
		cin.clear();
		cin >> response;
		if (cin.fail())
			cout << "### Erreur, veuillez recommencez ###" << endl;
	} while (cin.fail() || response == ' '
			|| (response != possibleChoices[0] && response != possibleChoices[1] && response != possibleChoices[2]
					&& response != possibleChoices[3] && response != possibleChoices[4]
					&& response != possibleChoices[5]));

	cout << "~ Attente de la Banque..." << endl << endl;
	return response;
}

/**
 * Fonction qui demande au joueur si il veut prendre une assurance ou non.
 * @param   player  Référence vers Player, le joueur à qui une assurance est proposée.
 * @return          FALSE si l'assurance est refusée et TRUE si elle est acceptée.
 */
bool HMI::insurrance(Player &player)
{
	char response;
	cout << endl << "~ La première carte de la banque est un AS." << endl << "~ La banque peut faire Blackjack !"
			<< endl;

	if (player.getBalance() < (int) player.getHand()->getBet() / 2)
		return false;

	do
	{
		cout << "> Voulez-vous prendre une assurance ? O/N" << endl;
		cin.clear();
		cin >> response;
		if (cin.fail())
			cout << "### Erreur, veuillez recommencez. Merci d'entrer O ou N ###" << endl;
	} while (cin.fail() || (response != 'O' && response != 'N' && response != 'o' && response != 'n'));

	cout << endl << "##################################################" << endl << endl;
	cout << "Attente de la Banque..." << endl << endl;
	return (response == 'O' || response == 'o') ? true : false;
}

/**
 * Affichage lors de la fin d'un tour avec le solde final du joueur.
 * @param   p   Joueur en référence.
 */
void HMI::PrintEndRound(Player &p)
{
	cout << endl << "##################################################" << endl << endl;
	cout << "Fin du Tour. Les résulats sont affichés dans la Banque." << endl;
	cout << "Nouveau solde : $ " << p.getBalance() << endl << endl;
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
	cout << endl << "~ Bienvenue, votre nom est : Joueur " << id << endl << endl;
	cout << "##################################################" << endl << endl;
}

/**
 * Affiche la chaine de caractère en paramètre.
 * @param   str String à afficher.
 */
void HMI::PrintMessage(string str)
{
	cout << "##################################################" << endl << endl;
	cout << str << endl << endl;
	cout << "##################################################" << endl << endl;
}

/**
 * Fonction centrant la string passée en paramètre, par rappot au nombre de colonnes.
 * @param   str         String contenant le message.
 * @param   num_cols    Entier nombre de colonnes.
 */
// numb_cols = nombre de colonnes dans la console.
// Je prends toujours 50.
void HMI::center_output(string str, int num_cols)
{
	// Calculate left padding
	int padding_left = (num_cols / 2) - (str.size() / 2);

	// Put padding spaces
	for (int i = 0; i < padding_left; ++i)
		cout << ' ';

	// Print the message
	cout << str << endl;
}
