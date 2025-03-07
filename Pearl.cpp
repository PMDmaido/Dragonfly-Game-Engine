//
// Pearl.cpp
//

#include "Pearl.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "LogManager.h"
#include "EventCollision.h"
#include "EventView.h"
#include "Life.h"
#include "Sound.h"
#include "ResourceManager.h"

// Constructor
Pearl::Pearl(df::Vector position) {
    setType("pearl");
    setSprite("pearl");
    setPosition(position);
    setVelocity(df::Vector(0, 0.001));
    setSolidness(df::SOFT);
	LM.writeLog("Pearl created");
	setAltitude(3);
    lifetime = getAnimation().getSprite()->getFrameCount() * 30 * 2; 
}

// Handle events
int Pearl::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::STEP_EVENT) {;
        step();
        return 1;
    }
    
    if (p_e->getType() == df::COLLISION_EVENT) {
        return collide((df::EventCollision*)p_e);
    }


    return 0;
}

// Step function to track lifetime
void Pearl::step() {
    lifetime--;
    if (lifetime <= 0) {
        WM.markForDelete(this); // Remove pearl from the game
    }
}

// Handle collision events
int Pearl::collide(const df::EventCollision* p_e) {

	df::Object* obj1 = p_e->getObject1();
	df::Object* obj2 = p_e->getObject2();

    if (obj1->getType() == "medium-shark" || obj2->getType() == "medium-shark" ||
        obj1->getType() == "small-shark" || obj2->getType() == "small-shark" ||
        obj1->getType() == "large-shark" || obj2->getType() == "large-shark") {
        if (obj1->getType() == "pearl" || obj2->getType() == "pearl") {
            WM.markForDelete(this);
            return 1;

        }
	}
    return 0;
}