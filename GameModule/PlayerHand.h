/**
 * Classe PlayerHand. Hérite de la classe Hand. Main d'un joueur.
 * @author Christophe HUBERT
 */

#ifndef _PLAYERHAND_H
#define _PLAYERHAND_H
#include "Hand.h"

class PlayerHand : public Hand
{
protected:
	int bet;  /**< Entier Mise du joueur. */
	bool stand ;  /**< Booléen. Vrai si le joueur ne veut plus de carte pour cette main, faux sinon. */

public:

	/**
	 * Constructeur par défaut.
	 * La main est vide.
	 */
	PlayerHand();

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

	/**
	 * Getteur de l'attribut bet. Retourne bet.
	 * @return Entier Mise de la main.
	 */
	int getBet();

	/**
	 * Setteur de l'attribut bet.
	 * @param bet Nouvelle mise
	 */
	void setBet(int bet);

	/**
	 * Méthode doublant la valeur de l'attribut bet (mise).
	 */
	void doubleBet();

	/**
	 * Getteur de stand.
	 * @return Booléen.
	 */
	bool getStand();

	/**
	 * Setteur de stand.
	 * @param b Nouvelle valeur de stand.
	 */
	void setStand(bool b);
};

#endif
