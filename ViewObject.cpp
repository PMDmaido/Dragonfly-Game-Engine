// 
// ViewObject.cpp
//

#include "ViewObject.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "EventView.h"

namespace df {

    ViewObject::ViewObject() {
        // Initialize Object attributes.
        setSolidness(SPECTRAL);
        setAltitude(MAX_ALTITUDE);
        setType("ViewObject");

        // Initialize ViewObject attributes.
        setValue(0);
        setDrawValue();
        setBorder(true);
        setLocation(TOP_CENTER);
        setColor(COLOR_DEFAULT);

    }

    int ViewObject::draw() {
        // Construct the string to display.
        std::string temp_str;
        if (m_border) {
            temp_str = " " + getViewString() + " " + toString(m_value) + " ";
        }
        else {
            temp_str = getViewString() + " " + toString(m_value);
        }

        // Convert view coordinates to world coordinates.
        Vector pos = viewToWorld(getPosition());

        // Draw the string centered at the position.
        DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

        // Draw a border around the display if enabled.
        if (m_border) {
            // Implementation for drawing a box around the display.
            // You can add logic here to draw a rectangle using DM.
        }

        return 0;
    }

    int ViewObject::eventHandler(const Event* p_e) {
        // Check if this is a 'view' event.
        if (p_e->getType() == VIEW_EVENT) {
            const EventView* p_ve = static_cast<const EventView*>(p_e);

            // Check if this event is meant for this ViewObject.
            if (p_ve->getTag() == getViewString()) {
                // Update the value either by adding (if delta is true) or replacing it.
                if (p_ve->getDelta()) {
                    setValue(getValue() + p_ve->getValue());  // Change in value.
                }
                else {
                    setValue(p_ve->getValue());  // New value.
                }

                // Event was handled successfully.
                return 1;
            }
        }

        // If here, event was not handled. Call parent eventHandler().
        return Object::eventHandler(p_e);
    }

    void ViewObject::setLocation(ViewObjectLocation new_location) {
        Vector p; // Position of the ViewObject
        int y_delta = 0;

        // Set new position based on location.
        switch (new_location) {
        case ViewObjectLocation::TOP_LEFT:
            p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
            if (!getBorder()) {
                y_delta = -1;
            }
            break;
        case ViewObjectLocation::TOP_CENTER:
            p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
            if (!getBorder()) {
                y_delta = -1;
            }
            break;
        case ViewObjectLocation::TOP_RIGHT:
            p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
            if (!getBorder()) {
                y_delta = -1;
            }
            break;
        case ViewObjectLocation::CENTER_LEFT:
            p.setXY(WM.getView().getHorizontal() * 1 / 6,
                WM.getView().getVertical() / 2);
            break;
        case ViewObjectLocation::CENTER_CENTER:
            p.setXY(WM.getView().getHorizontal() * 3 / 6,
                WM.getView().getVertical() / 2);
            break;
        case ViewObjectLocation::CENTER_RIGHT:
            p.setXY(WM.getView().getHorizontal() * 5 / 6,
                WM.getView().getVertical() / 2);
            break;
        case ViewObjectLocation::BOTTOM_LEFT:
            p.setXY(WM.getView().getHorizontal() * 1 / 6,
                WM.getView().getVertical() - 2);
            break;
        case ViewObjectLocation::BOTTOM_CENTER:
            p.setXY(WM.getView().getHorizontal() * 3 / 6,
                WM.getView().getVertical() - 2);
            break;
        case ViewObjectLocation::BOTTOM_RIGHT:
            p.setXY(WM.getView().getHorizontal() * 5 / 6,
                WM.getView().getVertical() - 2);
            break;
        default:
            break;
        }

        // Shift, as needed, based on border.
        p.setY(p.getY() + y_delta);

        // Set position of object to new position.
        setPosition(p);

        // Set new location.
        m_location = new_location;
    }

    ViewObjectLocation ViewObject::getLocation() const {
        return m_location;
    }

    void ViewObject::setValue(int new_value) {
        m_value = new_value;
    }

    int ViewObject::getValue() const {
        return m_value;
    }

    void ViewObject::setBorder(bool new_border) {
        if (m_border != new_border) {
            m_border = new_border;

            // Reset location to account for border setting.
            setLocation(getLocation());
        }
    }

    bool ViewObject::getBorder() const {
        return m_border;
    }

    // Set and get text color.
    void ViewObject::setColor(Color new_color) {
        m_color = new_color;
    }
    Color ViewObject::getColor() const {
        return m_color;
    }

    // Set and get view display string.
    void ViewObject::setViewString(std::string new_view_string) {
        view_string = new_view_string;
    }
    std::string ViewObject::getViewString() const {
        return view_string;
    }

    // Set and get draw value flag.
    void ViewObject::setDrawValue(bool new_draw_value) {
        m_draw_value = new_draw_value;
    }
    bool ViewObject::getDrawValue() const {
        return m_draw_value;
    }
}