/*
 * AI.h
 */

#ifndef AI_H_
#define AI_H_

#include <iostream>

class AI {
public:
	AI();

	~AI();

	/**
	 * Methode permettant d'afficher la mise de l'ia
	 */
	void IaBet(int bet);

	bool insurrance(int val);
};

#endif /* AI_H_ */
