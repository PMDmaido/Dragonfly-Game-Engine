//
// Shark.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "ResourceManager.h" 

// Game includes.
#include "Shark.h"
#include "LogManager.h"
#include <iostream>
#include "EventView.h"
#include "Points.h"
#include "game.h"
#include "GameOver.h"
#include "ObjectList.h"

#include "Diver.h"
#include "Bomb.h"
#include "Life.h"
#include "Pearl.h"

Shark::Shark() {
    setType("small-shark");
    setSolidness(df::HARD);
    if (setSprite("small-shark-right") != 0) {
        LM.writeLog("Shark::Shark(): Error! Unable to find sprite");
    }
    setAltitude(df::MAX_ALTITUDE); // Make Reticle in the foreground.

    // Reticle moves with mouse, so register.
#ifdef DF_REGISTER_INTEREST
    registerInterest(df::MSE_EVENT);
#endif

    // Start reticle in center of window.
    df::Vector p(WM.getBoundary().getHorizontal() / 2,
        WM.getBoundary().getVertical() / 2);
    setPosition(p);
    diver = false;
    bomb = false;
	old_x = getPosition().getX();
}

Shark::~Shark() {
    // Create GameOver object.
    new GameOver(false);

}


// Handle event.
// Return 0 if ignored, else 1.
int Shark::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            // Change location to new mouse position.
            setPosition(p_mouse_event->getMousePosition());
			if (old_x < getPosition().getX()) {
				setSprite(getType() + "-right");
			}
			else {
				setSprite(getType() + "-left");
			}
			old_x = getPosition().getX();
            return 1;
        }
    }

	if (p_e -> getType() == df::COLLISION_EVENT) {
		return collide((df::EventCollision *) p_e);
	}

    if (p_e->getType() == df::STEP_EVENT)
        return step((df::EventStep*)p_e);

    // If get here, have ignored this event.
    return 0;
}

int Shark::step(const df::EventStep* p_e) {
    
    df::ObjectList ol = WM.getAllObjects();

	for (int i = 0; i < ol.getCount(); i++) {

        df::Object* p_o = ol[i];

		if (dynamic_cast<Points*>(p_o)) {
			Points* p = dynamic_cast<Points*>(ol[i]);
            if (p->getValue() >= DIVER_BAR && !diver) {
                new Diver();
                diver = true;
                LM.writeLog("Diver enter");
                return 1;
            }
            else if (p->getValue() >= BOMB_BAR && !bomb) {
				for (int i = 0; i < 5; i++) {
					new Bomb();
				}
                //new Bomb();
                bomb = true;
                LM.writeLog("Bombing");
                return 1;
            }

            else if (p->getValue() >= LARGE_SHARK_BAR) {

                setSprite("large-shark");
                setType("large-shark");
                return 1;
            }
            else if (p->getValue() >= MEDIUM_SHARK_BAR) {
                setSprite("medium-shark");
                setType("medium-shark");
                return 1;
            }
		}
	}

    return 0;
}

