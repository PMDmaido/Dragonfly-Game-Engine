#pragma once
//
// EventStep.h
//

#include "Event.h"

namespace df {

    const std::string STEP_EVENT = "STEP_EVENT";

    class EventStep : public Event {
    private:
        int m_step_count;  

    public:
        // Constructor sets the event type
        EventStep();

        // Constructor with initial stepcount
        EventStep(int inti_step_count);

        // Destructor
        ~EventStep();

        // Set step count.
        void setStepCount(int new_step_count);

        // Get step count.
        int getStepCount() const;
    };

} // end namespace df
