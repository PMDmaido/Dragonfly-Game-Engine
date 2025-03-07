#pragma once
//
// Frame.h
//
#include <string>
#include "Vector.h"
#include "Color.h"

namespace df {

    class Frame {
    private:
        int m_width;               // Width of frame.
        int m_height;              // Height of frame.
        std::string m_frame_str;   // All frame characters stored as string.

    public:
        // Create an empty frame.
        Frame();

        // Create a frame with indicated width, height, and string.
        Frame(int new_width, int new_height, std::string frame_str);

        // Set width of frame.
        void setWidth(int new_width);

        // Get width of frame.
        int getWidth() const;

        // Set height of frame.
        void setHeight(int new_height);

        // Get height of frame.
        int getHeight() const;

        // Set frame characters (stored as a string).
        void setString(std::string new_frame_str);

        // Get frame characters (stored as a string).
        std::string getString() const;

        // Draw self, centered at position (x, y) with color.
        // Return 0 if OK, else -1.
        // Note: Top-left coordinate is (0,0).
        int draw(Vector position, Color color) const;
    };

}