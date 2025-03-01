///
/// A 2d (x,y) vector
///

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <string>

namespace df {
	class Vector {
	private:
		float m_x; // Horizontal component .
		float m_y; // Vertical component .
	public:
		// Create Vector with (x , y ).
		Vector(float init_x, float init_y);

		// Defeault 2d (x,y) is (0,0).
		Vector();

		// Get/set horizontal component.
		void setX(float new_x);
		float getX() const;

		// Get/set vertical component.
		void setY(float new_y);
		float getY() const;

		// Set horizontal and vertical components.
		void setXY(float new_x, float new_y);

		// Return magnitude of vector .
		float getMagnitude() const;

		// Normalize vector.
		void normalize();

		// Scale vector.
		//void scale(float s);
		Vector scale(float s) const;

		// Add two vectors, return new vector.
		Vector operator+(const Vector& other) const;

		Vector operator-(const Vector& other) const;
	};

} // end of namespace df
#endif //__VECTOR_H__
