/**
 * AI.cpp
 * @author Ariel NONO
 * @author Ali SIF
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
	cout << endl <<  "##################################################" << endl << endl;
	if(!value)
		cout << "> L'IA ne prend pas d'assurance !" << endl << endl;
    else
        cout << "> L'IA prend une assurance !" << endl << endl;
}

void AI::stateCards(Player& ia)
{

	cout << endl << "##################################################" << endl << endl;
	std::vector<Card*>  myCards;

    cout<<"~ Joueur " << ia.getId() << " : IA" << endl;

    // Première main
	if(ia.getHand() != NULL)
	{
        cout << endl << "~ Main 1" << endl << endl;

		myCards = ia.getHand()->getCards();

        cout << "~ Cartes :";

		for (vector<Card*>::iterator it = myCards.begin(); it != myCards.end(); ++it)
	    {
	        cout << " " << (*it)->getStringRepresentation() << " ";
	    }

	    cout << "  Valeur : " << ia.getHand()->getValue2();

	    if (ia.getHand()->getValue2() != ia.getHand()->getValue1())
	        cout << " / " << ia.getHand()->getValue1();

	    cout << endl << endl;
	}

    // Seconde main
    if (ia.getHand2() != NULL)
    {
        cout << "\n ___Main 2___\n" <<  endl;

        std::vector<Card*> myCards2 = ia.getHand2()->getCards();

        for (vector<Card*>::iterator it = myCards2.begin(); it != myCards2.end(); it++)
        {
            cout <<" "<< (*it)->getStringRepresentation() << " ";
        }

        cout << "  Valeur : " << ia.getHand2()->getValue2();

        if (ia.getHand2()->getValue2() != ia.getHand2()->getValue1())
            cout << " / " << ia.getHand2()->getValue1();

        cout << endl << endl;
    }
}

void AI::stateBalanceBet(Player & ia,int bet)
{
	cout << endl << "##################################################" << endl << endl;
    cout << "> Solde de l'IA :\t$ " << ia.getBalance() << endl << endl;
    cout << "> L'IA mise :\t\t$ " << bet << endl << endl;
}

void AI::choice(int hand,bool hit, bool stand, bool Double, bool split,bool quit,bool surrender)
{

	cout << endl << "##################################################" << endl << endl;
	if(hand == 0)//premiere main
	{
		cout << " ___Main 1___" <<  endl;
		if(stand)
			cout << "\n L'IA préfère rester !" << endl;
		else if(hit)
			cout << "\n L'IA choisit de tirer une carte " << endl;
		else if(Double)
			cout << "\n L'IA choisit de doubler sa mise " << endl;
		else if(split)
			cout << "\n L'IA partage sa main" << endl;
		else if(quit)
			cout << "\n L'IA quitte le jeu" << endl;
		else if(surrender)
			cout << "\n L'IA choisit d'abandonner le tour pour plus de securité" << endl;

	}
	else
	{
		cout << "___Main 2___" <<  endl;
				if(stand)
					cout << "\n L'IA prefere rester !" << endl;
				else if(hit)
					cout << "\n L'IA choisit de tirer une carte" << endl;
				else if(Double)
					cout << "\n L'IA choisit de doubler sa mise" << endl;
				else if(split)
					cout << "\n L'IA partage sa main" << endl;
				else if(quit)
					cout << "\n L'IA quitte le jeu" << endl;
				else if(surrender)
					cout << "\n L'IA choisit d'abandonner le tour pour plus de securité" << endl;
	}
}

void AI::balanceState(Player & ia)
{
	cout << endl << "##################################################" << endl << endl;
	cout << "~ Nouveau solde :\t$" << ia.getBalance() << endl << endl;
}

// numb_cols = nombre de colonnes dans la console.
// Je prends toujours 50.
void AI::center_output(std::string str, int num_cols)
{
    // Calculate left padding
    int padding_left = (num_cols / 2) - (str.size() / 2);

    // Put padding spaces
    for(int i = 0; i < padding_left; ++i) cout << ' ';

    // Print the message
    cout << str << endl;
}

void AI::endRound(Player &ia)
{
	cout << endl << "##################################################" << endl << endl;
    cout << "Fin de Tour. Les résultats sont affichés dans la Banque." << endl;
    cout << "Nouveau solde : $ " << ia.getBalance() << endl << endl;
	cout << "##################################################" << endl << endl;

}

void AI::startRound()
{
	cout << endl << endl << "##################################################" << endl << endl;
    center_output("*** Nouveau Tour ***",50);


}
void AI::EnterGame(int id)
{
    system("clear");
    cout << "##################################################" << endl << endl;
    center_output("******* Blackjack *******", 50);
    cout << endl;
    center_output("*** IA ***", 50);
    cout << endl <<"~ Son nom est : Joueur " << id << endl << endl;
    cout << "##################################################" << endl << endl;
}

void AI::endGame()
{
	cout << endl << "##################################################" << endl << endl;
	center_output("L'IA quitte le Jeu !",50);
	cout << endl << "##################################################" << endl << endl;

}

void AI::nextRound()
{
	cout << endl << endl << "> Appuyez sur Entrée pour passer au prochain tour... ";
}