int Shark::collide(const df::EventCollision* p_e) {

    df::Object* obj1 = p_e->getObject1();
    df::Object* obj2 = p_e->getObject2();

    LM.writeLog("Collision detected! Object1: %s, Object2: %s",
        obj1->getType().c_str(), obj2->getType().c_str());


    if (obj1->getType() == "small-shark" || obj2->getType() == "small-shark") {
        if (obj1->getType() == "little-fish" || obj2->getType() == "little-fish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +LITTLE_PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("eat");
            p_sound->play();
        }
        else if (obj1->getType() == "Starfish" || obj2->getType() == "Starfish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("starfish");
            p_sound->play();
        }
        else if (obj1->getType() == "pearl" || obj2->getType() == "pearl") {
            
            df::Sound* p_sound = RM.getSound("yay");
            p_sound->play();
			if (obj1->getType() == "pearl") {
				WM.markForDelete(obj1);
			}
			else {
				WM.markForDelete(obj2);
			}
            df::ObjectList ol = WM.getAllObjects();
            for (int i = 0; i < ol.getCount(); i++) {
                df::Object* p_o = ol[i];
                if (dynamic_cast<Life*>(p_o)) {
                    Life* p = dynamic_cast<Life*>(ol[i]);
                    p->gainLife();
                    return 1;
                }
            }
        }
        else {
            // Mark for deletion.
            df::ObjectList ol = WM.getAllObjects();
			for (int i = 0; i < ol.getCount(); i++) {
				df::Object* p_o = ol[i];
				if (dynamic_cast<Life*>(p_o)) {
                    Life* p = dynamic_cast<Life*>(ol[i]);
					if (p->getValue() > 1) {
						p->loseLife();
						LM.writeLog("Life lost");
						return 1;
					}
					else {
                        WM.markForDelete(this);
					}
				}
			}
        }
        return 1; // Handled.
    }
    else if (obj1->getType() == "medium-shark" || obj2->getType() == "medium-shark") {
        if (obj1->getType() == "little-fish" || obj2->getType() == "little-fish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +LITTLE_PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("eat");
            p_sound->play();
        }
        else if (obj1->getType() == "small-fish" || obj2->getType() == "small-fish"){
            // Increase points.
            df::EventView ev(POINTS_STRING, +SMALL_PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("eat");
            p_sound->play();
        }
        else if (obj1->getType() == "Starfish" || obj2->getType() == "Starfish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("starfish");
            p_sound->play();
        }
        else if (obj1->getType() == "pearl" || obj2->getType() == "pearl") {
            df::Sound* p_sound = RM.getSound("yay");
            p_sound->play();
            if (obj1->getType() == "pearl") {
                WM.markForDelete(obj1);
            }
            else {
                WM.markForDelete(obj2);
            }
            df::ObjectList ol = WM.getAllObjects();
            for (int i = 0; i < ol.getCount(); i++) {
                df::Object* p_o = ol[i];
                if (dynamic_cast<Life*>(p_o)) {
                    Life* p = dynamic_cast<Life*>(ol[i]);
                    p->gainLife();
                    return 1;
                }
            }
        }
        else {
            // Mark for deletion.
            df::ObjectList ol = WM.getAllObjects();
            for (int i = 0; i < ol.getCount(); i++) {
                df::Object* p_o = ol[i];
                if (dynamic_cast<Life*>(p_o)) {
                    Life* p = dynamic_cast<Life*>(ol[i]);
                    if (p->getValue() > 1) {
                        p->loseLife();
                        LM.writeLog("Life lost");
                        return 1;
                    }
                    else {
                        WM.markForDelete(this);
                    }
                }
            }

        }
        return 1; // Handled.
    }
    else if (obj1->getType() == "large-shark" || obj2->getType() == "large-shark") {
        if (obj1->getType() == "little-fish" || obj2->getType() == "little-fish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +LITTLE_PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("eat");
            p_sound->play();
        }
        else if (obj1->getType() == "small-fish" || obj2->getType() == "small-fish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +SMALL_PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("eat");
            p_sound->play();
        }
        else if (obj1->getType() == "medium-fish" || obj2->getType() == "medium-fish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +MEDIUM_PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("eat");
            p_sound->play();
        }
        else if (obj1->getType() == "Starfish" || obj2->getType() == "Starfish") {
            // Increase points.
            df::EventView ev(POINTS_STRING, +PLUS_POINT, true);
            WM.onEvent(&ev);
            df::Sound* p_sound = RM.getSound("starfish");
            p_sound->play();
        }
        else if (obj1->getType() == "Diver" || obj2->getType() == "Diver") {
            new GameOver(true);
		}
		else if (obj1->getType() == "pearl" || obj2->getType() == "pearl") {
            df::Sound* p_sound = RM.getSound("yay");
            p_sound->play();
            if (obj1->getType() == "pearl") {
                WM.markForDelete(obj1);
            }
            else {
                WM.markForDelete(obj2);
            }
            df::ObjectList ol = WM.getAllObjects();
            for (int i = 0; i < ol.getCount(); i++) {
                df::Object* p_o = ol[i];
                if (dynamic_cast<Life*>(p_o)) {
                    Life* p = dynamic_cast<Life*>(ol[i]);
                    p->gainLife();
                    return 1;
                }
            }
		}
        else {
            // Mark for deletion.
            df::ObjectList ol = WM.getAllObjects();
            for (int i = 0; i < ol.getCount(); i++) {
                df::Object* p_o = ol[i];
                if (dynamic_cast<Life*>(p_o)) {
                    Life* p = dynamic_cast<Life*>(ol[i]);
                    if (p->getValue() > 1) {
                        p->loseLife();
                        LM.writeLog("Life lost");
                        return 1;
                    }
                    else {
                        WM.markForDelete(this);
                    }
                }
            }

        }
        return 1; // Handled.

    }
    return 0;
}
