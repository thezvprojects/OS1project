/*
 * Thread.h
 *
 *  Created on: Jun 6, 2017
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x55ms
const Time defaultTimeSlice = 2; // default=2x55ms
typedef int ID;

class PCB;

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);
protected:
	friend class PCB;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice =
			defaultTimeSlice);
	virtual void run() {
	}
private:
	PCB* myPCB;
};

void dispatch();

#endif /* THREAD_H_ */
