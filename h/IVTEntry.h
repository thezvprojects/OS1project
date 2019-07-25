/*
 * IVTEntry.h
 *
 *  Created on: Aug 28, 2017
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Foos.h"

typedef void interrupt (*foo)(...);


#define PREPAREENTRY(ivtnum,cOld)\
		void interrupt foon##ivtnum(...);\
		IVTEntry newentry##ivtnum(ivtnum,cOld,foon##ivtnum);\
void interrupt foon##ivtnum(...){\
		newentry##ivtnum.intrptold();\
		newentry##ivtnum.intrptnew();\
}

class KernelEv;

class IVTEntry {
	foo oldroutine;
	KernelEv* myevent;
	int ivtnum;
	int cOld;
public:
	static IVTEntry* entries[];
	IVTEntry(int ivtnumm, int callold, foo intrpt);
	virtual ~IVTEntry();
	void intrptold();
	void intrptnew();
	static IVTEntry* get(int ivtnumm) { // >????
		return entries[ivtnumm];
	}
protected:
	friend class KernelEv;
};

#endif /* IVTENTRY_H_ */
