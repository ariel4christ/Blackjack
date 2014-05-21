/**
 * Classe Hand. Main d'un participant : joueur ou banque.
 * @author Christophe HUBERT
 */

#ifndef _HAND_H
#define _HAND_H
#include "Card.h"
#include <vector>
#include <stdexcept>

class Hand
{
protected:
	std::vector<Card*> cards; /**< Vecteur de pointeurs vers Card. Cartes constituant la main. */

public:

	/**
	 * Constructeur par d�faut.
	 * La main est vide.
	 */
	Hand();

	/**
	 * Constructeur. La nouvelle main contient la carte donn�e en param�tre.
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
	 * M�thode retournant le nombre de cartes de la main.
	 * @return Entier Nombre de cartes de l'attribut cards.
	 */
	int numberOfCards();

	/**
	 * M�thode retournant la valeur basse de la main. Les As vallent 1.
	 * @return Entier Valeur basse de la main.
	 */
	int getValue1();

	/**
	 * M�thode retournant la valeur haute de la main, si elle existe. Le 1er As vaut 11, les autres vallent 1.
	 * Si la main n'a qu'une seule valeur (elle n'a pas d'AS), retourne getValue1().
	 * @see isMultiValued()
	 * @see getValue1()
	 * @return Entier Valeur haute de la main.
	 */
	int getValue2();

	/**
	 * M�thode qui retourne le vecteur de pointeurs de cartes de la main
	 * @return vector<Card*>& Cartes de la main.
	 */
	std::vector<Card*>& getCards();

	/**
	 * M�thode qui retourne la i�me carte de la main.
	 * Lance une exception si i fait r�f�rence � une carte en dehors du vecteur de carte.
	 * @return Card* Pointeur vers la i�me carte de la main.
	 */
	Card* getCard(unsigned int i);

	/**
	 * M�thode qui ajoute la carte en param�tre � la liste des ca
	 * Lance une exception si la main contient d�j� 22 cartes.
	 * @see Hand::numberOfCards()
	 * @param c Pointeur vers la carte � ajouter � la main.
	 */
	void addCard(Card *c);

	/**
	 * M�thode retournant VRAI si la main a deux valeurs <= 21, et FAUX sinon.
	 * (i.e. VRAI si la main a un As qui peut avoir pour valeur 11 sans que la valeur totale de la main ne d�passe 21).
	 * @see Card::getType()
	 * @see getValue1()
	 * @return Bool�en.
	 */
	bool isMultiValued();

	/**
	 * M�thode retournant VRAI s'il y a un As dans la main. FAUX sinon.
	 * @see Card::getType()
	 * @return Bool�en.
	 */
	bool hasAs();

	/**
	 * M�thode retournant VRAI si la main a une configuration de blackjack. FAUX sinon.
	 * @return Bool�en.
	 */
	bool isBlackjack();

	/**
	 * M�thode retournant VRAI si les deux premi�res cartes de la main ont le m�me EType. Retourne FAUX sinon.
	 * @see Card::getType()
	 * @return Bool�en.
	 */
	bool isPair();

	/**
	 * M�thode qui les cartes qu'elle contient.
	 * Il faut absolument appeler delete apr�s l'appel de cette fonction!
	 */
	void deleteHand();

	/**
	 * M�thode qui d�salloue les cartes de la main courante et copie les pointeurs de cartes de la main h vers la main courante.
	 * La main h en param�tre n'est pas modifi�e.
	 * @param h Hand.
	 */
	void setHand(const Hand& h);

	/**
	 * M�thode qui d�salloue les cartes de la main courante et remplace les cartes par celles du pointeur en param�tre.
	 * @param h Pointeur vers la nouvelle main.
	 */
	void setHand(Hand* h);

	/**
	 * M�thode qui transf�re le 2eme carte de la main courante vers la main en param�tre.
	 * Ne fonctionne que s'il n'y a que 2 cartes dans la main. Lance une exception sinon.
	 * @see addCard()
	 * @param h Hand (main) o� on ajoute le pointeur de la 2eme carte.
	 */
	void trandferSecondCard(Hand *h);

};

#endif
