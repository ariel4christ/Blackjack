/**
 * Classe Bank. H�rite de la classe Participant.
 */

#ifndef _BANK_H
#define _BANK_H
#include "Participant.h"
#include "Hand.h"

class Bank : public Participant
{
private:
	Hand *hand;  /**< Pointeur vers Hand. Main de la banque. */

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

	inline Hand* getHand() { return hand; }
};

#endif