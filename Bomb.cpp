//
// Bomb.cpp
//

// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "DisplayManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "WorldManager.h"

// Game includes.
#include "Bomb.h"

Bomb::Bomb() {
    setType("bomb");
	setSprite("bomb");

    setSolidness(df::SOFT);
    setVelocity(df::Vector(0, (float)(rand() % 10 + 2) / 20.0)); 
    setAltitude(df::MAX_ALTITUDE);

    df::Vector p(
        (float)(rand() % (int)WM.getBoundary().getHorizontal()), -5.0f);
    setPosition(p);

}

Bomb::~Bomb() {
    new Bomb();
}

// Handle event.
// Return 0 if ignored, else 1.
int Bomb::eventHandler(const df::Event* p_e) {

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
int Bomb::collide(const df::EventCollision* p_e) {

    df::Object* obj1 = p_e->getObject1();
    df::Object* obj2 = p_e->getObject2();


    if (obj1->getType() == "medium-shark" || obj2->getType() == "medium-shark" ||
        obj1->getType() == "small-shark" || obj2->getType() == "small-shark" ||
        obj1->getType() == "large-shark" || obj2->getType() == "large-shark") {
        if (obj1->getType() == "bomb" || obj2->getType() == "bomb") {
            WM.markForDelete(this);
            return 1;
        }
    }
    return 0;
}

// If Star moved off window, move back to far right.
void Bomb::out() {
    df::Vector p(
        (float)(rand() % (int)WM.getBoundary().getHorizontal()), -5.0f); // Random X
    setPosition(p);
}
