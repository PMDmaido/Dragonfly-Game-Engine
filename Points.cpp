//
// Points.cpp
//

// Engine includes
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"

// Game includes.
#include "Points.h"
#include "Diver.h"


Points::Points() {
    setType(POINTS_STRING);
    setLocation(df::TOP_RIGHT);
    setViewString(POINTS_STRING);
    setColor(df::WHITE);
    setValue(0);
}