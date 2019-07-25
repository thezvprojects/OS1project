/*
 * Foos.cpp

 *
 *  Created on: Jul 6, 2017
 *      Author: OS1
 */

#include "Foos.h"
#include "PCB.h"
#include "Thread.h"
#include <dos.h>
#include "SCHEDULE.H"
#include "PCBl.h"
#include <iostream.h>
#include <stdio.h>
#include "Blockeds.h"
#include "Slist.h"
#include "Kernels.h"
#include "Bins.h"

typedef unsigned int REG;

REG oldTimerSEG, oldTimerOFF;

void tick();
volatile unsigned tbp;
volatile unsigned tss;
volatile unsigned tsp;
volatile unsigned count = 0;
volatile unsigned requested_context_change = 0;
volatile int lockFlag = 1;

void dispatch() {
	//lockFlag = 0;
	//printf("Pocetak disp\n"); //cout << "pocetak disp" << endl;
	//lockFlag = 1;
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	requested_context_change=1;
	timer();
	asm sti;
#endif
}

void interrupt timer() {
#ifndef BCC_BLOCK_IGNORE
	asm cli
	if (!requested_context_change) asm int 60h
#endif
	if (!requested_context_change)
		tick();
	//printf("Pocetak timera %d\n",count); //cout << "pocetak timera" << endl;

	if (!requested_context_change && count != 0) {
		count--;
		//printf("count =%d\n", count);
		PCB::globalblist->timerblist();
	}

	if ((count == 0 && PCB::running->quant > 0) || requested_context_change) {
		if (lockFlag == 1) {
			lockFlag = 0;
			requested_context_change = 0;
#ifndef BCC_BLOCK_IGNORE
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
#endif
			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;

			if (!PCB::running->finished && !PCB::running->blocked && PCB::running->ready) {
				Scheduler::put(PCB::running);

				// printf("Stigao put\n"); //cout << "stigo sam put" << endl;

			}

			// printf("Stigao sam ovde\n"); //cout << "stigo sam ovde" << endl;

			if (!(PCB::running = Scheduler::get())) {

				// if (alive->empty())
				PCB::running = PCB::idle;

				//printf("Upao u idle\n"); //cout << "upo u idle" << endl;

				/*running = mn;
				 lockFlag = 0;
				 cout << "upo u main" << endl;
				 lockFlag = 1; */

			}
			//printf("Stigao %d\n", Thread::getRunningId()); //cout << "stigo2" << endl;

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			count = PCB::running->quant;
#ifndef BCC_BLOCK_IGNORE
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
#endif
		} else
			requested_context_change = 1;
	}
	tick();
	lockFlag = 1;
#ifndef BCC_BLOCK_IGNORE
	asm sti
#endif
}

void idlewhile() {
	while (1)
		;
}

void inic() {
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h//; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer//postavlja
		mov word ptr es:0020h, offset timer//novu rutinu

		mov ax, oldTimerSEG//	postavlja staru rutinu
		mov word ptr es:0182h, ax//; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif
}

void restore() {
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}
