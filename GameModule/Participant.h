#ifndef _PARTICIPANT_H
#define _PARTICIPANT_H

class Participant
{
protected:
	int id;
	long balance;

public:
	void decreaseBalance(int i);
	void increaseBalance(int i);
	virtual void newHand()=0;

protected:
	Participant(int i, int b);

};

#endif