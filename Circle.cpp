//
// Circle.cpp
//

#include "Circle.h"
#include <sstream> // For toString()

namespace df {

    // Create circle at center with radius r.
    Circle::Circle(Vector init_center, float init_radius) {
        m_center = init_center;
        m_radius = init_radius;
    }

    // Default circle is at (0,0) with radius 0.
    Circle::Circle() {
        m_center = Vector(0, 0);
        m_radius = 0;
    }

    // Set center.
    void Circle::setCenter(Vector new_center) {
        m_center = new_center;
    }

    // Get center.
    Vector Circle::getCenter() const {
        return m_center;
    }

    // Set radius.
    void Circle::setRadius(float new_radius) {
        m_radius = new_radius;
    }

    // Get radius.
    float Circle::getRadius() const {
        return m_radius;
    }

    // Return attributes as a string.
    std::string Circle::toString() const {
        std::ostringstream oss;
        oss << "Circle: Center(" << m_center.getX() << ", " << m_center.getY()
            << "), Radius: " << m_radius;
        return oss.str();
    }

} // end of namespace df
