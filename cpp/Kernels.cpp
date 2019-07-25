/*
 * Kernels.cpp
 *
 *  Created on: Aug 21, 2017
 *      Author: OS1
 */

#include "Kernels.h"
#include "Blockeds.h"
#include "Foos.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "Slist.h"
#include "Bins.h"
#include <stdio.h>

static int sem_ID = 0;

Kernels::Kernels(int init) {
	lock;
	Svalue = init;
	SemId = ++sem_ID;
	blist = new Bins();
	unlock;
}

Kernels::~Kernels() {
	while (Svalue < 0)
		signal();
	delete blist;
}

int Kernels::wait(int timee) {
	lock;
	Svalue--;
	if (Svalue < 0) {
		blist->addinS(PCB::running);
		PCB::globalblist->addS(PCB::running, timee);
		PCB::running->mysem = this;
		PCB::running->blocked = 1;
		//printf("Idniti: %d\n", PCB::running->retid());
		unlock;
		dispatch();
	} else {
		PCB::running->waitflag = 1;
	unlock; }
	return PCB::running->waitflag;

}

void Kernels::signal() {
	lock;
	Svalue++;
	if (Svalue < 1) {

		PCB* auxP = blist->popS();
		PCB::globalblist->popoutS(auxP);
		//printf("Odblok se%d", auxP->retid());
		auxP->blocked = 0;
		auxP->waitflag = 1;
		//printf("idesignal\n");
		Scheduler::put(auxP);
	}
	unlock;
}

int Kernels::value() {

	return Svalue;
}
