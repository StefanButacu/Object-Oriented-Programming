// Lab2_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include "ui.h"
#include "service.h"

int main()
{
	testAll();
	serviceCars service = createServiceCars();
	//run(&service);
	destroyService(&service);
	_CrtDumpMemoryLeaks();
	return 0;
}