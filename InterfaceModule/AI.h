/*
 * AI.h
 */

#ifndef AI_H_
#define AI_H_
#include "Interface.h"

class AI : public Interface {
public:
	AI();
	virtual ~AI();
	int getBet();
	bool insurrance();
};

#endif /* AI_H_ */
