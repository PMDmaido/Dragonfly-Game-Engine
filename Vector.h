#pragma once
//
// Vector.h
//

namespace df {
	class Vector {
	private:
		float m_x;	// Horizontal component.
		float m_y;	// Vertical component.

	public:

		// Create Vector with (x,y)
		Vector(float intit_x, float init_y);

		// Default 2d (x,y) is (0,).
		Vector();

		// Get/set horizontal component.
		void setX(float new_x);
		float getX() const;

		// Get/set vertical component.
		void setY(float new_x);
		float getY() const;

		// Set horizaontal & veritcal components.
		void setXY(float new_x, float new_y);

		// Return magnitudie of vector.
		float getMagnitude() const;

		// Normalize vector.
		void normalize();

		// Scale vector.
		void scale(float s) const;

		// Add two Vectors, return new Vector.
		Vector operator+(const Vector& other) const;

	};

}