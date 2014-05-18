#include "BankModule/BankGame.h"

using namespace std;


int main(int argc, char  *argv[])
{
	int min, max;
	long playerInit, bankInit;

	switch (argc)
	{
		case 1 :
			min = 5;
			max = 100;
			playerInit = 2000;
			bankInit = 200000000;
			break;

		case 5 :
			min = atoi(argv[1]);
			max = atoi(argv[2]);
			playerInit = atoi(argv[3]);
			bankInit = atoi(argv[4]);
			break;

		default :
			cout << "Le programme de la Banque peut etre lancé avec 0 ou 5 paramètres." << endl;
			cout << "Les paramètres doivent etre dans l'ordre suivant :" << endl;
			cout << "\tMise minimale\n\tMise maximale\n\tSolde initial d'un joueur\n\tSolde initial de la Banque" << endl << endl;
			exit(EXIT_FAILURE);
			break;
	}

    if (min < 1)
    {
        cout << "Erreur :\tLa mise minimale doit etre supérieure \n\t\tou égale à 1" << endl << endl;
        exit(EXIT_FAILURE);
    }

	if (min > max)
    {
        cout << "Erreur :\tLa mise maximale doit etre supérieure \n\t\tou égale à la mise minimale." << endl << endl;
        exit(EXIT_FAILURE);
    }

    if (playerInit < min)
    {
        cout << "Erreur :\tLe solde initial d'un joueur doit etre supérieur \n\t\tou égal à la mise minimale." << endl << endl;
        exit(EXIT_FAILURE);
    }

	if (bankInit < (8 * max))  // La banque doit pouvoir perdre contre 4 joueurs qui ont doublé.
	{
        cout << "Erreur :\tLe solde initial de la Banque doit etre supérieur \n\t\tou égal à 8 fois la mise maximale." << endl << endl;
        exit(EXIT_FAILURE);
	}

	BankGame bank(min, max, playerInit, bankInit);

	system("clear");
	cout << "##################################################" << endl <<endl;
	cout << "Pour pouvoir jouer, il faut que les vieux fichiers des joueurs soient effacés." << endl;
	cout << "Si le jeu ne s'est pas terminé correctement lors de la précédente utilisation," << endl;
	cout << "ou bien si vous n'etes pas sur que les fichiers soient effacés," << endl;
	cout << "il est prérable de le faire." << endl;
	cout << "Si vous effacez les fichiers, les éventuels programmes Joueur (Player ou Ia)" << endl;
	cout << "déjà lancés, ne pourront pas rejoindre la partie. Il faudra les relancer." << endl << endl;

	char suppr;
	do
	{
		suppr = '\0';
		cout << "> Voulez-vous supprimer les vieux fichiers ? O / N \t: ";
		cin >> suppr;
		cout << endl;
	} while (cin.fail() || (suppr != 'O' && suppr != 'N' && suppr!= 'o' && suppr != 'n'));

	if (suppr == 'O' || suppr == 'o')
	{
		bank.getCom().CleanFiles();
		cout << "Fichiers supprimés! Vous pouvez lancer les programmes Joueur." << endl;
	}

	cout << "\n\nLorsque tous les programmes joueurs sont lancés pour le 1er tour,\n> Appuyez sur Entrée..." << endl;
	while (getchar() != '\n');
	getchar();
	cout << endl << "##################################################" << endl;

	bank.runGame();

	return 0;
}

