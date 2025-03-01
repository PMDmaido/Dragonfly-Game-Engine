// 
// Frame.cpp
//

// Engine includes.
#include "Frame.h"
#include "LogManager.h"

#include "DisplayManager.h"

namespace df {

	/// Create empty frame.
	Frame::Frame() {
		m_width = 0;
		m_height = 0;
		m_frame_str = "";
	}

	/// Create frame of indicated width and height with string.
	Frame::Frame(int new_width, int new_height, std::string frame_str) {
		m_width = new_width;
		m_height = new_height;
		m_frame_str = frame_str;
	}

	/// Set width of frame.
	void Frame::setWidth(int new_width) {
		m_width = new_width;
	}

	/// Get width of frame.
	int Frame::getWidth() const {
		return m_width;
	}

	/// Set height of frame.
	void Frame::setHeight(int new_height) {
		m_height = new_height;
	}

	/// Get height of frame.
	int Frame::getHeight() const {
		return m_height;
	}

	/// Set frame characters (stored as string).
	void Frame::setString(std::string new_frame_str) {
		m_frame_str = new_frame_str;
	}

	/// Get frame characters (stored as string).
	std::string Frame::getString() const {
		return m_frame_str;
	}
	/// Draw self, centered at position (x,y) with color.
	/// Don't draw transparent characters (0 means none).
	/// Return 0 if ok, else -1.
	/// Note: top-left coordinate is (0,0).
	int Frame::draw(Vector position, Color color, char transparency) const {

		// Error check empty strings
		if (m_frame_str.empty()) {
			LM.writeLog("Frame::draw - Error: Frame string is empty.");
			return -1; // Error: Empty frame
		}

		// Determine offset since centered at position.
		int x_offset = m_width / 2; // frame.getWidth () 
		int y_offset = m_height / 2; // frame.getHeight ()

		//LM.writeLog("Frame::draw - Calculated offsets: x_offset = %d, y_offset = %d", x_offset, y_offset);

		// Draw character by character.
		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				Vector temp_pos(position.getX() + x - x_offset,
								position.getY() + y - y_offset);
				// Log each character placement
				//LM.writeLog("Frame::draw: Drawing char '%c' at position (%d, %d)",
					//m_frame_str[y * m_width + x], temp_pos.getX(), temp_pos.getY()); 

				DM.drawCh(temp_pos, m_frame_str[y*m_width + x], color);
			} // end x
		} // end y
		LM.writeLog("Frame::draw: Finished drawing frame successfully."); 
		return 0;

	} // end draw

	
} // end of namespace df

