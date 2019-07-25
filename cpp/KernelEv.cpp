/*
 * KernelEv.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: OS1
 */

#include "KernelEv.h"
#include "IVTEntry.h"
#include "PCB.h"
#include "Foos.h"
#include "SCHEDULE.H"
#include <dos.h>
#include <stdio.h>

KernelEv::KernelEv(int ivtnum) {
	lock;
	blck = 0;
	this->ivtnum = ivtnum;
	bsem = 0; // kao bsemafor
	idd = PCB::running->retid();
	IVTEntry* entr = IVTEntry::get(ivtnum);
	if(entr && entr->myevent==0)
	entr->myevent = this;
	unlock;
}

KernelEv::~KernelEv() {
	lock;
	IVTEntry* ent = IVTEntry::get(ivtnum);
	if(blck!=0) signal();
	if(ent && ent->myevent==this)
	ent->myevent = 0;
	delete blck;
	unlock;
}

void KernelEv::wait() {
	lock;
	if (PCB::running->retid() == idd) {
		if (bsem == 1){
			bsem = 0;
			unlock; }
		else {
			PCB::running->blocked = 1;
			blck = PCB::running;
			//printf("waitevent%d\n",idd);
			unlock;
			dispatch();
			//blocked=0;
		}
	} else unlock;
}

void KernelEv::signal() {
	lock;
	if (blck == 0) {
		bsem = 1;
		unlock;
	}
	else {
		blck->blocked = 0;
		Scheduler::put(blck);
		bsem = 0;
		blck=0;
		unlock;

		//printf("signalevent\n");

	}
}

