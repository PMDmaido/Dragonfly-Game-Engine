//
// EventView.cpp
//

#include "EventView.h"

namespace df {
    // Default constructor: sets VIEW_EVENT, value = 0, delta = false.
    EventView::EventView() {
        setType(VIEW_EVENT);
        m_tag = "";
        m_value = 0;
        m_delta = false;
    }

    // Constructor with parameters.
    EventView::EventView(std::string new_tag, int new_value, bool new_delta) {
        setType(VIEW_EVENT);
        m_tag = new_tag;
        m_value = new_value;
        m_delta = new_delta;
    }

    // Set the tag.
    void EventView::setTag(std::string new_tag) {
        m_tag = new_tag;
    }

    // Get the tag.
    std::string EventView::getTag() const {
        return m_tag;
    }

    // Set the value.
    void EventView::setValue(int new_value) {
        m_value = new_value;
    }

    // Get the value.
    int EventView::getValue() const {
        return m_value;
    }

    // Set delta.
    void EventView::setDelta(bool new_delta) {
        m_delta = new_delta;
    }

    // Get delta.
    bool EventView::getDelta() const {
        return m_delta;
    }

}