#ifndef _HAND_H
#define _HAND_H
#include "Card.h"
#include <vector>

class Hand 
{
protected:
	std::vector<Card*> cards;

public:
	Hand();
	Hand(Card& c);
	Hand(Hand& h);
	~Hand();

	int numberOfCards();
	int getValue1();
	int getValue2();
	bool isMultiValued();
	bool hasAs();
	virtual bool isBlackjack();  // à redéfinir dans PlayerHand ?

	std::vector<Card*> getCards();
	void addCard(Card& c);
	void deleteHand();
	void setHand(Hand& h);

};

#endif