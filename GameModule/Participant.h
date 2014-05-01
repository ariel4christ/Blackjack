/**
* Classe Participant. Classe abstraite
*/

#ifndef _PARTICIPANT_H
#define _PARTICIPANT_H

class Participant
{
protected:
	int id;  /**< Entier. Identifiant du participant. */
	long balance;  /**< Entier long. Solde du participant */

public:

	/**
	* Méthode diminuant le solde de la valeur donnée en paramètre.
	* @param i valeur à soustraire du solde.
	*/
	void decreaseBalance(int i);

	/**
	* Méthode augmentant le solde de la valeur donnée en paramètre.
	* @param i valeur à ajouter du solde.
	*/
	void increaseBalance(int i);

	/**
	 * Méthode virtuelle pure.
	 */
	virtual void newHand()=0;

	/*
	 * Destructeur.
	 */
	~Participant();

protected:

	/**
	 * Constructeur.
	 * @param i identifiant du participant.
	 * @param b solde (balance) initial du joueur.
	 */
	Participant(int i, int b);

};

#endif