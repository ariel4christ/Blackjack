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


