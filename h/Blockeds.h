/*
 * Blockeds.h
 *
 *  Created on: Aug 21, 2017
 *      Author: OS1
 */

#ifndef BLOCKEDS_H_
#define BLOCKEDS_H_

class PCB;

class Blockeds {
	struct Elem {
		PCB* pcb;
		int time;
		Elem* next;
		Elem(PCB* pcbb=0,int timee=0,Elem* nextt=0) {
			pcb=pcbb;
			time=timee;
			next=nextt;
		}
	};
	Elem* head;
	Elem* last;
	unsigned int size;
public:
	Blockeds();
	virtual ~Blockeds();
	void addS(PCB* pcbb,int time);
	PCB* popS();
	PCB* popoutS(PCB* pcbbb);
	void timerblist();
	static Blockeds* globalblist;
protected:
	friend void interrupt timer();
};

#endif /* BLOCKEDS_H_ */
