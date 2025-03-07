//
// Points.cpp
//

// Engine includes
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"

// Game includes.
#include "Life.h"
#include "ResourceManager.h"

Life::Life() {
    setType(LIFE_STRING);
    setLocation(df::TOP_LEFT);
    setViewString(LIFE_STRING);
    setValue(1);
    setColor(df::RED);

}

// Handle event.
// Return 0 if ignored, else 1.
int Life::eventHandler(const df::Event* p_e) {
    return 0;
}


// Reduce 1 life 
void Life::loseLife() {
	df::Sound* p_sound = RM.getSound("hit");
    p_sound->play();
    setValue(getValue() - 1);
}

void Life::gainLife() {
    setValue(getValue() + 1);
}

void Life::lose() {
    setValue(0);
}