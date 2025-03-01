#ifndef UTILITY_H 
#define UTILITY_H

#include "Vector.h"
#include "Box.h"
//#include "Object.h" 
#include "Line.h"
#include "Circle.h"
#include "WorldManager.h"
#include "Object.h"

#include <sstream>
#include <string>


using std::stringstream;
using std::string;

namespace df {
    // Return true if two positions intersect 
    // (are within 1 unit of each other).
	// else return false.
    bool positionsIntersect(Vector p1, Vector p2);

	// Return true if two boxes intersect.
    bool boxIntersectsBox(Box A, Box B);

    // Optional

    // Return true if value is between min and max (inclusive).
    bool valueInRange(float value, float min, float max);

    // Convert relative bounding Box for Object to absolute world Box.
    Box getWorldBox(const Object* p_o); 

    // Convert relative bounding Box for Object to absolute world Box at position where.
    Box getWorldBox(const Object* p_o, Vector where); 

    // Return true if Box contains Position.
    bool boxContainsPosition(Box b, Vector p);

    // Return true if Box1 completely contains Box2.
    bool boxContainsBox(Box b1, Box b2);

    // Return true if Line segments intersect. 
    // (Parallel line segments don't intersect)
    //bool lineIntersectsLine(Line line1, Line line2);

    // Return true if Line intersects Box.
    //bool lineIntersectsBox(Line line, Box b);

    // Return true if Circle intersects or contains Box.
    //bool circleIntersectsBox(Circle circle, Box b);

    // Return distance between any two positions.
    float distance(Vector p1, Vector p2);

    // End of optional

	// Convert world position to view position.
    Vector worldToView(Vector world_pos);

	// Convert view position to world position.
	Vector viewToWorld(Vector view_pos);

    // Convert int to a string, returning the string.
    std::string toString(int i);

}

#endif // UTILITY_H
