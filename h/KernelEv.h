/*
 * KernelEv.h
 *
 *  Created on: Aug 28, 2017
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

class PCB;

class KernelEv {
	int ivtnum;
	unsigned int idd;
	PCB* blck;
	int bsem;
public:
	KernelEv(int ivtnum);
	virtual ~KernelEv();
	void wait();
	void signal();
};

#endif /* KERNELEV_H_ */
