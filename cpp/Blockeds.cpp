/*
 * Blockeds.cpp
 *
 *  Created on: Aug 21, 2017
 *      Author: OS1
 */

#include "Blockeds.h"
#include "PCB.h"
#include "Foos.h"
#include <stdio.h>
#include <iostream.h>
#include "SCHEDULE.H"
#include "Bins.h"
#include "Kernels.h"

Blockeds::Blockeds() {
	head = 0;
	last = 0;
	size = 0;
}

Blockeds::~Blockeds() {
	while (head) {
		Elem* old = head;
		head = head->next;
		if (last == old)
			last = 0;
		delete old;
	}
	head = 0;
	last = 0;
	size = 0;
}

void Blockeds::addS(PCB* pcbb, int time) {

	Elem *tmp = new Elem(pcbb, time);
	Elem *aux = head;
	Elem *auxx = 0;

	//printf("time:%d\n", time);
	if (time == 0) {
		return;
	}
	size++;
	if (head == 0) {
		head = tmp;
		last = tmp;
		return;
	}
	int k = aux->time;
	int auxk = 0;
	while (time > k && aux != 0) {
		auxx = aux;
		aux = aux->next;

		auxk = k;
		if (aux == 0)
			break;
		k += aux->time;
	}
	if (aux == 0) {
		if (head == last)
			head->next = tmp;
		last->next = tmp;
		last = tmp;
		tmp->time = time - k;
		return;
	}
	if (aux == head) {
		head->time = head->time - time;
		tmp->next = head;
		head = tmp;
		return;
	}
	auxx->next = tmp;
	tmp->next = aux;
	aux->time = k - time;
	tmp->time = time - auxk;
}

PCB* Blockeds::popS() {
	if (head == 0) {
		return 0;

	}
	size--;
	int k = head->time;
	Elem* old = head;
	PCB* z = old->pcb;
	head = head->next;
	if (head == 0) {
		last = 0;
		return z;
	}
	old->next = 0;
	head->time = head->time + k;
	delete old;
	return z;
}

PCB* Blockeds::popoutS(PCB* idd) {
	Elem* tmp = head;
	Elem* aux = 0;

	while (tmp != 0 && tmp->pcb != idd) {
		aux = tmp;
		tmp = tmp->next;
	}
	if (tmp == 0) {
		return 0;
	}
	size--;
	if (tmp == head) {
		head = head->next;
		if (head == 0)
			last = 0;
		PCB* hlp = tmp->pcb;
		if (tmp->next != 0)
			tmp->next->time += tmp->time;
		delete tmp;
		return hlp;
	} else {
		aux->next = tmp->next;
		if (tmp == last)
			last = aux;
		PCB* j = tmp->pcb;
		if (tmp->next != 0)
			tmp->next->time += tmp->time;
		delete tmp;
		return j;
	}
}

Blockeds::Elem* globalhead=0;
PCB* aux=0;

void Blockeds::timerblist() {
	if (PCB::globalblist->head) {
		globalhead = PCB::globalblist->head;

		globalhead->time--;
		//cout<<"Head time="<<globalhead->time<<"   \n";

		//cout<<"List size="<<hex<<PCB::globalblist->size<<"\n";
		//printf("Head timer2 = %d",globalhead->time);
		while (globalhead != 0 && globalhead->time == 0) {
			aux = PCB::globalblist->popS();
			PCB::running->mysem->blist->popoutS(aux);
			aux->blocked = 0;
			aux->waitflag = 0;
			Scheduler::put(aux);
			globalhead = PCB::globalblist->head;
		}
	}
}
