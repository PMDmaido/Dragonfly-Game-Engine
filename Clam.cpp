//
// Clam.cpp
//

#include "Clam.h"
#include "Pearl.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"

// Constructor
Clam::Clam() {
    setType("clam");
    setSprite("c-clam"); // Default closed clam
    setSolidness(df::SPECTRAL);

    // Set position near the bottom of the screen
    df::Vector p = df::Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() - 4);
    setPosition(p);

    clam_open = false;
    time_spawn_pearl = -1; // No pearl spawning initially
    step_count = 0;
    pearl = false;
}

// Handle events
int Clam::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
		step_count++;
        return step((df::EventStep*)p_e);
    }
    return 0;
}

// Handle step events
int Clam::step(const df::EventStep* p_step) {

	if (step_count == 0 ) {
		return 0;
	}

	

    if (step_count % 900 == 0) { // Every 30 seconds
        if (!clam_open) {
            setSprite("clam");  // Switch to animated open-mouth clam

            clam_open = true;
            time_spawn_pearl = getAnimation().getSprite()->getFrameCount() * 30;
        }
    }

    // If clam is open and has a valid spawn time
    if (clam_open && time_spawn_pearl > 0) {
        int current_frame = getAnimation().getIndex();

        if (current_frame == 3 && !pearl) {  // Frame 4: Spawn pearl
            new Pearl(getPosition());
            pearl = true;
        }


        if (current_frame > 13 ) {  // After frame 8, reset pearl tracking
            time_spawn_pearl = -1;
        }
    }

    // Once animation completes, switch back to closed clam
    if (clam_open && getAnimation().getIndex() == getAnimation().getSprite()->getFrameCount() - 1) {
        setSprite("c-clam");  // Reset to closed clam
        clam_open = false;
		pearl = false;
    }

    return 1;
}
