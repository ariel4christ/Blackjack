/**
 * BankCommunication.h
 * @author Thomas MAINGUY
 */

#ifndef _BANKCOMMUNICATION_H
#define _BANKCOMMUNICATION_H

#include "../GameModule/Card.h"
#include "../GameModule/Hand.h"
#include "../GameModule/Player.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdexcept>
#include <string>

class BankCommunication
{
public:
	void AskInsurance(int player);
	int CheckFiles();
	void CleanFiles();
	void CreditPlayer(int player, int money);
	void DebitPlayer(int player, int money);
	void EndRound(std::vector<Player*> &p);
	void PlayerEntered(int id_player, std::vector<Player*> &player);
	void HasQuit(int player, std::vector<Player*> &p);
	std::string ReadFile(int id);
	void RoundStart(int id);
	void SendCard(int player, EType t, int secondHand, std::vector<Player*> &p);
	void setBalance(int player, int balance);
	void setBet(int player, int bet);
	void setHand(int player, Hand &h, int secondHand, std::vector<Player*> &p);
	void validStand(int player, int secondHand);
	void validSurrender(int player);
	void validSplit(int player);
	void AskAction(int player, int secondHand);
	void ReceiveAck(std::vector<Player*> &p);
	void ReceiveAck(int i);
};

#endif
