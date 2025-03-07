#pragma once
//
// Pearl.h
//

#include "Object.h"
#include "EventCollision.h"

class Pearl : public df::Object {
private:
    int lifetime; // Lifetime of the pearl in steps

public:
    // Constructor
    Pearl(df::Vector position);

    // Handle events (optional, if needed later)
    int eventHandler(const df::Event* p_e) override;

    // Step event to handle disappearance
    void step();

	// Handle collision events
	int collide(const df::EventCollision* p_e);
};

