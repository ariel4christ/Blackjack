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
	char askAction(bool hit, bool split, bool doubler, bool stay, int secHand);
	int getBet(Player &p);
	bool insurrance(Player &p);
    void PrintGameState(Player &p, bool hit, bool split, bool doubler, bool stay);
    void PrintEndRound(Player &p);
    void PrintEnterGame(int id);
    void PrintMessage(std::string str);

    static void center_output(std::string str, int num_cols);
};

#endif /* HMI_H_ */
