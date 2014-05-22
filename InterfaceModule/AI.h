/**
 * AI.h
 * @author Ariel NONO
 * @author Ali SIF
 */

#ifndef AI_H_
#define AI_H_

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "../GameModule/Player.h"
#include "../GameModule/Card.h"

class AI
{
public:
	AI();

	~AI();

	/**
	 * Methode permettant d'afficher le solde et la mise de l'ia.
	 * @param ia	Joueur pour lequel l'action s'applique
	 * @param bet	Mise du joueur
	 */
	void stateBalanceBet(Player& ia, int bet);
	
	/**
	 * Affiche le choix de l'IA concernant la prise d'assurance.
	 * @param val Entier 1 si l'IA prend l'assurance et 0 sinon
	 */
	void insurrance(int val);
	
	/**
	 * Affiche la (les) main du joueur.
	 * @param ia IA pour laquelle on affiche sa (ses) main
	 */
	void stateCards(Player& ia);
	
	/**
	 * Affiche l'action effectuée par l'IA sur un main en fonction de l'entier hand passé en paramètre.
	 * @param	hand		0 si l'action est sur la main 1, et 1 si sur la main 2
	 * @param	hit		VRAI si l'IA a tiré une carte, FAUX sinon
	 * @param	stand		VRAI si l'IA garde sa main telle quelle, FAUX sinon
	 * @param	Double		VRAI si l'IA a tiré une carte, FAUX sinon
	 * @param	split		VRAI si l'IA a séparé sa main en deux, FAUX sinon
	 * @param	quit		VRAI si l'IA a quitté le jeu, FAUX sinon
	 * @param	surrender	VRAI si l'IA a abandonnée la main, FAUX sinon
	 */
	void choice(int hand, bool hit, bool stand, bool Double, bool split, bool quit, bool surrender);
	
	/**
	 * Affiche le solde de l'IA.
	 * @param ia Joueur pour lequel l'action s'applique
	 */
	void balanceState(Player& ia);
	
	/**
	 * Affiche la fin du tour.
	 * @param ia	Joueur pour lequel l'action s'applique
	 */
	void endRound(Player &ia);
	
	/**
	 * Affichage du début de jeu.
	 * @param id	Entier identifiant du joueur
	 */
	void EnterGame(int id);
	
	/**
	 * Affichage de début de tour.
	 */
	void startRound();
	
	/**
	 * Affichage de fin de jeu.
	 */
	void endGame();
	
	/**
	 * Méthode demandant à l'utilisateur d'appuiller sur Entrée s'il a choisi le mode IA interactif.
	 */
	void nextRound();

	/**
	 * Fonction centrant la string passée en paramètre, par rappot au nombre de colonnes.
	 * @param str String contenant le message.
	 * @param int Entier nombre de colonnes.
	 */
	static void center_output(std::string str, int num_cols);
};

#endif /* AI_H_ */
