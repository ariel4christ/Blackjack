/**
 * Classe Hand. Main d'un participant : joueur ou banque.
 */

#ifndef _HAND_H
#define _HAND_H
#include "Card.h"
#include <vector>
#include <stdexcept>

class Hand
{
protected:
	std::vector<Card*> cards;  /**< Vecteur de pointeurs vers Card. Cartes constituant la main. */

public:

	/**
	 * Constructeur par défaut.
	 * La main est vide.
	 */
	Hand();

	/**
	 * Constructeur. La nouvelle main contient la carte donnée en paramètre.
	 * @param c Pointeur vers la 1ere carte de la nouvelle main.
	 */
	Hand(Card& c);

	/**
	 * Constructeur par recopie de main.
	 * @param h Hand
	 */
	Hand(const Hand &h);

	/**
	 * Destructeur. Ne supprime pas les cartes de la main.
	 * @see deleteHand()
	 */
	~Hand();

	/**
	 * Méthode retournant le nombre de cartes de la main.
	 * @return Entier Nombre de cartes de l'attribut cards.
	 */
	int numberOfCards();

	/**
	 * Méthode retournant la valeur basse de la main. Les As vallent 1.
	 * @return Entier Valeur basse de la main.
	 */
	int getValue1();

	/**
	 * Méthode retournant la valeur haute de la main, si elle existe. Le 1er As vaut 11, les autres vallent 1.
	 * Si la main n'a qu'une seule valeur (elle n'a pas d'AS), retourne getValue1().
	 * @see isMultiValued()
	 * @see getValue1()
	 * @return Entier Valeur haute de la main.
	 */
	int getValue2();

	/**
	 * Méthode qui retourne le vecteur de pointeurs de cartes de la main
	 * @return vector<Card*>& Cartes de la main.
	 */
	std::vector<Card*>& getCards();

	/**
	 * Méthode qui retourne la ième carte de la main.
	 * Lance une exception si i fait référence à une carte en dehors du vecteur de carte.
	 * @return Card* Pointeur vers la ième carte de la main.
	 */
	Card* getCard(unsigned int i);

	/**
	 * Méthode qui ajoute la carte en paramètre à la liste des ca
	 * Lance une exception si la main contient déjà 22 cartes.
	 * @see Hand::numberOfCards()
 	 * @param c Pointeur vers la carte à ajouter à la main.
	 */
	void addCard(Card *c);

	/**
	 * Méthode retournant VRAI si la main a deux valeurs <= 21, et FAUX sinon.
   	 * (i.e. VRAI si la main a un As qui peut avoir pour valeur 11 sans que la valeur totale de la main ne dépasse 21).
	 * @see Card::getType()
	 * @see getValue1()
 	 * @return Booléen.
 	 */
	bool isMultiValued();

	/**
	 * Méthode retournant VRAI s'il y a un As dans la main. FAUX sinon.
	 * @see Card::getType()
	 * @return Booléen.
	 */
	bool hasAs();

	/**
	 * Méthode retournant VRAI si la main a une configuration de blackjack. FAUX sinon.
	 * @return Booléen.
	 */
	bool isBlackjack();

	/**
	 * Méthode retournant VRAI si les deux premières cartes de la main ont le même EType. Retourne FAUX sinon.
	 * @see Card::getType()
	 * @return Booléen.
	 */
	bool isPair();


	/**
	 * Méthode qui supprime la main ET les cartes qu'elle contient.
	 * @see ~Hand()
	 */
	void deleteHand();

	/**
	 * Méthode qui désalloue les cartes de la main courante et copie les pointeurs de cartes de la main h vers la main courante.
	 * La main h en paramètre n'est pas modifiée.
	 * @param h Hand.
	 */
	void setHand(const Hand& h);

	/**
	 * Méthode qui transfère le 2eme carte de la main courante vers la main en paramètre.
	 * Ne fonctionne que s'il n'y a que 2 cartes dans la main. Lance une exception sinon.
	 * @see addCard()
	 * @param h Hand (main) où on ajoute le pointeur de la 2eme carte.
	 */
	void trandferSecondCard(Hand *h);

};

#endif
