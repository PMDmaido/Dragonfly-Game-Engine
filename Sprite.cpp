//
// Sprite.cpp 
//

#include "Sprite.h"

namespace df {
	/// Delete sprite, removing any allocated frames.
	Sprite::~Sprite() {
		if (m_frame != NULL)
			delete[] m_frame;
	}
	/// Create sprite with indicated maximum number of frames.
	Sprite::Sprite(int max_frames) {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_color = COLOR_DEFAULT;

		m_frame = new Frame[max_frames]; 
		m_max_frame_count = max_frames;

		m_slowdown = 1;
		m_transparency = 0;
	}
	Sprite::Sprite() {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_color = COLOR_DEFAULT;
		m_frame = nullptr;
		m_max_frame_count = 0;
		m_slowdown = 1;
		//m_transparency = 0;
	}

	/// Set width of sprite.
	void Sprite::setWidth(int new_width) {
		m_width = new_width;
	}
	/// Get width of sprite.
	int Sprite::getWidth() const {
		return m_width;
	}
	/// Set height of sprite.
	void Sprite::setHeight(int new_height) {
		m_height = new_height;
	}
	/// Get height of sprite.
	int Sprite::getHeight() const {
		return m_height;
	}
	/// Set sprite color.
	void Sprite::setColor(Color new_color) {
		m_color = new_color;
	}
	/// Get sprite color.
	Color Sprite::getColor() const {
		return m_color;
	}
	/// Get total count of frames in sprite.
	int Sprite::getFrameCount() const {
		return m_frame_count;
	}

	/// Add frame to sprite.
	/// Return -1 if frame array full, else 0.
	int Sprite::addFrame(Frame new_frame) {
		if (m_frame_count >= m_max_frame_count) {// Is Sprite array full?
			return -1;
		}
		m_frame[m_frame_count] = new_frame;
		m_frame_count++;
		return 0;
	}

	/// Get next sprite frame indicated by number.
	/// Return empty frame if out of range [0, m_frame_count-1].
	Frame Sprite::getFrame(int frame_number) const {
		if (frame_number < 0 || frame_number >= m_frame_count) {
			return Frame(); // Return empty frame if out of range.
		}
		return m_frame[frame_number];
	}

	/// Set animation slowdown.
	void Sprite::setSlowdown(int new_slowdown) {
		m_slowdown = new_slowdown;
	}
	/// Get animation slowdown.
	int Sprite::getSlowdown() const {
		return m_slowdown;
	}
	/// Set label associated with sprite.
	void Sprite::setLabel(std::string new_label) {
		m_label = new_label;
	}
	/// Get label associated with sprite.
	std::string Sprite::getLabel() const {
		return m_label;
	}

	// Set sprite transparency character.
	void Sprite::setTransparency(char new_transparency) {
		m_transparency = new_transparency;
	}

	// Get sprite transparency character.
	char Sprite::getTransparency() const {
		return m_transparency;
	}

	// Draw indicated frame centered at position (x,y).
	int Sprite::draw(int frame_number, Vector position, char transparency) const {
		if (frame_number < 0 || frame_number >= m_frame_count) {
			return -1; // Invalid frame number.
		}
		return m_frame[frame_number].draw(position, m_color, m_transparency); // Draw frame.
	}

} // end of namespace df