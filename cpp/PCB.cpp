/*
 * PCB.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: OS1
 */

#include "PCB.h"
#include "PCBl.h"
#include "Foos.h"
#include "SCHEDULE.H"
#include <dos.h>
#include "Kernels.h"
#include "Blockeds.h"

Blockeds* PCB::globalblist = new Blockeds();

PCBl* PCB::alive=new PCBl();

PCB* PCB::running = 0;
PCB* PCB::idle = 0;
PCB* PCB::mn = 0;


PCB::PCB(Time timeSlice) {
	myThread = 0;
	started = 0;
	ready = 1;
	blocked = 0;
	finished = 0;
	quant = timeSlice;
	id = 0;
	mysem = 0;
	waitflag = 0;
	mainflag=1;
	blockedl = new PCBl();
}

PCB::PCB(StackSize stackSize, Time timeSlice) {
	stsize = stackSize;
	//stsize = stsize / sizeof(unsigned);
	if (stsize > 65530)
		stsize = 65530;
	stack = new unsigned[stsize];
	myThread = 0; // prosledjivanje threada koji je pokrenuo(KORISTIS *this u PCB konstr argumentima)
#ifndef BCC_BLOCK_IGNORE
			stack[stackSize - 3] = 0x200; // omogucuje prekide PSW
			stack[stackSize - 4] = FP_SEG(PCB::wrapper);
			stack[stackSize - 5] = FP_OFF(PCB::wrapper);
			ss = FP_SEG(stack + stackSize - 14);
			sp = FP_OFF(stack + stackSize - 14);
#endif
	bp = sp;
	started = 0;
	ready = 1;
	blocked = 0;
	finished = 0;
	quant = timeSlice;
	id = 0;
	blockedl = new PCBl();
	mysem = 0;
	mainflag=0;
	waitflag = 0;
}

PCB::~PCB() {
	lockFlag=0;
	if(mainflag!=1)
	delete[] stack;
	delete blockedl;
	myThread = 0; // pazi na pokazivace
	lockFlag=1;
}

void PCB::wrapper() {
	running->myThread->run();
	PCB* aux = 0;
	lockFlag = 0;
	while (!running->blockedl->empty()) {
		aux = running->blockedl->popPCB();
		aux->blocked = 0;
		Scheduler::put(aux);
	}
	lockFlag = 1;
	aux = 0; // za svaki slucaj, ko zna gde moze viseci
	running->finished = 1;
	dispatch();
}

