/*
 * IDLThr.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: OS1
 */

#include "IDLThr.h"
#include "pcb.h"
#include "Foos.h"
#include <stdio.h>
#include <iostream.h>

IDLThr::IDLThr() :
		Thread(1024, 2) {
}

void IDLThr::run() {
	while (1);
}

IDLThr::~IDLThr() {

}

