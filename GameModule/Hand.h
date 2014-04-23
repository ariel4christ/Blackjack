#ifndef _HAND_H
#define _HAND_H
#include "Card.h"

class Hand 
{
protected:
	Card* hand[22];
	int index;

public:
	Hand();
	Hand(Card& c);
	Hand(Hand& h);
	~Hand();

	/*Une main doit-elle créer de nouvelles cartes ou bien juste stocker les adresses vers ls cartes ?*/
	int numberOfCards();
	void addCard(Card& c);
	void deleteHand();
	Card** getCards();
	int getValue1();
	int getValue2();
	bool hasAs();
	bool isMultiValued();
	virtual bool isBlackjack();
	

};

#endif