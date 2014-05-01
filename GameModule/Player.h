/**
 * Classe Player. Hérite de la classe Participant.
 * Classe qui va instancier un joueur humain ou un joueur IA.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Hand.h"
#include "Participant.h"

class Player : public Participant
{

private:
	bool blackjack = false;  /**< Booléen. Vrai si le joueur fait blackjack, faux sinon. */
	bool stand = false;  /**< Booléen. Vrai si le joueur ne veut plus de carte, faux sinon. */
	bool surrender = false;  /**< Booléen. Vrai di le joueur abandonne le tour, faux sinon. */
	
protected:
	Hand *hand;  /**< Pointeur vers Hand. Main principale du joueur. */
	Hand *hand2;  /**< Pointeur vers Hand. Seconde main si le joueur sépare sa main principale. */

public:

	/**
	 * Constructeur.
	 * @param i Identifiant du joueur.
	 * @param pBalance Solde initial du joueur.
	 */
	Player(int i, int pBalance);

	/**
	 * Destructeur. Destruction des mains et des cartes.
	 * @see Hand::deleteHand()
	 * @see Hand::~Hand()
	 */
	~Player();

	/**
	 * Méthode créant une nouvelle main. Méthode virtuelle héritée de Participant.
	 * @see Hand::Hand()
	 */
	virtual void newHand();

	/**
	 * Méthode supprimant une main du joueur donnée en paramètre.
	 * @param h Pointeur vers une main du joueur.
	 * @see Hand::deleteHand()
	 */
	void deleteHand(Hand *h);
};

#endif