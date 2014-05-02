/**
 * Classe Player. Hérite de la classe Participant.
 * Classe qui va instancier un joueur humain ou un joueur IA.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "PlayerHand.h"
#include "Participant.h"

class Player : public Participant
{

private:
	bool blackjack = false;  /**< Booléen. Vrai si le joueur fait blackjack, faux sinon. */
	bool surrender = false;  /**< Booléen. Vrai di le joueur a abandonné ses deux main, faux sinon. */
	
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

	/**
	 * Méthode qui appelle PlayerHand::setStand() sur la main en paramètre.
	 * Lance une exception si la main en paramètre n'est pas une du joueur.
	 * @see PlayerHand::setStand()
	 * @param h Pointeur vers la main "servie".
	 */
	void Stand(PlayerHand *h);

	/**
	 * Méthode qui effectue l'action d'abandonner la main donnée en paramètre. Le solde du joueur est augmentée de la moitié de la mise.
	 * La main en paramètre est désallouée. Lance une exception si la main en paramètre n'est pas une du joueur.
	 * Surrender est FAUX tant que le joueur a une main en jeu.
	 * @see increaseBalance()
	 * @see Hand::deleteHand()
	 * @see setSurrender()
	 * @param h Pointeur vers la main abandonnée.
	 */
	void Surrender(PlayerHand *h);

	/**
	 * Getteur de blackjack.
	 * @return Booléen.
	 */
	bool getBlackjack();

	/**
	 * Setteur de blackjack.
	 * @param b Nouvelle valeur de blackjack.
	 */
	void setBlackjack(bool b);
	
	/**
	* Getteur de surrender.
	* @return Booléen.
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