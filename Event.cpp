//
// Event.cpp
//

#include "Event.h"

namespace df {

    Event::Event() {
        m_type = UNDEFINED_EVENT;
    }

    Event::~Event() {
        // Nothing to clean up
    }

    void Event::setType(std::string new_type) {
        m_type = new_type;
    }

    std::string Event::getType() const {
        return m_type;
    }

} // end namespace df
