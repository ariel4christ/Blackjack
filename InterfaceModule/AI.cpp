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
	center_output("\n##################################################\n" ,50);
	if(!value)
		cout<<" L'IA ne prends pas d'assurance !"<<endl<<endl;;
}

void AI::stateCards(Player& ia){

	center_output("\n##################################################\n" ,50);
	std::vector<Card*>  myCards;

	cout<<" Les cartes de l'IA :"<<endl;

	if(ia.getHand() != NULL){
		cout << "\n ___Main 1___\n" <<  endl;
		myCards = ia.getHand()->getCards();

		for (vector<Card*>::iterator it = myCards.begin(); it != myCards.end(); it++)
	    {
	        cout << (*it)->getStringRepresentation() << " ";
	    }
		cout<<""<<endl<<endl;
	    cout << " Valeur : " << ia.getHand()->getValue2();

	    if (ia.getHand()->getValue2() != ia.getHand()->getValue1())
	        cout << " / " << ia.getHand()->getValue1();

	    cout << endl << endl;
	}
	    if (ia.getHand2() != NULL)
	    {
	    	cout << "\n ___Main 2___\n" <<  endl;

			std::vector<Card*> myCards2 = ia.getHand2()->getCards();

		    for (vector<Card*>::iterator it = myCards2.begin(); it != myCards2.end(); it++)
		    {
		        cout << (*it)->getStringRepresentation() << " ";
		    }

		    cout<<""<<endl<<endl;

		    cout << " Valeur : " << ia.getHand2()->getValue2();

		    if (ia.getHand2()->getValue2() != ia.getHand2()->getValue1())
	            cout << " / " << ia.getHand2()->getValue1();

		    cout << endl << endl;
	    }
}

void AI::stateBalanceBet(Player & ia,int bet)
{
    system("clear");
	center_output("\n##################################################\n" ,50);
	cout<< "\n Solde:\t"<<ia.getBalance()<<endl<<endl;
	cout<<" L'IA mise :\t $"<<bet<<endl<<endl;
}

void AI::choice(int hand,bool hit, bool stand, bool Double, bool split,bool quit,bool surrender)
{

	center_output("\n##################################################\n" ,50);
	if(hand == 0)//premiere main
	{
		cout << " ___Main 1___" <<  endl;
		if(stand)
			cout<<"\n L'IA prefere rester !"<<endl;
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
		cout << "\n ___Main 2___\n" <<  endl;
				if(stand)
					cout<<"\n L'IA prefere rester !"<<endl;
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
	center_output("\n##################################################\n" ,50);
	cout<<" Nouveau solde :\t$"<<ia.getBalance()<<endl<<endl;
}

// numb_cols = nombre de colonnes dans la console.
// Je prends toujours 50.
void AI::center_output(std::string str, int num_cols)
{
    // Calculate left padding
    int padding_left = (num_cols / 2) - (str.size() / 2);

    // Put padding spaces
    for(int i = 0; i < padding_left; ++i) std::cout << ' ';

    // Print the message
    std::cout << str << endl;
}

void AI::endRound()
{
	center_output("\n##################################################\n" ,50);
	center_output("Fin de Tour",50);
	center_output("\n##################################################\n" ,50);

}
void AI::EnterGame(int id)
{
    system("clear");
    cout << "##################################################" << endl << endl;
    center_output("******* Blackjack *******", 50);
    cout << endl;
    center_output("*** IA ***", 50);
    cout << endl <<" Son nom est : Joueur " << id << endl << endl;
    cout << "##################################################" << endl << endl;
}


