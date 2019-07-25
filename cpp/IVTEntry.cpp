/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <dos.h>
#include "KernelEv.h"
#include "Foos.h"

IVTEntry* IVTEntry::entries[256] = { 0 };

IVTEntry::IVTEntry(int ivtnumm, int callold, foo intrpt) {
	lock;
ivtnum = ivtnumm;
cOld = callold;
#ifndef BCC_BLOCK_IGNORE
oldroutine=getvect(ivtnum);
setvect(ivtnum,intrpt);
#endif
entries[ivtnum] = this;
myevent = 0;
unlock;
}

IVTEntry::~IVTEntry() {
lock;
entries[ivtnum] = 0;
#ifndef BCC_BLOCK_IGNORE
setvect(ivtnum,oldroutine);
#endif
unlock;
}

void IVTEntry::intrptold() {
if (cOld == 1)
oldroutine();
}

void IVTEntry::intrptnew() {
if (myevent != 0)
myevent->signal();
}
