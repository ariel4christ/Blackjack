/**
 *  Classe Card.
 * @author Christophe HUBERT
 */

#ifndef _CARD_H
#define _CARD_H

/**
 *  Enumeration des types de carte.
 */
enum EType
{
	NaN = 0, AS = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

class Card
{
private:
	int id; /**< Entier. Identifiant de la carte. */
	static int sId; /**< Entier statique. Variable utilis�e pour d�terminer l'id d'une carte. */
	EType type; /**< EType. Type de la carte. */

public:

	/**
	 * Constructeur.
	 * @param t type de la carte � cr�er.
	 */
	Card(EType t);

	/**
	 * Destructeur.
	 */
	~Card();

	/**
	 * Constructeur par recopie.
	 */
	Card(const Card& c);

	/**
	 * Surcharge de l'operateur =.
	 */
	Card& operator=(Card& c);

	/**
	 * Getteur de hand.
	 * @return Entier.
	 */
	inline int getId()
	{
		return id;
	}

	/**
	 * M�thode retournant la valeur de la carte.
	 * @return Entier Valeur de la carte.
	 */
	int getValue();

	/**
	 * M�thode retournant le type la carte.
	 * @return EType Type de la carte.
	 */
	EType getType();

	/**
	 * Retourne une repr�sentation de la carte sur quelques caract�res	 * @return la r�pr�sentation
	 */
	const char* getStringRepresentation();

	void setType(EType t)
	{
		this->type = t;
	}
};

#endif
