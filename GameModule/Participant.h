/**
 * Classe Participant. Classe abstraite.
 * @author Christophe HUBERT
 */

#ifndef _PARTICIPANT_H
#define _PARTICIPANT_H

class Participant
{
protected:
	long balance;  /**< Entier long. Solde du participant. */

public:

	/**
	 * Méthode diminuant le solde de la valeur donnée en paramètre.
	 * @param i valeur à soustraire du solde.
	 */
	void decreaseBalance(int i);

	/**
	 * Getteur de l'attribut balance. Solde du participant.
	 * @return Entier long solde.
	 */
	long getBalance() { return this->balance; }

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
	virtual ~Participant();

	/**
	 * Setteur de l'attribut balance.
	 * @param b Nouveau solde du participant
	 */
	void setBalance(long b) { this->balance = b; }

protected:

	/**
	 * Constructeur.
	 * @param b solde (balance) initial du joueur.
	 */
	Participant(int b);

};

#endif
