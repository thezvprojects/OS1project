/*
 * event.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: OS1
 */

#include "event.h"
#include "KernelEv.h"

Event::Event(int num) {
	myImpl= new KernelEv(num);

}

Event::~Event() {
	delete myImpl;
}

void Event::wait() {
	myImpl->wait();
}

void Event::signal() {
	myImpl->signal();
}
