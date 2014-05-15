/**
 * BankInterface.h
 * @author Thomas MAINGUY
 */

#ifndef _BANKINTERFACE_H
#define _BANKINTERFACE_H

#include "../GameModule/Player.h"
#include "../GameModule/Hand.h"
#include "../GameModule/Card.h"
#include "../GameModule/Bank.h"
#include <vector>
#include <iostream>

class BankInterface
{
public:
    void printGameState(std::vector<Player*> &players, Bank &bank);

    /**
     * Fonction centrant la string passée en paramètre, par rappot au nombre de colonnes.
     * @param str String contenant le message.
     * @param int Entier nombre de colonnes.
     */
    static void center_output(std::string str, int num_cols);
};

#endif
