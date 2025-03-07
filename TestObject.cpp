#include "TestObject.h"
#include "LogManager.h"
#include <chrono>
#include <thread>
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "windows.h"

TestObject::TestObject() {
    // Set object type
    setType("TestObject");
    step_count = 0;

    // Log object creation
    LM.writeLog("TestObject created.");
}

TestObject::~TestObject() {

}

// Handle events (e.g., step event)
int TestObject::eventHandler(const Event* p_e)  {
    if (p_e->getType() == STEP_EVENT) {

        timeBeginPeriod(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        timeEndPeriod(1);

        // Stop the game loop after 100
        if (step_count >= 100) {
            LM.writeLog("TestObject stopping the game loop.");
            WM.markForDelete(this);
            GM.setGameOver(true); // Stop the game loop.
        }
        step_count++;
        return 1; // Event handled.
    }
    return 0; // Event not handled.
}