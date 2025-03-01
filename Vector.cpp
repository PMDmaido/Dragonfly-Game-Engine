// Vector.cpp

// Engine includes
#include "Vector.h"
#include <math.h> // For sqrt()

namespace df {
	// Create Vector with (x , y ).
	Vector::Vector(float init_x, float init_y) {
		m_x = init_x;
		m_y = init_y;
	}

	// Defeault 2d (x,y) is (0,0).
	Vector::Vector() {
		m_x = 0;
		m_y = 0;
	}

	// Get horizontal component.
	float Vector::getX() const {
		return m_x;
	}
	// Set horizontal component.
	void Vector::setX(float new_x) {
		m_x = new_x;
	}
	// Get vertical component.
	float Vector::getY() const {
		return m_y;
	}
	// Set vertical component.
	void Vector::setY(float new_y) {
		m_y = new_y;
	}
	// Set horizontal and vertical components.
	void Vector::setXY(float new_x, float new_y) {
		m_x = new_x;
		m_y = new_y;
	}

	// Returns magnitude of vector.
	float Vector::getMagnitude() const {
		float mag = sqrt(m_x * m_x + m_y * m_y); // Pythagorean theorem square root of x^2 + y^2
		return mag;
	}

	// Scale vector.
	// Resizes (changes the magnitude) of the vector by the scale factor, leaving the direction for the vector unchanged
	//void Vector::scale(float s) {
	Vector Vector::scale(float s) const {
		//m_x *= s;
		//m_y *= s;
		return Vector(m_x * s, m_y * s); // Return new vector
	}

	// Normalize vector.
	/* Takes a vector of any length and,
	Keeping it pointing in the same direction, changes its length to 1 (also called a unit vector).
	The if check is to avoid a possible division by zero.*/
	void Vector::normalize() {
		float mag = getMagnitude();
		if (mag > 0.0001f) { // mag > 0
			m_x /= mag;
			m_y /= mag;
		}
	}

	Vector Vector::operator+(const Vector& other) const {
		Vector v(m_x + other.m_x, m_y + other.m_y);
		// Vector v (v.x, v.y) >> Create new vector
		// v.x = x + other.x; >> Add x components
		// v.y = y + other.y; >> Add y components
		return v;
	}

	Vector Vector::operator-(const Vector& other) const {
		return Vector(m_x - other.m_x, m_y - other.m_y);
	}


} // end of namespace df