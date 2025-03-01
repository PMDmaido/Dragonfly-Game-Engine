#include "utility.h"
#include <cmath>

namespace df {

	// Return true if two positions intersect
	// (are within 1 unit of each other).
	// else return false.
    bool positionsIntersect(Vector p1, Vector p2) {
        if ( (std::abs(p1.getX() - p2.getX()) <= 1) &&
             (std::abs(p1.getY() - p2.getY()) <= 1)    ) {
			return true;
		}
		else {
			return false;
		} // end if
    }

	// Return true if two boxes intersect.
	bool boxIntersectsBox(Box A, Box B) {
		
        // Get the coordinates of Box A
        float Ax1 = A.getCorner().getX();
        float Ay1 = A.getCorner().getY();
        float Ax2 = Ax1 + A.getHorizontal();
        float Ay2 = Ay1 + A.getVertical();

        // Get the coordinates of Box B
        float Bx1 = B.getCorner().getX();
        float By1 = B.getCorner().getY();
        float Bx2 = Bx1 + B.getHorizontal();
        float By2 = By1 + B.getVertical();

        // Test horizontal overlap (x-overlap)
        bool x_overlap = (Bx1 <= Ax2 && Ax1 <= Bx2);

        // Test vertical overlap (y-overlap)
        bool y_overlap = (By1 <= Ay2 && Ay1 <= By2);

		return x_overlap && y_overlap;

	}

    // Return true if value is between min and max (inclusive).
    bool valueInRange(float value, float min, float max) {
        return (value >= min) && (value <= max);
    }

    // Convert relative bounding Box for Object to absolute world Box.
    Box getWorldBox(const Object* p_o) {
        return getWorldBox(p_o, p_o->getPosition());
    }

    // Convert relative bounding Box for Object to absolute world Box at position where.
    Box getWorldBox(const Object* p_o, Vector where) {
        // Get the object's bounding box (relative)
        Box box = p_o->getBox();
        // Get the box's current corner position
        Vector corner = box.getCorner();
        // Convert to absolute world position
        corner.setX(corner.getX() + where.getX());
        corner.setY(corner.getY() + where.getY());
        // Update the box with the new absolute position
        box.setCorner(corner);
        return box;
    }

    // Return true if Box contains Position.
    bool boxContainsPosition(Box b, Vector p) {
        float x1 = b.getCorner().getX();
        float y1 = b.getCorner().getY();
        float x2 = x1 + b.getHorizontal();
        float y2 = y1 + b.getVertical();

        return (valueInRange(p.getX(), x1, x2) && valueInRange(p.getY(), y1, y2));
    }

    // Return true if Box1 completely contains Box2.
    bool boxContainsBox(Box b1, Box b2) {
        Vector b2_corner = b2.getCorner();
        Vector b2_top_right(b2_corner.getX() + b2.getHorizontal(), b2_corner.getY());
        Vector b2_bottom_left(b2_corner.getX(), b2_corner.getY() + b2.getVertical());
        Vector b2_bottom_right(b2_corner.getX() + b2.getHorizontal(), b2_corner.getY() + b2.getVertical());

        return boxContainsPosition(b1, b2_corner) &&
            boxContainsPosition(b1, b2_top_right) &&
            boxContainsPosition(b1, b2_bottom_left) &&
            boxContainsPosition(b1, b2_bottom_right);
        /*
        Vector b2Corner = b2.getCorner();
        Vector b2Opposite(b2Corner.getX() + b2.getHorizontal(), b2Corner.getY() + b2.getVertical());

        return boxContainsPosition(b1, b2Corner) && boxContainsPosition(b1, b2Opposite);
*/
    }

    // Return distance between any two positions.
    float distance(Vector p1, Vector p2) {
        float dx = p2.getX() - p1.getX();
        float dy = p2.getY() - p1.getY();
        return sqrt(dx * dx + dy * dy);
    }

	// Convert world position to view position.
	Vector worldToView(Vector world_pos) {
        // Get the top-left corner of the current view
        Vector view_origin = WM.getView().getCorner();

        // Convert world coordinates to view coordinates
        Vector view_pos(world_pos.getX() - view_origin.getX(),
            world_pos.getY() - view_origin.getY());

        return view_pos;
       
	}

    Vector viewToWorld(Vector view_pos) {
        Vector view_origin = WM.getView().getCorner();
        float view_x = view_origin.getX();
        float view_y = view_origin.getY();
        Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
        return world_pos;
    }

    // Convert int to a string, returning the string.
    std::string toString(int i) {
        std::stringstream ss;  // Create stringstream.
        ss << i;          // Add number to stream.
        return ss.str();  // Return string with contents of stream.
    }

} // end of namespace df
