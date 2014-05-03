/**
 *  Classe Card.
 */

#ifndef _CARD_H
#define _CARD_H

/**
 *  Enumeration des types de carte.
 */
enum EType { NaN = 0, AS = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

class Card
{
private:
	int id;  /**< Entier. Identifiant de la carte. */
	static int sId;  /**< Entier statique. Variable utilisée pour déterminer l'id d'une carte. */
	EType type;  /**< EType. Type de la carte. */

public:

	/**
	 * Constructeur.
	 * @param t type de la carte à créer.
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
	inline int getId() { return id; }

	/**
	 * Méthode retournant la valeur de la carte.
	 * @return Entier Valeur de la carte.
	 */
	int getValue();

	/**
	 * Méthode retournant le type la carte.
	 * @return EType Type de la carte.
	 */
	EType getType();

	/**
	 * Retourne une représentation de la carte sur quelques caractères
	 * @return la réprésentation
	 */
	const char* getStringRepresentation();

	void setType(EType t) { this->type = t; }
};

#endif