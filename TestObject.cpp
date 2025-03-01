// TestObject.cpp

// eventHandler look for for STEP_EVENT
// start at (0,0) at step 0
// set position to (3,4) at step 10
// delete object at step 100
// GameManager setGameOver at step 100

#include "TestObject.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "GameManager.h"
#include "Event.h"
#include "DisplayManager.h"

TestObject::TestObject() {
	setType("TestObject"); // Object should auto setPosition(df::Vector(0, 0));
	int test_x = getPosition().getX();
	int test_y = getPosition().getY();
	LM.writeLog("TestObject created at (x=%d, y=%d)\n", test_x, test_y);
}

int TestObject::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step = dynamic_cast <const df::EventStep*> (p_e);
		if (p_step) {
			int step_count = p_step->getStepCount();
			if (step_count == 10) {
				setPosition(df::Vector(3, 4));
				int step10_x = getPosition().getX();
				int step10_y = getPosition().getY();
				draw();
				LM.writeLog("TestObject set position to (%d, %d) at step %d.\n", step10_x, step10_y, step_count);
			}
			else if (step_count == 450) {// running for 15 seconds
				WM.markForDelete(this);
				LM.writeLog("TestObject deleted at step %d\n", step_count);
				GM.setGameOver(true); // Set game over at step 100
			}
		}
		return 1;
	}
	return 0;
}

int TestObject::draw() {

	DM.drawCh(df::Vector({ 10,7 }), 'X', df::RED);
	//return df::Object::draw();
	return 0;
}

TestObject::~TestObject() {
	LM.writeLog("TestObject deleted\n");
}