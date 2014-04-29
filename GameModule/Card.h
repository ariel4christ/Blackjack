#ifndef _CARD_H
#define _CARD_H

enum EType { AS = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

class Card 
{	
private:
	int id;
	static int sId;
	EType type;
	
public:
	Card(EType t);
	~Card();
	Card(Card& c);
	Card& operator=(Card& c);

	int getValue();
	EType getType();
};

#endif