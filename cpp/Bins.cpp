/*
 * Bins.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: OS1
 */

#include "Bins.h"

Bins::Bins() {
	head = 0;
	last = 0;

}

Bins::~Bins() {
	while (head) {
			Elem* old = head;
			head = head->next;
			if (last == old)
				last = 0;
			delete old;
		}
	head = 0;
	last = 0;
}

void Bins::addinS(PCB* id) {
	Elem *tmp = new Elem(id);

	if (head == 0) {
		head = tmp;
		last = tmp;
		return;
	}

	last->next = tmp;
	if (head == last)
		head->next = tmp;
	last = tmp;
}

PCB* Bins::popoutS(PCB* idd) {
	Elem* tmp = head;
	Elem* aux = 0;

	while (tmp != 0 && tmp->pcb != idd) {
		aux = tmp;
		tmp = tmp->next;

	}
	if (tmp == 0)
		return 0;
	if (tmp == head) {
		head = head->next;
		if (head == 0)
			last = 0;
		PCB* hlp = tmp->pcb;
		delete tmp;
		return hlp;
	} else {
		aux->next = tmp->next;
		if (tmp == last)
			last = aux;
		PCB* j = tmp->pcb;
		delete tmp;
		return j;
	}
}

PCB* Bins::popS() {
	if (head == 0)
		return 0;
	Elem* old = head;
	PCB* idd = old->pcb;
	head = head->next;
	if (head == 0)
		last = 0;
	delete old;
	return idd;
}
