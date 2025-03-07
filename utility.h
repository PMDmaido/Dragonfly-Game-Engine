#pragma once
//
// utility.h
//

#include "Vector.h"
#include "Box.h"
#include "Object.h"

namespace df {

	// Return true if two positions intersect, else false.
	bool positionsIntersect(Vector p1, Vector p2);

	// Return true if boxes intersect, else false.
	bool boxIntersectsBox(Box A, Box B);

	// Convert a relative bounding Box for Object.
	Box getWorldBox(const Object* p_o);

	// Convert a relative bounding Box for Object to an absolute world Box at a given position.
	Box getWorldBox(const Object* p_o, Vector where);

	// Convert world position to view position.
	Vector worldToView(Vector world_pos);

	// Convert view position to world position.
	Vector viewToWorld(Vector view_pos);

	// Convert int to a string, returning a string.
	std::string toString(int i);
}