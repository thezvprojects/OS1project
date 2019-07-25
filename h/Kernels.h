/*
 * Kernels.h
 *
 *  Created on: Aug 21, 2017
 *      Author: OS1
 */

#ifndef KERNELS_H_
#define KERNELS_H_

class Bins;

class Kernels {
public:
	Kernels(int init);
	virtual ~Kernels();
	int wait(int b);
	void signal();
	int value();
private:
	int Svalue;
	int SemId;
	Bins* blist;
protected:
	friend class Semaphore;
	friend class Slist;
	friend void interrupt timer();
	friend class Blockeds;
};

#endif /* KERNELS_H_ */
