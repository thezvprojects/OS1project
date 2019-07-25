/*
 * PCBl.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: OS1
 */

#include "PCBl.h"
#include "PCB.h"
#include "Foos.h"

PCBl::PCBl() {
	head = 0;
	last = 0;
	cnt = 0;
}
void PCBl::addPCB(PCB* pcbb) {
	Node* n = new Node(pcbb);
	if (head == 0)
		head = n;
	else
		last->next = n;
	last = n;
	cnt++;
}
PCB* PCBl::popPCB(int id) {
	Node* tmp = head;
	Node* aux = 0;
	while (tmp && (tmp->pcb->retid() != id)) {
		aux = tmp;
		tmp = tmp->next;
	}

	if (tmp != 0) {
		if (aux == 0) {
			head = head->next;
			if (head == 0)
				last = 0;
		} else {
			aux->next = tmp->next;
			if (last == tmp)
				last = aux;
		}
		PCB* pcbb=tmp->pcb;
		delete tmp;
		return pcbb;
	}
	return 0;
}
PCB* PCBl::popPCB() {
	if (head == 0)
		return 0;
	else {
		Node* tmp = head;
		PCB* pcbbb = tmp->pcb;
		head = head->next;
		delete tmp;
		cnt--;
		if (head == 0)
			last = 0;
		return pcbbb;
	}
}

PCB* PCBl::getPCB(int id) {
	Node* tmp = head;
	while (tmp && (tmp->pcb->retid() != id))
		tmp = tmp->next;
	if (tmp != 0)
		return tmp->pcb;
	return 0;
}

unsigned int PCBl::empty() {
	if (head == 0) {
		return 1;
	}
	return 0;

}

PCBl::~PCBl() {
	while (head) {
			Node* old = head;
			head = head->next;
			if (last == old)
				last = 0;
			delete old;
		}
	head = 0;
	last = 0;
	cnt = 0;
}
