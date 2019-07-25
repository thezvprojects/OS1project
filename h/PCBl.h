/*
 * PCBl.h

 *
 *  Created on: Jun 8, 2017
 *      Author: OS1
 */

#ifndef PCBL_H_
#define PCBL_H_

class PCB;

class PCBl {
	struct Node {
		PCB* pcb;
		Node* next;
		Node(PCB* pcbb = 0, Node* nod = 0) {
			pcb = pcbb;
			next = nod;
		} // podrazumevani
	};
	Node* head;
	Node* last;
	int cnt;

public:
	PCBl();
	virtual ~PCBl();
	void addPCB(PCB* pcbb);
	PCB* popPCB(int id);
	PCB* popPCB();
	PCB* getPCB(int id);
	unsigned int empty();
protected:
	friend class PCB;
	friend class Thread;
	friend void interrupt timer();
	friend class UMThr;
};

#endif /* PCBL_H_ */
