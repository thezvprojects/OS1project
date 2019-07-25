/*
 * IDLThr.h
 *
 *  Created on: Jul 17, 2017
 *      Author: OS1
 */

#ifndef IDLTHR_H_
#define IDLTHR_H_

#include "Thread.h"

class IDLThr: public Thread {
public:
	IDLThr();
	void run();
	virtual ~IDLThr();
protected:
	friend int main(int argc, char* argv[]);
	friend class Thread;
	friend class PCB;
};

#endif /* IDLTHR_H_ */
