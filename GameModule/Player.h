/**
 * Classe Player. Hérite de la classe Participant.
 * Classe qui va instancier un joueur humain ou un joueur IA.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "PlayerHand.h"
#include "Participant.h"
#include <stdexcept>

class Player : public Participant
{

private:
	int id;  /**< Entier. Identifiant du joueur. */
	bool blackjack ;  /**< Booléen. Vrai si le joueur fait blackjack, faux sinon. */
	bool insurance;  /**< Booléen. Vrai si le joueur a pris une assurance, faux sinon. */
	bool surrender ;  /**< Booléen. Vrai di le joueur a abandonné ses deux main, faux sinon. */

protected:
	PlayerHand *hand;  /**< Pointeur vers Hand. Main principale du joueur. */
	PlayerHand *hand2;  /**< Pointeur vers Hand. Seconde main si le joueur sépare sa main principale. */

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
	* Getteur de hand.
	* @return Entier id du joueur.
	*/
	inline int getId() { return id; }

	/**
	 * Méthode créant une nouvelle main. Méthode virtuelle héritée de Participant.
	 * @see Hand::Hand()
	 */
	virtual void newHand();

	/**
	* Méthode créant une nouvelle main avec une mise en paramètre.
	* @see Hand::Hand(int i)
	* @param i	Mise de la main.
	*/
	void newHand(int i);

	/**
	 * Méthode supprimant une main du joueur donnée en paramétre.
	 * @param h Pointeur vers une main du joueur.
	 * @see Hand::deleteHand()
	 */
	void deleteHand(Hand *h);

	/**
	 * Méthode qui appelle PlayerHand::setStand() sur la main en paramétre.
	 * Lance une exception si la main en paramétre n'est pas une du joueur.
	 * @see PlayerHand::setStand()
	 * @param h Pointeur vers la main "servie".
	 */
	void Stand(PlayerHand *h);

	/**
	 * Méthode qui effectue l'action d'abandonner la main donnée en paramétre. Le solde du joueur est augmentée de la moitié de la mise.
	 * La main en paramétre est désallouée. Lance une exception si la main en paramétre n'est pas une du joueur.
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
	inline PlayerHand* getHand() { return this->hand;  }

	/**
	* Getteur de hand2.
	* @return Pointeur vers hand2.
	*/
	inline PlayerHand* getHand2() { return this->hand2; }

	/**
	 * Méthode qui retourne VRAI si le joueur a pris une assurance, FAUX sinon.
	 * @return Booleen.
	 */
	inline bool hasInsurance() { return this->insurance; }

	/**
	 * Setteur de l'attribut inssurance.
	 * @param b Booleen valeur de insurance.
	 */
	inline void setInsurance(bool b) { this->insurance = b; }
};

#endif
