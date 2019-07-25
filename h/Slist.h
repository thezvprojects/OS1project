/*
 * Slist.h
 *
 *  Created on: Aug 24, 2017
 *      Author: OS1
 */

#ifndef SLIST_H_
#define SLIST_H_

class Kernels;

class Slist {
	struct Elem {
		Kernels* semaph;
		Elem* next;
		Elem(Kernels* s, Elem* nxt=0) {
			semaph=s;
			next=nxt;
		}
	};
	Elem* head;
	Elem* last;
public:
	Slist();
	virtual ~Slist();
	void add(Kernels* sem);
	Kernels* get(int idd);
	void deletesem(Kernels* ks);
protected:
	friend void interrupt timer();
};

#endif /* SLIST_H_ */
