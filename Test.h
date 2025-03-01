#ifndef __TEST_H__
#define __TEST_H__


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
#include "DisplayManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "Event.h"
#include "EventStep.h"
#include "EventCollision.h"

class Test {
public:
	void runTest();

	///// Tests list
	// Check-point 1
	void testManager();
	void testLogManager();
	// Check-point 2
	void TestSystemTime(); 
	void testClock();
	// void testGameManager();
// Check-point 3
	void testVector();
	void testObject();
	void testObjectList();
	// Check-point 4

	// Naiad
	bool testDM_DrawCharacter();
	bool testDM_DrawString();
	bool testWM_Collision();
	bool testObject_Solidness();
	bool testObject_Altitude();
	bool testObject_Velocity();

	// Dragonfly
	bool testBoxIntersections();
	bool testBoxNonIntersection(); 
	bool testEventViewData();

	//bool testSpriteAttributes();
	bool testSoundAttributes();
	bool testMusicAttributes();
	bool testFrameAttributes();
	bool testBoxAttributes();
	bool testViewObjectAttributes();
	bool testEventViewAttributes(); 
};

#endif // __TEST_H__