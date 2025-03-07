#pragma once
//
// Box.h
//
#include "Vector.h"

namespace df {
    class Box {
    private:
        Vector m_corner;      // Upper left corner of the box.
        float m_horizontal;   // Horizontal dimension.
        float m_vertical;     // Vertical dimension.

    public:
        // Create a box with (0,0) for the corner, and 0 for horizontal and vertical dimensions.
        Box();

        // Create a box with an upper-left corner, horizontal and vertical sizes.
        Box(Vector init_corner, float init_horizontal, float init_vertical);

        // Set upper left corner of box.
        void setCorner(Vector new_corner);

        // Get upper left corner of box.
        Vector getCorner() const;

        // Set horizontal size of box.
        void setHorizontal(float new_horizontal);

        // Get horizontal size of box.
        float getHorizontal() const;

        // Set vertical size of box.
        void setVertical(float new_vertical);

        // Get vertical size of box.
        float getVertical() const;
    };
}