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
			min = *(argv[1]);
			max = *(argv[2]);
			playerInit = *(argv[3]);
			bankInit = *(argv[4]);
		
		default :
			cout << "Le programme de la Banque peut etre lancé avec ou sans paramètres." << endl;
			cout << "Les paramètres doivent etre dans l'ordre suivant :" << endl;
			cout << "\tMise minimale\n\tMise maximale\n\tSode initial d'un joueur\n\tSolde initial de la Banque" << endl;
			exit(0);
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
	} while (cin.fail() || (suppr != 'O' && suppr != 'N'));
	
	if (suppr == 'O')
	{
		bank.getCom().CleanFiles();
		cout << "Fichiers supprimés! Vous pouvez lancer les programmes Joueur." << endl;
	}
	
	cout << "\n\nLorsque tous les programmes joueurs sont lancés pour le 1er tour,\n> Appuillez sur n'importe quelle touche..." << endl;
	while (getchar() != '\n');
	getchar();
	cout << endl << "##################################################" << endl;
	
	bank.runGame();

	return 0;
}

