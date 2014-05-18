/**
 * IaMain.cpp
 * Main de l'éxécutable Ia.
 * @author Ariel NONO
 */

#include "AIModule/AIGame.h"

using namespace std;


int main(int argc, char const *argv[])
{
    AIGame ia;
    system("clear");
	cout << "##################################################" << endl;
	AI::center_output("******* Blackjack *******", 50);
	cout << endl << "En attente de la Banque..." << endl;
	cout << endl << "##################################################" << endl << endl;
    ia.runGame();

    return 0;
}
