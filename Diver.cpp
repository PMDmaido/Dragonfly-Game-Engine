//
// Diver.cpp
//

// System includes.
#include <stdlib.h>  // for rand()

// Engine includes.
#include "WorldManager.h"
#include "LogManager.h"

// Game includes.
#include "Diver.h"
#include "GameOver.h"
#include "DisplayManager.h"
#include "EventOut.h"

Diver::Diver() {
    setType("Diver");
    if (setSprite("diver") != 0) {
        LM.writeLog("Diver::Diver(): Error! Unable to find sprite: diver");
    }
    setSolidness(df::SOFT);
    startPosition();
	LM.writeLog("Diver created");
}

// Handle event.
int Diver::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::COLLISION_EVENT) {
        return collide((df::EventCollision*)p_e);
    }

	if (p_e->getType() == df::OUT_EVENT) {
		new GameOver(false);
		WM.markForDelete(this);
		return 1;
	}
    return 0;
}

// Handle collision events.
int Diver::collide(const df::EventCollision* p_e) {
    df::Object* obj1 = p_e->getObject1();
    df::Object* obj2 = p_e->getObject2();

    if (obj1->getType() == "Diver" || obj2->getType() == "Diver") {
        if (obj1->getType() == "large-shark" || obj2->getType() == "large-shark") {
			// Mark for deletion.
			WM.markForDelete(this);
			LM.writeLog("Diver eaten by large shark");
        }
    }
    return 0;
}

// Set the starting position of the diver.
void Diver::startPosition() {
    df::Vector begin, end;

    // Get world boundaries.
    int world_x = (int)WM.getBoundary().getHorizontal();
    int world_y = (int)WM.getBoundary().getVertical();

    switch (1) {
    case 0: // Left side.
        begin.setX(0);
        begin.setY((float)(rand() % world_y));
        end.setX(world_x + 3.0f);
        end.setY((float)(rand() % world_y));
        break;
    case 1: // Right side.
        begin.setX(DM.getHorizontal());
        begin.setY((float)(rand() % world_y));
        end.setX(0 - 3.0f);
        end.setY((float)(rand() % world_y));
        break;
    }

    WM.moveObject(this, begin);
    df::Vector velocity = df::Vector(end.getX() - begin.getX(), end.getY() - begin.getY());
    velocity.normalize();
    setDirection(velocity);
	setSpeed(1.0f);
}
