/*
 * semaphor.cpp
 *
 *  Created on: Aug 21, 2017
 *      Author: OS1
 */

#include "semaphor.h"
#include "Kernels.h"

Semaphore::Semaphore(int init) {
	myksem = new Kernels(init);
}

Semaphore::~Semaphore() {
	delete myksem;
}

int Semaphore::wait(int MaxBtime) {

	return myksem->wait(MaxBtime);

}

void Semaphore::signal() {

	myksem->signal();

}

int Semaphore::val() const {

	return myksem->Svalue;

}
