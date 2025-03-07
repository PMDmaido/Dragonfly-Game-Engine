//
// Star.cpp
//

// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "DisplayManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "WorldManager.h"

// Game includes.
#include "Starfish.h"

Starfish::Starfish() {
    setType("Starfish");
    setSolidness(df::SOFT);
    setVelocity(df::Vector(0, (float)-1.0 / (rand() % 15 + 5)));
    setAltitude(df::MAX_ALTITUDE);	
    df::Vector p(
        (float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)(WM.getBoundary().getVertical() + 1));
    setPosition(p);
}

Starfish::~Starfish() {
	new Starfish();
}

// Draw star window.
int Starfish::draw() {
    DM.drawCh(getPosition(), STAR_CHAR, df::YELLOW);
    return 0;
}

// Handle event.
// Return 0 if ignored, else 1.
int Starfish::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }
    if (p_e->getType() == df::COLLISION_EVENT) {
        return collide((df::EventCollision*)p_e);
    }

    // If get here, have ignored this event.
    return 0;
}


// Handle collision events.
int Starfish::collide(const df::EventCollision* p_e) {

    df::Object* obj1 = p_e->getObject1();
    df::Object* obj2 = p_e->getObject2();


    if (obj1->getType() == "medium-shark" || obj2->getType() == "medium-shark" ||
        obj1->getType() == "small-shark" || obj2->getType() == "small-shark" ||
        obj1->getType() == "large-shark" || obj2->getType() == "large-shark") {
        if (obj1->getType() == "Starfish" || obj2->getType() == "Starfish") {
            WM.markForDelete(this);
        }
    }
    return 0;
}

// If Star moved off window, move back to far right.
void Starfish::out() {
    df::Vector p(
        (float)(rand() % (int)WM.getBoundary().getHorizontal()),  // Random X
        (float)(WM.getBoundary().getVertical() + 1));   // Reset below screen
    setPosition(p);
}
