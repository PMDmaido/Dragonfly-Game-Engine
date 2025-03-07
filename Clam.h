#pragma once
//
// Clam.h
//

#include "Object.h"
#include "EventStep.h"

class Clam : public df::Object {

private:
    bool clam_open; //if clam is open
    int time_spawn_pearl;
	int step_count;
	bool pearl;

public:
    // Constructor
    Clam();

    // Handle event (if needed in future)
    int eventHandler(const df::Event* p_e) override;

    int step(const df::EventStep* p_e);
};