/**
 * Classe Bank. Hérite de la classe Participant.
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
	 * Méthode créant une nouvelle main. Méthode virtuelle héritée de Participant.
	 * @see Hand::Hand()
	 */
	virtual void newHand();

	/**
	 * Méthode supprimant la main de la banque.
	 * @see Hand::deleteHand()
	 */
	void deleteHand();

	inline Hand* getHand() { return hand; }
};

#endif