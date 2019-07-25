/*
 * Bins.h
 *
 *  Created on: Aug 24, 2017
 *      Author: OS1
 */

#ifndef BINS_H_
#define BINS_H_


class PCB;

class Bins {
	struct Elem {
			PCB* pcb;
			Elem* next;
			Elem(PCB* idd=0,Elem* nextt=0) {
				pcb=idd;
				next=nextt;
			}
		};
		Elem* head;
		Elem* last;
public:
	Bins();
	void addinS(PCB* pcbb);
	PCB* popoutS(PCB* pcbb);
	virtual ~Bins();
	PCB* popS();
};

#endif /* BINS_H_ */
