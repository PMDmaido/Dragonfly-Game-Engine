#pragma once
//
// Animation.h
//

#include <string>
#include "Sprite.h"
#include "Box.h"

namespace df {
    class Animation {
    private:
        Sprite* m_p_sprite;       // Associated sprite for the animation.
        std::string m_name;       // Sprite name in ResourceManager.
        int m_index;              // Current index frame for the sprite.
        int m_slowdown_count;     // Slowdown counter.

    public:
        // Constructor
        Animation();

        // Set associated sprite to a new one.
        // Note: The sprite is managed by ResourceManager.
        // Sets sprite index to 0 (first frame).
        void setSprite(Sprite* p_new_sprite);

        // Return pointer to associated sprite.
        Sprite* getSprite() const;

        // Set sprite name (in ResourceManager).
        void setName(std::string new_name);

        // Get sprite name (in ResourceManager).
        std::string getName() const;

        // Set index of current sprite frame to be displayed.
        void setIndex(int new_index);

        // Get index of current sprite frame to be displayed.
        int getIndex() const;

        // Set animation slowdown count (-1 means stop animation).
        void setSlowdownCount(int new_slowdown_count);

        // Get animation slowdown count (-1 means stop animation).
        int getSlowdownCount() const;

        // Draw single frame centered at position (x, y).
        // Drawing accounts for slowdown, and advances sprite frame.
        // Return 0 if ok, else -1.
        int draw(Vector position);

        Box getBox() const;
    };
}