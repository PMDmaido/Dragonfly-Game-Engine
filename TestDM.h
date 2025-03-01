#ifndef __TEST_DM_H__
#define __TEST_DM_H__


// System includes
#include <iostream>
#include <cassert>
#include <cstdio>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <math.h>

// Engine includes
#include "Manager.h"
#include "LogManager.h"
#include "Clock.h"
#include "GameManager.h"
#include "Vector.h"
#include "Object.h"
#include "ObjectList.h" 

class TestDM {
public:
	void runTest();

	///// Tests list
	void test1();
	void test2();

};

#endif // __TEST_H__