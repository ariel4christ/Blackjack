/**
 * AI.cpp
 * @author Ariel NONO
 */

#include "AI.h"

using namespace std;

AI::AI()
{
}

AI::~AI()
{
}


void AI::insurrance(int value)
{
	cout << "##################################################" << endl << endl;
	if(!value)
		cout<<">L'IA ne prends pas d'assurance !"<<endl<<endl;;
}

void AI::stateCards(Player& ia){

	cout << "##################################################" << endl << endl;
	std::vector<Card*>  myCards;

	cout<<"Les cartes de l'IA:"<<endl;

	if(ia.getHand() != NULL){
		cout << "\n___Main 1___\n" <<  endl;
		myCards = ia.getHand()->getCards();

		for (vector<Card*>::iterator it = myCards.begin(); it != myCards.end(); it++)
	    {
	        cout << (*it)->getStringRepresentation() << " ";
	    }
		cout<<""<<endl<<endl;
	    cout << "Valeur : " << ia.getHand()->getValue2();

	    if (ia.getHand()->getValue2() != ia.getHand()->getValue1())
	        cout << " / " << ia.getHand()->getValue1();

	    cout << endl << endl;
	}
	    if (ia.getHand2() != NULL)
	    {
	    	cout << "\n___Main 2___\n" <<  endl;

			std::vector<Card*> myCards2 = ia.getHand2()->getCards();

		    for (vector<Card*>::iterator it = myCards2.begin(); it != myCards2.end(); it++)
		    {
		        cout << (*it)->getStringRepresentation() << " ";
		    }

		    cout<<""<<endl<<endl;

		    cout << "Valeur : " << ia.getHand2()->getValue2();

		    if (ia.getHand2()->getValue2() != ia.getHand2()->getValue1())
	            cout << " / " << ia.getHand2()->getValue1();

		    cout << endl << endl;
	    }
}

void AI::stateBalanceBet(Player & ia,int bet)
{
	cout << "##################################################" << endl << endl;
	cout<< "\nSolde:\t"<<ia.getBalance()<<endl<<endl;
	cout<<"L'IA mise :\t $"<<bet<<endl<<endl;
}

void AI::choice(int hand,bool hit, bool stand, bool Double, bool split,bool quit,bool surrender)
{
	cout << "##################################################" << endl << endl;
	if(hand == 0)//premiere main
	{
		cout << "___Main 1___" <<  endl;
		if(stand)
			cout<<"\nL'IA prefere rester !"<<endl;
		else if(hit)
			cout<<"\n L'IA choisi de tirer une carte "<<endl;
		else if(Double)
			cout<<"\n L'IA choisi de doubler sa mise "<<endl;
		else if(split)
			cout<<"\n L'IA partage sa main"<<endl;
		else if(quit)
			cout<<"\n L'IA quitte le jeux"<<endl;
		else if(surrender)
			cout<<"\n L'IA choisi d'abbandoner le tour pour plus de securité"<<endl;

	}
	else
	{
		cout << "\n___Main 2___\n" <<  endl;
				if(stand)
					cout<<"\nL'IA prefere rester !"<<endl;
				else if(hit)
					cout<<"\n L'IA choisi de tirer une carte "<<endl;
				else if(Double)
					cout<<"\n L'IA choisi de doubler sa mise "<<endl;
				else if(split)
					cout<<"\n L'IA partage sa main"<<endl;
				else if(quit)
					cout<<"\n L'IA quitte le jeux"<<endl;
				else if(surrender)
					cout<<"\n L'IA choisi d'abbandoner le tour pour plus de securité"<<endl;
	}
}

void AI::balanceState(Player & ia)
{
	cout << "##################################################" << endl << endl;
	cout<<"Nouveau solde :\t$"<<ia.getBalance()<<endl<<endl;
}









