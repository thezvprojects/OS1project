/*
 * UMThr.h
 *
 *  Created on: Jul 14, 2017
 *      Author: OS1
 */

#ifndef UMTHR_H_
#define UMTHR_H_

#include "Thread.h"

class UMThr: public Thread {
private:
	int argc;
	char** argv;
public:
	UMThr(int argcc, char* argvv[]);
	void run();
	~UMThr();
};

#endif /* UMTHR_H_ */
