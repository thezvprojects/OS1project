/*
 * main.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "PCBl.h"
#include "Foos.h"
#include "UMThr.h"
#include "IDLThr.h"
#include <iostream.h>
#include <stdio.h>
#include "semaphor.h"
#include "Kernels.h"
#include "Slist.h"
#include "event.h"
#include "KernelEv.h"
#include "IVTEntry.h"

int returnV;
int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	IDLThr* idlThr = new IDLThr();
	PCB::mn = new PCB(0);
	PCB::running = PCB::mn;
	inic();
	returnV = userMain(argc, argv);
	restore();
	delete idlThr;
	delete PCB::mn;
	delete PCB::alive;
	PCB::running = 0;
	PCB::idle = 0;
	return returnV;

}

