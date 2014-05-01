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
	* M�thode diminuant le solde de la valeur donn�e en param�tre.
	* @param i valeur � soustraire du solde.
	*/
	void decreaseBalance(int i);

	/**
	* M�thode augmentant le solde de la valeur donn�e en param�tre.
	* @param i valeur � ajouter du solde.
	*/
	void increaseBalance(int i);

	/**
	 * M�thode virtuelle pure.
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