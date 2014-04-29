#ifndef _HAND_H
#define _HAND_H
#include "Card.h"
#include <vector>

class Hand 
{
protected:
	std::vector<Card*> hand;

public:
	Hand();
	Hand(Card& c);
	Hand(Hand& h);
	~Hand();

	int numberOfCards();
	void addCard(Card& c);
	void deleteHand();
	std::vector<Card*> getCards();
	int getValue1();
	int getValue2();
	bool hasAs();
	bool isMultiValued();
	virtual bool isBlackjack();
	

};

#endif