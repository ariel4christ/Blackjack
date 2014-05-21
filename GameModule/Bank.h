/**
 * Classe Bank. H�rite de la classe Participant.
 * @author Christophe HUBERT
 */

#ifndef _BANK_H
#define _BANK_H
#include "Participant.h"
#include "Hand.h"
#include <stdexcept>

class Bank: public Participant
{
private:
	Hand *hand; /**< Pointeur vers Hand. Main de la banque. */
	Card *hiddenCard;

public:

	/**
	 * Constructeur.
	 * La banque a id = 0.
	 * @see Participant(int i, int b)
	 * @param bankBalance Solde initial de la banque.
	 */
	Bank(int bankBalance);

	/**
	 * Destructeur.
	 * @see Hand::deleteHand()
	 */
	~Bank();

	/**
	 * M�thode cr�ant une nouvelle main. M�thode virtuelle h�rit�e de Participant.
	 * @see Hand::Hand()
	 */
	virtual void newHand();

	/**
	 * M�thode supprimant la main de la banque.
	 * @see Hand::deleteHand()
	 */
	void deleteHand();

	bool isBankBlackjack();

	inline Hand* getHand()
	{
		return hand;
	}
	inline Card* getHiddenCard()
	{
		return this->hiddenCard;
	}

	inline void setHand(Hand *h)
	{
		this->deleteHand();
		this->hand = h;
	}
	inline void setHiddenCard(Card* c)
	{
		this->hiddenCard = c;
	}
};

#endif
