/*
 * UMThr.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: OS1
 */

#include "UMThr.h"
#include<iostream.h>
#include"Foos.h"

extern int returnV;

int userMain(int argc, char* argv[]);

UMThr::UMThr(int argcc, char* argvv[]) :
		Thread() {
	this->argc = argcc;
	this->argv = argvv;
}

void UMThr::run() {
	returnV = userMain(argc, argv);
}

UMThr::~UMThr() {
	for (int i = 0; i < argc; i++)
		delete argv[i];
	delete[] argv; // pokazivac?
}

