//
// Animation.cpp
//

#include "Animation.h"
#include "LogManager.h"  // For logging

namespace df {

    Animation::Animation() {
        m_p_sprite = nullptr;
        m_name = "";
        m_index = 0;
        m_slowdown_count = 0;
    }

    void Animation::setSprite(Sprite* p_new_sprite) {
        m_p_sprite = p_new_sprite;
        m_index = 0;  // Reset to first frame
    }

    Sprite* Animation::getSprite() const {
        return m_p_sprite;
    }

    void Animation::setName(std::string new_name) {
        m_name = new_name;
    }

    std::string Animation::getName() const {
        return m_name;
    }

    void Animation::setIndex(int new_index) {
        if (m_p_sprite && new_index >= 0 && new_index < m_p_sprite->getFrameCount()) {
            m_index = new_index;
        }
    }

    int Animation::getIndex() const {
        return m_index;
    }

    void Animation::setSlowdownCount(int new_slowdown_count) {
        m_slowdown_count = new_slowdown_count;
    }

    int Animation::getSlowdownCount() const {
        return m_slowdown_count;
    }

    int Animation::draw(Vector position) {
        // If sprite is not defined, don't continue further.
        if (m_p_sprite == nullptr) {
            LM.writeLog("Animation::draw - Error: No associated sprite.");
            return -1;
        }

        // Ask the sprite to draw the current frame.
        int index = getIndex();
        m_p_sprite->draw(index, position);


        // If slowdown count is -1, animation is frozen.
        if (getSlowdownCount() == -1) {
            LM.writeLog("Animation::draw - Animation is frozen (slowdown count = -1).");
            return 0;
        }

        // Increment slowdown counter.
        int count = getSlowdownCount();
        count++;

        // Advance sprite index if appropriate.
        if (count >= m_p_sprite->getSlowdown()) {
            count = 0;  // Reset counter

            // Advance frame index.
            index++;

            // If at last frame, loop to beginning.
            if (index >= m_p_sprite->getFrameCount()) {
                index = 0;
            }

            // Set index for next draw().
            setIndex(index);
        }

        // Set counter for next draw().
        setSlowdownCount(count);

        return 0;
    }

    Box Animation::getBox() const {

        if (!m_p_sprite) {
            Box box(Vector(-0.5, -0.5), 0.99, 0.99);
            return box;
        }

        // Create Box around centered Sprite.
        Vector corner(-1 * m_p_sprite->getWidth() / 2.0,
                      -1 * m_p_sprite->getHeight() / 2.0);
        Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());

        return box;

    }

}
