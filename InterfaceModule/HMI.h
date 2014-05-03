/*
 * HMI.h
 */

#ifndef HMI_H_
#define HMI_H_
#include "Interface.h"
#include "../GameModule/Player.h"
#include "../GameModule/Hand.h"
#include "../GameModule/Card.h"

class HMI : public Interface {

public:
	char askAction(bool hit, bool split, bool doubler, bool stay);
	int getBet();
	bool insurrance();
    void PrintGameState(Player &p, bool hit, bool split, bool doubler, bool stay);
};

#endif /* HMI_H_ */
