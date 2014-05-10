/**
 * Classe AIGame.
 * @autor Ariel NONO
 */

#ifndef _AIGAME_H
#define _AIGAME_H

#include <vector>
#include <math.h>
#include <string>
#include <stdexcept>
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include "../GameModule/Player.h"
#include "../CommunicationModule/PlayerCommunication.h"
#include "../InterfaceModule/AI.h"

class AIGame
{
public:

	AIGame();
	virtual ~AIGame();
	void runGame();

private:

	int betMin;  /**< Entier. Mise minimale.*/
	int betMax;  /**< Entier. Mise maximale.*/
	std::vector<int> previousBets; /**< vector<int>. Liste des differentes mises au cours du jeu par l'IA */
	std::vector<Card> listOfCards; /**< vector<Card>. Liste de toutes les cartes qui on été jouées au cours du jeux */
	Player ia;/**< Player. Joueur IA */
	PlayerCommunication com; /**< PlayerCommunication. Objet permettant la communication entre l'exécutable IA et l'exécutable bank */
	AI aiInterface; /**< AI. Objet permettant l'affichages des differentes étapes de calcul de l'IA */
	Card bankCard; /**< Bank. Objet bankCard permetant d'enregistrer la carte de la banque necessaire pour le calcul des probabilités*/
	std::string message; /**< string. message recu de la banque */

	/**
	 * Permet de quitter le jeu
	 */
	void quitGame();

	/**
	 * Permets de jouer un tour
	 */
	bool runRound();

	/**
	 * Permet de choisir l'action appropriée à faire
	 * @params myhand la main sur laquelle sera appliquée l'action à faire
	 */
	void chooseAction(PlayerHand* myhand);

	/**
	 * Permet de vider la liste des joueurs humains
	 */
	void emptyPlayerList();

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 21
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_21(EType type,PlayerHand* myhand);

	 /**
	  * strategie a adopter si les cartes de l'ia ont une valeur de 20
	  * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	  */
	void strategy_20(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 19
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_19(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 18
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_18(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 17
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_17(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 16
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_16(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 15
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_15(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 14
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_14(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 13
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_13(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 12
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_12(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 11
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_11(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 10
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_10(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 9
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_9(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 8
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_8(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 7
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_7(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 6
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_6(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les cartes de l'ia ont une valeur de 5
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_5(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux As
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_A(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 10
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_10_10(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 9
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_9_9(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 8
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_8_8(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 7
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_7_7(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 6
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_6_6(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 5
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_5_5(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 4
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_4_4(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 3
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_3_3(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont deux 2
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_2_2(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 10
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_10(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 9
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_9(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 8
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_8(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 7
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_7(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 6
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_6(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 5
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_5(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 4
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_4(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 3
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_3(EType type,PlayerHand* myhand);

	/**
	 * strategie a adopter si les 2 premières cartes de l'ia sont l'As et le 2
	 * @params type. type de la carte de la banque
	 * @params myhand. main sur laquelle s'applique la strategie
	 */
	void strategy_A_2(EType type,PlayerHand* myhand);

	/**
	 * Methode permettant de trouver la valeur booleene de la main
	 * @params myhand. main pour laquelle on veut trouver la valeur entiere permettant de savoir si c'est la première ou la deuxiemme main
	 */
	int handValue(PlayerHand* myhand);

	/**
	 * Methode permettant de savoir si les cartes d'une main sont presentes dans les combinaisons de cartes spéciales
	 * @params myhand . Main sur laquelle s'applique la verification
	 */
	bool isSpecial(PlayerHand* myhand);

	/**
	 * Methode permettant savoir si deux couple de type de carte sont equivalentes
	 * @params type1a. Premier élement du premier couple de type de carte
	 * @params type1b. Deuxiemme élement du premier couple de type de carte
	 * @params type2a. Premier élement du deuxiemme couple de type de carte
	 * @params type2b. Deuxiemme élement du deuxiemme couple de type de carte
	 */
	bool isEqual(EType type1a,EType type1b,EType type2a,EType type2b);

	/**
	 * Methode permetant de determiner la bonne somme d'argent à miser
	 */
	int getBet();

	/**
	 * Methode permetant d'evaluer une carte selon le systeme Hi-LO
	 * @params type type de carte à base duquel s'effectue le calcul
	 */
	int pointCard(EType type);

	/**
	 * Methode permetant de donner la réelle estimation de l'avantage de l'IA
	 */
	float trueCountCard();

};

#endif
