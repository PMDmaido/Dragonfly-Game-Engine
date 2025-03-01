//
// Line.cpp
//

#include "Line.h"
#include <cmath>  // For sqrt()
#include <sstream> // For toString()

namespace df {

    // Create line segment from p1 to p2.
    Line::Line(Vector init_p1, Vector init_p2) {
        m_p1 = init_p1;
        m_p2 = init_p2;
    }

    // Default line segment is at (0,0).
    Line::Line() {
        m_p1 = Vector(0, 0);
        m_p2 = Vector(0, 0);
    }

    // Set first endpoint.
    void Line::setP1(Vector new_p1) {
        m_p1 = new_p1;
    }

    // Get first endpoint.
    Vector Line::getP1() const {
        return m_p1;
    }

    // Set second endpoint.
    void Line::setP2(Vector new_p2) {
        m_p2 = new_p2;
    }

    // Get second endpoint.
    Vector Line::getP2() const {
        return m_p2;
    }

    // Return attributes as a string.
    std::string Line::toString() const {
        std::ostringstream oss;
        oss << "Line: P1(" << m_p1.getX() << ", " << m_p1.getY() << ") - "
            << "P2(" << m_p2.getX() << ", " << m_p2.getY() << ")";
        return oss.str();
    }

    // Draw pixel line (placeholder function).
    void Line::draw() const {
        // This function would normally use a graphics API.
        // For now, it serves as a placeholder for rendering logic.
    }

} // end of namespace df
