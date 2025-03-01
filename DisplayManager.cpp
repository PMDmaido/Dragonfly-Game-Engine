// DisplayManager.cpp

// Engine includes.
#include "DisplayManager.h"
#include "LogManager.h"

namespace df {

    // Private constructor for singleton.
    DisplayManager::DisplayManager() {
		setType("DisplayManager");
        m_p_window = nullptr;
        m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT; 
        m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
        m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT; 
        m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT; 
    }

    // Get the one and only instance of the DisplayManager.
    DisplayManager& DisplayManager::getInstance() {
        static DisplayManager instance;
        return instance;
    }

    // Open graphics window, ready for text-based display.
    int DisplayManager::startUp() {
		// if window already created, do nothing
        if (m_p_window != nullptr) {
            return 0; // No more work to do, but ok
		} // end if

		// Create SFML window.		
		//m_p_window = new sf::RenderWindow(); /// WILL GET BACK TO THIS LATER
		m_p_window = new sf::RenderWindow(sf::VideoMode
		({(unsigned int) m_window_horizontal_pixels, (unsigned int) m_window_vertical_pixels}),
			WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

		if (!m_p_window) {
			LM.writeLog("Error: Unable to create SFML window.");
			return -1;
		}

		// Turn off mouse cursor for window: window.setMouseCursorVisible(false);
        m_p_window->setMouseCursorVisible(false);         

		// Synchronize refresh rate (window drawing) with monitor: window.setVerticalSyncEnabled(true); 
        m_p_window->setVerticalSyncEnabled(true);  

        // Load font.
        if (!m_font.openFromFile(FONT_FILE_DEFAULT)) {
            LM.writeLog("DisplayManager::startUp(): Error loading font '%s'", FONT_FILE_DEFAULT.c_str()); 
            return -1; // Error: Font loading failed.
        } // end if

		return Manager::startUp(); // Call parent startUp, return 0 if ok, else -1.
    }

    // Close graphics window.
    void DisplayManager::shutDown() {
		if (m_p_window != nullptr) {
			m_p_window->close();
			delete m_p_window;
			m_p_window = nullptr;
		} // end if
		Manager::shutDown(); // Call parent shutDown.
    }

    // Draw character at window location (x,y) with color.
    int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
		// Make sure window is allocated.
        if (m_p_window == nullptr) {
			return -1; // Error: No window to draw to.
		} // end if

		// Convert space (x,y) into pixels (x,y).
		Vector pixel_pos = spacesToPixels(world_pos);

		// Convert world coordinates to view coordinates.
		//Vector view_pos = worldToView(world_pos);

		// Draw background rectangle since text is "see through" in SFML.
		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
		rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
		rectangle.setPosition({pixel_pos.getX() - charWidth()/10, 
                               pixel_pos.getY() + charHeight()/5});
		m_p_window->draw(rectangle);

		// Create character text to draw.
		static sf::Text text(m_font);
		text.setString(ch);
		text.setStyle(sf::Text::Bold); // Set Bold

        // Scale to right size.
		if (charWidth() < charHeight()) {
			text.setCharacterSize(charWidth() * 2);
		}
		else {
			text.setCharacterSize(charHeight() * 2);
		} // end if

		// Set SFML color based on Dragonfly color.
        switch (color)
        {
		case RED:     text.setFillColor(sf::Color::Red); break;
		case GREEN:   text.setFillColor(sf::Color::Green); break;
		case YELLOW:  text.setFillColor(sf::Color::Yellow); break;
		case BLUE:    text.setFillColor(sf::Color::Blue);	break;
		case MAGENTA: text.setFillColor(sf::Color::Magenta); break;
		case CYAN:    text.setFillColor(sf::Color::Cyan);	break;
        default:      text.setFillColor(sf::Color::White); break;
		} // end switch

		// Set position of text in window (in pixels).
		text.setPosition({ pixel_pos.getX(), pixel_pos.getY() }); 

		// Draw character.
		m_p_window->draw(text); // Draw text.

		return 0; // Success.
    }

