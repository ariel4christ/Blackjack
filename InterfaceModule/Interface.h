/**
 * Interface.h
 */

#ifndef _INTERFACE_H
#define _INTERFACE_H
#include <iostream>

class Interface
{
	public:
		virtual void printGameState();
		virtual void printMessage();
		virtual void printNewGame();
};

#endif
