/*
 * Foos.h
 *
 *  Created on: Jul 6, 2017
 *      Author: OS1
 */

#ifndef FOOS_H_
#define FOOS_H_

#include "PCBl.h"
#include "Thread.h"
#include <dos.h>

#define lock asm { pushf; cli;}

#define unlock asm { popf; } // je l treba u header?

class PCB;

class Blockeds;

class Slist;

class Bins;

//extern PCBl* alive;

//extern PCB* running; // running nit, volatile?

//extern PCB* idle;

//extern PCB* mn;

//extern Blockeds* globalblist;

//extern Bins* blockedinsem;

volatile extern unsigned tsp;
volatile extern unsigned tss;
volatile extern unsigned tbp;
volatile extern unsigned count;
volatile extern unsigned requested_context_change;
volatile extern int lockFlag;

void interrupt timer();

void idlewhile();

void inic();

void restore();

#endif /* FOOS_H_ */
