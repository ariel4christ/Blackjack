/**
 * Classe PlayerHand. Hérite de la classe Hand. Main d'un joueur.
 */

#ifndef _PLAYERHAND_H
#define _PLAYERHAND_H
#include "Hand.h"

class PlayerHand : public Hand
{
protected:
	int bet;  /**< Entier Mise du joueur. */

public:

	/**
	 * Constructeur.
	 * @see Hand()
	 * @param i Mise.
	 */
	PlayerHand(int i);

	/**
	 * Constructeur.
	 * @see Hand(Card &c)
	 * @param i Mise.
	 */
	PlayerHand(Card &c, int i);

	/**
	 * Constructeur.
	 * @see Hand(const Hand &h)
	 * @param i Mise.
	 */
	PlayerHand(const Hand &h, int i);

	/**
	 * Destructeur. Ne désalloue pas les cartes de la main.
	 * @see ~Hand()
	 * @see deleteHand()
	 */
	~PlayerHand();

};

#endif