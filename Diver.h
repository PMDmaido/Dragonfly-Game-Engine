#pragma once
//
// Diver.h
//

#ifndef DIVER_H
#define DIVER_H

#include "Object.h"
#include "EventCollision.h"

class Diver : public df::Object {
public:
    // Constructor
    Diver();

    // Handle events
    int eventHandler(const df::Event* p_e) override;

    // Handle collision events
    int collide(const df::EventCollision* p_e);

    // Set the starting position
    void startPosition();
};

#endif // DIVER_H