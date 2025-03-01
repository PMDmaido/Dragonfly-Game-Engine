// Event.cpp

#include "Event.h"

namespace df {

    // Create base event with undefined event type.
    Event::Event() {
        // Set event type to undefined by default.
        event_type = UNDEFINED_EVENT;
    }

    /// Destructor.
    Event::~Event() {
    }

    // Set event type.
    void Event::setType(std::string new_type) {
        event_type = new_type;
    }

    // Get event type.
    std::string Event::getType() const {
        return event_type; 
    }
} // end of namespace df