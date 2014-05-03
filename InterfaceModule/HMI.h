/*
 * HMI.h
 */

#ifndef HMI_H_
#define HMI_H_
#include "Interface.h"

class HMI : public Interface {

public:
	HMI();
	virtual ~HMI();
	void askAction();
	int getBet();
	void insurrance();
};

#endif /* HMI_H_ */
