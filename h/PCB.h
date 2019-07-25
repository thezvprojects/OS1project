#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"
class PCBl;

class Kernels;

class Blockeds;

class PCB {
public:
	PCB(StackSize stackSize, Time timeSlice);
	PCB(Time timeSlice);
	virtual ~PCB();
	ID retid() {
		return id;
	}
	static void wrapper(); // static zato sto se koristi u samom konstruktoru
	// void makeidle(PCB* idlePCB, void (*body)());
	void makemain(PCB* mainPCB);
	Kernels getsem();
private:
	unsigned* stack;
	unsigned bp;
	unsigned sp;
	unsigned ss;
	unsigned quant;
	unsigned ready;
	unsigned started; // flegovi, da li su private?
	unsigned finished; // zavrsen
	unsigned blocked; // da li je blokiran, stavljen u red blocked
	PCBl* blockedl;
	Thread* myThread;
	ID id;
	unsigned stsize;
	Kernels* mysem;
	int waitflag;
	int mainflag;
	static PCB* running; // running nit, volatile?

	static PCB* idle;

	static PCB* mn;

	static Blockeds* globalblist;

	static PCBl* alive;

	static ID pos_ID;
protected:
	friend class Thread;
	friend void interrupt timer();
	friend int main(int argc, char* argv[]);
	friend class IDLThr;
	friend class UMThr;
	friend class Kernels;
	friend class KernelEv;
	friend class Blockeds;
};

#endif /* PCB_H_ */
