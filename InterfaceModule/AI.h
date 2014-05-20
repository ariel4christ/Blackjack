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

class AI {
public:
	AI();

	~AI();

	/**
	 * Methode permettant d'afficher le solde et la mise de l'ia
	 */
	void stateBalanceBet(Player& ia,int bet);
	void insurrance(int val);
	void stateCards(Player& ia);
	void choice(int hand,bool hit, bool stand, bool Double, bool split,bool quit,bool surrender);
	void balanceState(Player& ia);
	void endRound(Player &ia);
	void EnterGame(int id);
	void startRound();
	void endGame();
	void nextRound();

    static void center_output(std::string str, int num_cols);
};

#endif /* AI_H_ */
