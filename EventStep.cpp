// EventStep.cpp

#include "EventStep.h"

namespace df {

    // Create step event with step count 0.
    EventStep::EventStep() {
        // Set event type to "df::step".
        setType(STEP_EVENT);

        // Initialize step count to 0.
        m_step_count = 0;
    }

    // Create step event with indicated count.
    EventStep::EventStep(int init_step_count) {
        // Set event type to "df::step".
        setType(STEP_EVENT);

        // Set initial step count.
        m_step_count = init_step_count;
    }

    // Set step count.
    void EventStep::setStepCount(int new_step_count) {
        m_step_count = new_step_count;
    }

    // Get step count.
    int EventStep::getStepCount() const {
        return m_step_count;
    }

} // end of namespace df