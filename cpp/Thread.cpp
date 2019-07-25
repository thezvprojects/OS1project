/*
 * Thread.cpp
 *
 *  Created on: Jun 6, 2017
 *      Author: OS1
 */

#include "Thread.h"
#include "PCBl.h"
#include "PCB.h"
#include "Foos.h"
#include "SCHEDULE.H"
#include <stdio.h>

ID PCB::pos_ID = 0;

Thread::Thread(StackSize stackSize, Time timeSlice) {
	lockFlag = 0;
	myPCB = new PCB(stackSize, timeSlice);
	myPCB->myThread = this;
	myPCB->id = ++PCB::pos_ID;
	if (myPCB->id == 1) {
		PCB::idle = myPCB;
		myPCB->ready = 0;
	}
	if (myPCB->id > 1)
		PCB::alive->addPCB(myPCB); // lista 'zivih'
	lockFlag = 1;
}

Thread::~Thread() {
	lockFlag=0;
	if(myPCB->id>1)
	PCB::alive->popPCB(myPCB->id); // razmisli o waittocomplete ovde
	delete myPCB; // samo da izbaci iz liste i stavi na nulu( treba jos sta?) // delete mypcb
	lockFlag=1;
}
// treba li jos sta brisanja ovde?

void Thread::waitToComplete() {
	lockFlag=0;
	if (this->myPCB->finished != 1) {
		myPCB->blockedl->addPCB(PCB::running);
		PCB::running->blocked = 1;
		lockFlag=1;
		dispatch();
	} else lockFlag=1;
}

void Thread::start() {
	lockFlag=0;
	if (!myPCB->started && myPCB->ready) {
		myPCB->started = 1;
		Scheduler::put(myPCB);
	}
	lockFlag=1;
}

ID Thread::getId() {
	return myPCB->id;
}

ID Thread::getRunningId() {
	return PCB::running->retid();
}

Thread* Thread::getThreadById(ID id) {
	lockFlag=0;
	PCB* aux = PCB::alive->getPCB(id);
	lockFlag=1;
	return aux->myThread;

}
