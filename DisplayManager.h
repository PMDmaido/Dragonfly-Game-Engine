#pragma once
//
// DisplayManager.h
//

// System includes.
#include <SFML/Graphics.hpp>

// Engine includes
#include "Color.h"
#include "Manager.h"
#include "Vector.h"

#define DM df::DisplayManager::getInstance()

namespace df {

    enum Justification {
    LEFT_JUSTIFIED,
    CENTER_JUSTIFIED,
    RIGHT_JUSTIFIED
    };


    // Default values for SFML window
    const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1920;//1024
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 1080;//768
    const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 160;//80
    const int WINDOW_VERTICAL_CHARS_DEFAULT = 48;//24
    const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
    const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
    const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
    const std::string FONT_FILE_DEFAULT = "df-font.ttf";

    class DisplayManager : public Manager {
    private:
        DisplayManager();
        DisplayManager(const DisplayManager&);
        void operator=(const DisplayManager&);
        sf::Font m_font;                        // Font used for ASCII graphics
        sf::RenderWindow* m_p_window;           // Pointer to SFML window
        int m_window_horizontal_pixels;         // Horizontal pixels in window
        int m_window_vertical_pixels;           // Vertical pixels in window
        int m_window_horizontal_chars;          // Horizontal ASCII spaces in window
        int m_window_vertical_chars;            // Vertical ASCII spaces in window
        sf::Color m_window_background_color;    // Background window color

    public:
        // Get the singleton instance
        static DisplayManager& getInstance();

        // Open graphics window, ready for text-based display. Return 0 if OK, else -1.
        int startUp();

        // Close graphics window.
        void shutDown();

        // Draw a character at window location (x, y) with color. Return 0 if OK, else -1.
        int drawCh(Vector world_pos, char ch, Color color) const;

        // Return window’s horizontal max (characters).
        int getHorizontal() const;

        // Return window’s vertical max (characters).
        int getVertical() const;

        // Return window’s horizontal max (pixels).
        int getHorizontalPixels() const;

        // Return window’s vertical max (pixels).
        int getVerticalPixels() const;

        // Render the current window buffer. Return 0 if OK, else -1.
        int swapBuffers();

        // Return pointer to SFML graphics window.
        sf::RenderWindow* getWindow() const;

        // Compute character height in pixels, based on window size.
        float charHeight();

        // Compute character width in pixels, based on window size.
        float charWidth();
        
        // Convert ASCII spaces (x,y) to window pixels (x,y).
        Vector spacesToPixels(Vector spaces);
        
        // Convert window pixels (x,y) to ASCII spaces (x,y).
        Vector pixelsToSpaces(Vector pixels);

        // Draw string at window location (x,y) with default color.
        // Justified left, center or right.
        // Return 0 if ok, else -1.
        int drawString(Vector pos, std::string str, Justification just, Color color) const;

        // Set default background color. Return true if ok, else false.
        bool setBackgroundColor(Color new_color);
    };

}
