// 
// Box.cpp
//

#include "Box.h"

namespace df {
	// Create box with upper-left corner, horiz and vert sizes.
	Box::Box(Vector init_corner, float init_horizontal, float init_vertical) {
		m_corner = init_corner;
		m_horizontal = init_horizontal;
		m_vertical = init_vertical;
	}
	// Create box with (0,0) for corner, and 0 for horiz and vert.
	Box::Box() {
		m_corner = Vector(0, 0);
		m_horizontal = 0;
		m_vertical = 0;
	}
	// Set upper left corner of box.
	void Box::setCorner(Vector new_corner) {
		m_corner = new_corner;
	}
	// Get upper left corner of box.
	Vector Box::getCorner() const {
		return m_corner;
	}
	// Set horizontal size of box.
	void Box::setHorizontal(float new_horizontal) {
		m_horizontal = new_horizontal;
	}
	// Get horizontal size of box.
	float Box::getHorizontal() const {
		return m_horizontal;
	}
	// Set vertical size of box.
	void Box::setVertical(float new_vertical) {
		m_vertical = new_vertical;
	}
	// Get vertical size of box.
	float Box::getVertical() const {
		return m_vertical;
	}
} // end of namespace df

/*
// Return attributes as string.
	std::string Box::toString() const {
		return "Box";
	}
	// Compare two boxes.
	bool Box::operator==(const Box& other) const {
		return m_corner == other.m_corner && m_horizontal == other.m_horizontal && m_vertical == other.m_vertical;
	}
	bool Box::operator!=(const Box& other) const {
		return !(*this == other);
	}
	// Draw box outline in pixels.
	void Box::draw() {
		// Draw horizontal lines.
		for (int i = 0; i < m_horizontal; i++) {
			// Draw left side.
			// Draw right side.
		}
		// Draw vertical lines.
		for (int i = 0; i < m_vertical; i++) {
			// Draw top side.
			// Draw bottom side.
		}
	}
	// Serialize attributes to stream.
	// Return 0 if ok, else -1.
	int Box::serialize(std::stringstream* p_ss) const {
		// Write to stream.
		*p_ss << m_corner.getX() << "
*/