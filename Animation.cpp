//
// Animation.cpp
//

#include "Animation.h"
#include "LogManager.h"

namespace df {

    Animation::Animation() {
        m_p_sprite = nullptr;
        m_index = 0;
        m_slowdown_count = 0;
        m_name = "";
        //m_modified = false;
    }

    void Animation::setSprite(Sprite* p_new_sprite) {
        m_p_sprite = p_new_sprite;
        m_index = 0; // Reset to first frame.
        //m_modified = true;
    }

    const Sprite* Animation::getSprite() const {
        return m_p_sprite;
    }

    void Animation::setName(std::string new_name) {
        m_name = new_name;
        //m_modified = true;
    }

    std::string Animation::getName() const {
        return m_name;
    }

    void Animation::setIndex(int new_index) {
        //m_index = new_index;
        //m_modified = true;
        if (m_p_sprite && new_index >= 0 && new_index < m_p_sprite->getFrameCount()) {
            m_index = new_index;
        }
    }

    int Animation::getIndex() const {
        return m_index;
    }

    void Animation::setSlowdownCount(int new_slowdown_count) {
        m_slowdown_count = new_slowdown_count;
        //m_modified = true;
    }

    int Animation::getSlowdownCount() const {
        return m_slowdown_count;
    }


    int Animation::draw(Vector position) {
        
		// If sprite is not defined, return -1.
        if (m_p_sprite == NULL) {
            return -1; // No sprite associated.
        }

        // Draw the current frame.
		m_index = getIndex(); // Get current frame.

        //Sprite::draw(frame_number, position, m_p_sprite->getTransparency());
        //m_p_sprite->draw(m_index, position, m_p_sprite->getTransparency());  
        if (m_p_sprite->draw(m_index, position, m_p_sprite->getTransparency()) == -1) {
            LM.writeLog("Animation::draw - Error: Failed to draw frame %d.", m_index);
            return -1;
        }

        // If slowdown count is -1, animation is frozen.
        if (getSlowdownCount() == -1) { 
            LM.writeLog("Animation::draw - Animation is frozen (slowdown count = -1).");
            return 0;
        }

        // Increment slowdown counter.
		m_slowdown_count = getSlowdownCount(); // Get current slowdown count.
        m_slowdown_count++;

        // Advance sprite index, if it's time to 
        if (m_slowdown_count >= m_p_sprite->getSlowdown()) {
            m_slowdown_count = 0; // Reset counter.
            m_index++; // Advance frame. 
             
            // If at last frame, loop back to the beginning.
            if (m_index >= m_p_sprite->getFrameCount()) {
                m_index = 0;
            }

            //m_modified = true;
			setIndex(m_index); // Set new frame. 
        } // end if 

		// Set new slowdown counter for next draw().
		setSlowdownCount(m_slowdown_count); 

        return 0;
    }

    /// Get bounding box of associated Sprite.
    Box Animation::getBox() const {

		// If no Sprite, return unit Box centered at (0, 0).
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


} // end of namespace df