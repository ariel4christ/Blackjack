#ifndef _CARD_H
#define _CARD_H

class Card 
{

	enum EType {AS=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK=10, QUEEN=10, KING=10};
	
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
};

#endif