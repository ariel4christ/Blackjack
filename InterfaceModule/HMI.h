/**
 * HMI.h
 * @author Thomas MAINGUY
 * @author Ariel NONO
 */

#ifndef HMI_H_
#define HMI_H_
#include "../GameModule/Player.h"
#include "../GameModule/Hand.h"
#include "../GameModule/Card.h"
#include <iostream>

class HMI
{

public:
	char askAction(bool hit, bool split, bool doubler, bool stay);
	int getBet();
	bool insurrance();
    void PrintGameState(Player &p, bool hit, bool split, bool doubler, bool stay);
    void PrintEndRound(Player &p);
};

#endif /* HMI_H_ */
