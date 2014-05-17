#include "UserModule/UserGame.h"

using namespace std;

int main(int argc, char const *argv[])
{
	UserGame u;
	system("clear");
	cout << "##################################################" << endl;
	cout << endl << "En attente de la Banque..." << endl;
	cout << endl << "##################################################" << endl;
	u.runGame();

	return 0;
}