    // Return window's horizontal maximum (in characters).
    int DisplayManager::getHorizontal() const {
        return m_window_horizontal_chars;
    }

    // Return window's vertical maximum (in characters).
    int DisplayManager::getVertical() const {
        return m_window_vertical_chars;
    }

    // Return window's horizontal maximum (in pixels).
    int DisplayManager::getHorizontalPixels() const {
        return m_window_horizontal_pixels;
    }

    // Return window's vertical maximum (in pixels).
    int DisplayManager::getVerticalPixels() const {
        return m_window_vertical_pixels;
    }

    // Render current window buffer.
    int DisplayManager::swapBuffers() {
		if (m_p_window == nullptr) {
			return -1; // Error: No window to swap.
		} // end if

		m_p_window->display(); 
		m_p_window->clear();
		//m_p_window->clear(WINDOW_BACKGROUND_COLOR_DEFAULT);
		return 0;
    }

    // Return pointer to SFML graphics window.
    sf::RenderWindow* DisplayManager::getWindow() const {
        return m_p_window;
    }

	/// Helper functions

	// Compute character height in pixels, based on window size.
	float DisplayManager::charHeight() const {
		//return m_window_vertical_pixels / m_window_vertical_chars;
		 float height = DM.getVerticalPixels() / DM.getVertical();
		 return height;
        //return static_cast<float> (m_window_vertical_pixels) / m_window_vertical_chars;
	}

	// Compute character width in pixels, based on window size.
	float DisplayManager::charWidth() const {
		//return m_window_horizontal_pixels / m_window_horizontal_chars;
		float width = DM.getHorizontalPixels() / DM.getHorizontal();
		return width;
        //return static_cast<float> (m_window_horizontal_pixels) / m_window_horizontal_chars;
	}

	// Convert ASCII space (x,y) to window pixels (x,y).
	Vector DisplayManager::spacesToPixels(Vector spaces) const {
        return Vector(spaces.getX() * charWidth(), spaces.getY() * charHeight());
	}

	// Convert window pixels (x,y) to ASCII space (x,y).
	Vector DisplayManager::pixelsToSpaces(Vector pixels) const {
        return Vector(pixels.getX() / charWidth(), pixels.getY() / charHeight());
	}

	// Draw string at window location (x,y) with default color.
	// Justified left, center, or right.
	// Return 0 if ok, else -1.
	int DisplayManager::drawString(Vector world_pos, std::string str, Justification just, Color color) const {

		Vector start_pos = world_pos; // Start position of string.

		switch (just)
		{
		case df::CENTER_JUSTIFIED:
			start_pos.setX(start_pos.getX() - str.size() / 2); 
			break;
		case df::RIGHT_JUSTIFIED:
			start_pos.setX(start_pos.getX() - str.size());
			break;
		case df::LEFT_JUSTIFIED:
		default:
			break;
		} // end switch

		for (size_t i = 0; i < str.size(); i++) {
			Vector temp_pos(start_pos.getX() + static_cast<float>(i), start_pos.getY()); // Position of character.
			drawCh(temp_pos, str[i], color); // Draw character.
		} // end for

		return 0; // Success.
	}

	// Optional: Background color
	bool df::DisplayManager::setBackgroundColor(Color new_color) {
		switch (new_color) {
		case BLACK:   m_window_background_color = sf::Color::Black; break;
		case RED:     m_window_background_color = sf::Color::Red; break;
		case GREEN:   m_window_background_color = sf::Color::Green; break;
		case YELLOW:  m_window_background_color = sf::Color::Yellow; break;
		case BLUE:    m_window_background_color = sf::Color::Blue; break;
		case MAGENTA: m_window_background_color = sf::Color::Magenta; break;
		case CYAN:    m_window_background_color = sf::Color::Cyan; break;
		case WHITE:   m_window_background_color = sf::Color::White; break;
		default:      return false;
		} // end switch
		return true;
	}

} // end of namespace df
