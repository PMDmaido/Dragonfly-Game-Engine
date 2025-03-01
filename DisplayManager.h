///
/// The SFML display manager
///

#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

// System includes.
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// Engine includes.
#include "Manager.h"
#include "Color.h"
#include "Vector.h"
#include "utility.h"

// Two-letter acronym for easier access to manager.
//#define DM df::DisplayManager::getInstance() 

namespace df {

#define DM df::DisplayManager::getInstance() // Two-letter acronym 

	/// String justifications.
	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};


	/// Defaults for SFML window.
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black; // BLACK;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	class DisplayManager : public Manager {

	private:
		DisplayManager();                      ///< Private since a singleton.
		DisplayManager(DisplayManager const&); ///< Don't allow copy.
		void operator=(DisplayManager const&); ///< Don't allow assignment.
		sf::Font m_font;		  ///< Font used for ASCII graphics.
		sf::RenderWindow* m_p_window;	  ///< Pointer to SFML window.
		int m_window_horizontal_pixels; ///< Horizontal pixels in window. // Put unsigned
		int m_window_vertical_pixels;   ///< Vertical pixels in window.  // Put unsigned
		int m_window_horizontal_chars;  ///< Horizontal ASCII spaces in window.
		int m_window_vertical_chars;    ///< Vertical ASCII spaces in window.

		sf::Color m_window_background_color; ///< Default background color.	

	public:
		/// Get the one and only instance of the DisplayManager.
		static DisplayManager& getInstance();

		/// Open graphics window, ready for text-based display.
		/// Return 0 if ok, else -1.
		int startUp() override;

		/// Close graphics window.
		void shutDown() override;

		/// Draw character at window location (x,y) with color
		/// Return 0 if ok, else -1.
		int drawCh(Vector world_pos, char ch, Color color) const;

		/// Return window's horizontal maximum (in characters).
		int getHorizontal() const;

		/// Return window's vertical maximum (in characters).
		int getVertical() const;

		/// Return window's horizontal maximum (in pixels).
		int getHorizontalPixels() const;

		/// Return window's vertical maximum (in pixels).
		int getVerticalPixels() const;

		/// Render current window buffer.
		/// Return 0 if ok, else -1.
		int swapBuffers();

		/// Return pointer to SFML graphics window.
		sf::RenderWindow* getWindow() const;

		/// Helper functions

		// Compute character height in pixels, based on window size.
		float charHeight() const;

		// Compute character width in pixels, based on window size.
		float charWidth() const;

		// Convert ASCII space (x,y) to window pixels (x,y).
		Vector spacesToPixels(Vector spaces) const;

		// Convert window pixels (x,y) to ASCII space (x,y).
		Vector pixelsToSpaces(Vector pixels) const;

		/// Draw string at window location (x,y) with default color.
		/// Justified left, center, or right.
		/// Return 0 if ok, else -1.
		int drawString(Vector world_pos, std::string str, Justification just, Color color) const;

		// Set default background color of the window. Return true if ok, else false.
		bool setBackgroundColor(Color new_color);
	};

} // end of namespace df
#endif //__DISPLAY_MANAGER_H__