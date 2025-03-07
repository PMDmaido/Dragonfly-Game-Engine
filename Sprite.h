#pragma once
//
// Sprite.h
//

#include <string>
#include "Frame.h"

namespace df {
    class Sprite {
    private:
        int m_width;              // Sprite width.
        int m_height;             // Sprite height.
        int m_max_frame_count;    // Max number of frames sprite can have.
        int m_frame_count;        // Actual number of frames sprite has.
        Color m_color;            // Optional color for the entire sprite.
        int m_slowdown;           // Animation slowdown (1=no slowdown, 0=stop).
        Frame* m_frame;           // Array of frames.
        std::string m_label;      // Text label to identify sprite.

    public:
        // Constructor with no arguments.
        Sprite();

        // Destructor to delete allocated frames.
        ~Sprite();

        // Create sprite with indicated maximum number of frames.
        Sprite(int max_frames);

        // Set width of sprite.
        void setWidth(int new_width);

        // Get width of sprite.
        int getWidth() const;

        // Set height of sprite.
        void setHeight(int new_height);

        // Get height of sprite.
        int getHeight() const;

        // Set sprite color.
        void setColor(Color new_color);

        // Get sprite color.
        Color getColor() const;

        // Get total count of frames in sprite.
        int getFrameCount() const;

        // Add frame to sprite. Returns -1 if the frame array is full, else 0.
        int addFrame(Frame new_frame);

        // Get next sprite frame indicated by number.
        // Return empty frame if out of range [0, m_frame_count - 1].
        Frame getFrame(int frame_number) const;

        // Set label associated with the sprite.
        void setLabel(std::string new_label);

        // Get label associated with the sprite.
        std::string getLabel() const;

        // Set animation slowdown value.
        void setSlowdown(int new_sprite_slowdown);

        // Get animation slowdown value.
        int getSlowdown() const;

        // Draw indicated frame centered at position (x, y).
        // Returns 0 if ok, else -1.
        int draw(int frame_number, Vector position) const;
    };
}