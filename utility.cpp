//
// utility.cpp
//

#include "utility.h"
#include <stdlib.h>
#include "WorldManager.h"
#include <sstream>
#include <string>
#include "LogManager.h"

namespace df {

	bool positionsIntersect(Vector p1, Vector p2) {
		return abs((int)(p1.getX() - p2.getX())) <= 1
			&& abs((int)(p1.getY() - p2.getY())) <= 1;	}

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
        bool x_overlap = (Bx1 <= Ax1 && Ax1 <= Bx2) ||
                          (Ax1 <= Bx1 && Bx1 <= Ax2);

        // Test vertical overlap (y-overlap)
        bool y_overlap = (By1 <= Ay1 && Ay1 <= By2) ||
                         (Ay1 <= By1 && By1 <= Ay2);

        // If both x-overlap and y-overlap exist, boxes intersect
        return x_overlap && y_overlap;
    }

    Box getWorldBox(const Object* p_o) {

        Box box = p_o->getBox();
        Vector corner = box.getCorner();

        corner.setX(corner.getX() + p_o->getPosition().getX());
        corner.setY(corner.getY() + p_o->getPosition().getY());

        box.setCorner(corner);

        return box;
    }

    Box getWorldBox(const Object* p_o, Vector where) {

        Box box = p_o->getBox();
        Vector corner = box.getCorner();

        corner.setX(corner.getX() + where.getX());
        corner.setY(corner.getY() + where.getY());

        box.setCorner(corner);

        return box;
    }

    Vector worldToView(Vector world_pos) {
        Vector view_origin = WM.getView().getCorner();
        float view_x = view_origin.getX();
        float view_y = view_origin.getY();
        Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
        return view_pos;
    }

    Vector viewToWorld(Vector view_pos) {
        Vector view_origin = WM.getView().getCorner();
        float view_x = view_origin.getX();
        float view_y = view_origin.getY();
        Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
        return world_pos;
    }

    std::string toString(int i) {
        std::stringstream ss;  // Create stringstream.
        ss << i;          // Add number to stream.
        return ss.str();  // Return string with contents of stream.
    }

}