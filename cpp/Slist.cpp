/*
 * Slist.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: OS1
 */

#include "Slist.h"
#include "Kernels.h"

Slist::Slist() {
	head = 0;
	last = 0;
}

Slist::~Slist() {
	while(head) {
		Elem* old=head;
		head=head->next;
		delete old;
	}
}

void Slist::add(Kernels* sem) {
	Elem *tmp = new Elem(sem);

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

Kernels* Slist::get(int idd) {
	Elem* aux = head;
	while (aux != 0 && aux->semaph->SemId != idd) {
		aux->next;
	}
	if (aux == 0)
		return 0;

	return aux->semaph;
}

void Slist::deletesem(Kernels* ks) {

}
