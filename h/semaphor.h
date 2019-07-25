/*
 * semaphor.h
 *
 *  Created on: Aug 21, 2017
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

typedef unsigned int Time;

class Kernels;

class Semaphore {
public:
	Semaphore(int init = 1);
	virtual ~Semaphore();

	virtual int wait(int MaxBtime);
	virtual void signal();

	int val() const;
private:
	Kernels* myksem;
};

#endif /* SEMAPHOR_H_ */
