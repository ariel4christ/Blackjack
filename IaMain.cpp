/**
 * IaMain.cpp
 * Main de l'éxécutable Ia.
 * @author Ariel NONO
 */

#include "AIModule/AIGame.h"
#include <string.h>

using namespace std;


int main(int argc, char const *argv[])
{
	AIGame ia;
	bool wait = false;
	system("clear");
	
	cout << "##################################################" << endl;
	AI::center_output("******* Blackjack *******", 50);
	cout << endl << "~ En attente de la Banque..." << endl;
	cout << endl << "##################################################" << endl << endl;
	
	if(argc >= 2 && strcmp(argv[1],"-v") == 0)
	{
		wait=true;
		cout << "##################################################" << endl;
		AI::center_output("~~~~ MODE INTERACTIF ~~~~",50);
		cout << "##################################################" << endl;
	}
	else {
		cout << "##################################################" << endl;
		AI::center_output("~~~~ MODE AUTOMATIQUE ~~~~",50);
		cout << "##################################################" << endl;
	}

	ia.runGame(wait);

	return 0;
}
