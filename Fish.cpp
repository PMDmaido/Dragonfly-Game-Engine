//
// Fish.cpp
//

// Engine includes.
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"

// Game includes.
#include "Fish.h"
#include <iostream>

// Constructor - supply name of Fish (matches Sprite).
Fish::Fish(std::string name) {
    setType(name);
    if (setSprite(name + "-left") != 0)
        LM.writeLog("Fish::Fish(): Error! Unable to find sprite: %s", name.c_str());
    setSolidness(df::SOFT);

}

// Handle event.
int Fish::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::OUT_EVENT)
        return out((df::EventOut*)p_e);
    if (p_e->getType() == df::COLLISION_EVENT)
        return collide((df::EventCollision*)p_e);
    return 0;
}

// Handle out events.
int Fish::out(const df::EventOut* p_e) {

    WM.markForDelete(this);
    return 1;
}

// Handle collision events.
int Fish::collide(const df::EventCollision* p_e) {

    df::Object* obj1 = p_e->getObject1();
    df::Object* obj2 = p_e->getObject2();

    if (obj1->getType() == "small-fish" || obj2->getType() == "small-fish" ||
        obj1->getType() == "little-fish" || obj2->getType() == "little-fish"||
        obj1->getType() == "medium-fish" || obj2->getType() == "medium-fish") {
        if (obj1->getType() == "medium-shark" || obj2->getType() == "medium-shark" ||
            obj1->getType() == "small-shark" || obj2->getType() == "small-shark" || 
            obj1->getType() == "large-shark" || obj2->getType() == "large-shark")
		        WM.markForDelete(this);
    }
    return 0;
}

// Destructor.
Fish::~Fish() {
    
    WM.markForDelete(this);
}

// Setup starting conditions.
void Fish::start(float speed) {

    df::Vector begin, end;

    // Get world boundaries.
    int world_x = (int)WM.getBoundary().getHorizontal();
    int world_y = (int)WM.getBoundary().getVertical();

    switch (rand() % 2) {
    case 0: // Left side.
		setSprite(getType() + "-right");
        begin.setX(0 - 3.0f);
        begin.setY((float)(rand() % world_y));
        end.setX(world_x + 3.0f);
        end.setY((float)(rand() % world_y));
        break;
    case 1: // Right side.
        begin.setX(DM.getHorizontal() + 3.0f);
        begin.setY((float)(rand() % world_y));
        end.setX(0 - 3.0f);
        end.setY((float)(rand() % world_y));
        break;
    }

	setPosition(begin);

    WM.moveObject(this, begin);
	df::Vector velocity = df::Vector(end.getX() - begin.getX(), end.getY() - begin.getY());
    velocity.normalize();
    setDirection(velocity);
    setSpeed(0.1f + static_cast<float>(rand()) / RAND_MAX * (0.4f - 0.2f));
}
