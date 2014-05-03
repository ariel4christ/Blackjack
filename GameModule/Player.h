/**
 * Classe Player. H�rite de la classe Participant.
 * Classe qui va instancier un joueur humain ou un joueur IA.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "PlayerHand.h"
#include "Participant.h"

class Player : public Participant
{

private:
	bool blackjack ;  /**< Bool�en. Vrai si le joueur fait blackjack, faux sinon. */
	bool surrender ;  /**< Bool�en. Vrai di le joueur a abandonn� ses deux main, faux sinon. */

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

	/**
	 * M�thode qui appelle PlayerHand::setStand() sur la main en param�tre.
	 * Lance une exception si la main en param�tre n'est pas une du joueur.
	 * @see PlayerHand::setStand()
	 * @param h Pointeur vers la main "servie".
	 */
	void Stand(PlayerHand *h);

	/**
	 * M�thode qui effectue l'action d'abandonner la main donn�e en param�tre. Le solde du joueur est augment�e de la moiti� de la mise.
	 * La main en param�tre est d�sallou�e. Lance une exception si la main en param�tre n'est pas une du joueur.
	 * Surrender est FAUX tant que le joueur a une main en jeu.
	 * @see increaseBalance()
	 * @see Hand::deleteHand()
	 * @see setSurrender()
	 * @param h Pointeur vers la main abandonn�e.
	 */
	void Surrender(PlayerHand *h);

	/**
	 * Getteur de blackjack.
	 * @return Bool�en.
	 */
	bool getBlackjack();

	/**
	 * Setteur de blackjack.
	 * @param b Nouvelle valeur de blackjack.
	 */
	void setBlackjack(bool b);

	/**
	* Getteur de surrender.
	* @return Bool�en.
	*/
	bool getSurrender();

	/**
	* Setteur de surrender.
	* @param b Nouvelle valeur de surrender.
	*/
	void setSurrender(bool b);

	/**
	* Getteur de hand.
	* @return Pointeur vers hand.
	*/
	inline Hand* getHand() { return hand;  }

	/**
	* Getteur de hand2.
	* @return Pointeur vers hand2.
	*/
	inline Hand* getHand2() { return hand2; }
};

#endif
