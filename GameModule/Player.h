/**
 * Classe Player. H�rite de la classe Participant.
 * Classe qui va instancier un joueur humain ou un joueur IA.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Hand.h"
#include "Participant.h"

class Player : public Participant
{

private:
	bool blackjack = false;  /**< Bool�en. Vrai si le joueur fait blackjack, faux sinon. */
	bool stand = false;  /**< Bool�en. Vrai si le joueur ne veut plus de carte, faux sinon. */
	bool surrender = false;  /**< Bool�en. Vrai di le joueur abandonne le tour, faux sinon. */
	
protected:
	Hand *hand;  /**< Pointeur vers Hand. Main principale du joueur. */
	Hand *hand2;  /**< Pointeur vers Hand. Seconde main si le joueur s�pare sa main principale. */

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
	 * M�thode cr�ant une nouvelle main. M�thode virtuelle h�rit�e de Participant.
	 * @see Hand::Hand()
	 */
	virtual void newHand();

	/**
	 * M�thode supprimant une main du joueur donn�e en param�tre.
	 * @param h Pointeur vers une main du joueur.
	 * @see Hand::deleteHand()
	 */
	void deleteHand(Hand *h);
};

#endif