//
// DisplayManager.cpp
//


//Engine Includes.
#include "DisplayManager.h"
#include "LogManager.h"
#include "utility.h"

namespace df {

    DisplayManager& DisplayManager::getInstance() {
        static DisplayManager instance;
        return instance;
    }

    DisplayManager::DisplayManager() {
        setType("DisplayManager");
        m_p_window = nullptr;
        m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
        m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
        m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
        m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
    }

    int DisplayManager::startUp() {

        if (m_p_window != nullptr) {
            LM.writeLog("DisplayManager::startUp(): DisplayManager is already start up.");
            return 0;
        }

        
        // Create SFML window
        m_p_window = new sf::RenderWindow(
            sf::VideoMode({ (unsigned int)m_window_horizontal_pixels, (unsigned int)m_window_vertical_pixels }),
            WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

        if (!m_p_window) {
            LM.writeLog("DisplayManager::startUp(): Failed to create window.");
            return -1;
        }

        // Turn off mouse cursor
        m_p_window->setMouseCursorVisible(false);

        // Disable keyboard repeat
        m_p_window->setKeyRepeatEnabled(false);

        // Synchronize refresh rate with monitor (V-Sync)
        m_p_window->setVerticalSyncEnabled(true);

        // Load font
        if (!m_font.openFromFile(FONT_FILE_DEFAULT)) {
            LM.writeLog("DisplayManager::startUp(): Failed to load font.");
            return -1;
        }
        

        // Call Manager's startUp function
        Manager::startUp();

        return 0;
    }

    void DisplayManager::shutDown() {
        if (m_p_window) {
            m_p_window->close();
            delete m_p_window;
            m_p_window = nullptr;
        }
    }

    int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {


        if (m_p_window == nullptr)
            return -1;

        // Convert world coordinates to pixel coordinates
        Vector view_pos = DM.spacesToPixels(worldToView(world_pos));

        // Draw background rectangle for character visibility
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(DM.charWidth(), DM.charHeight()));
        rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
        rectangle.setPosition({ view_pos.getX() - DM.charWidth() / 10, view_pos.getY() + DM.charHeight() / 5 });
        m_p_window->draw(rectangle);

        // Create character text to draw
        sf::Text text(m_font);
        text.setString(std::string(1, ch)); // Convert char to string
        text.setStyle(sf::Text::Bold); // Make text bold for better visibility

        // Scale text size properly
        if (DM.charWidth() < DM.charHeight()) {
            text.setCharacterSize(DM.charWidth() * 2);
        }
        else {
            text.setCharacterSize(DM.charHeight() * 2);
        }

        // Set SFML color based on Dragonfly color
        switch (color) {
        case YELLOW:
            text.setFillColor(sf::Color::Yellow);
            break;
        case RED:
            text.setFillColor(sf::Color::Red);
            break;
        case GREEN:
            text.setFillColor(sf::Color::Green);
            break;
        case BLUE:
            text.setFillColor(sf::Color::Blue);
            break;
        case BLACK:
            text.setFillColor(sf::Color::Black);
            break;
        case MAGENTA:
            text.setFillColor(sf::Color::Magenta);
            break;
        case CYAN:
            text.setFillColor(sf::Color::Cyan);
            break;
        case WHITE:
            text.setFillColor(sf::Color::White);
            break;
        default:
            text.setFillColor(sf::Color::White); // Default to white
            break;
        }


        // Set position in window (in view)
        text.setPosition({ view_pos.getX(), view_pos.getY() });


        // Draw character
        m_p_window->draw(text);

        return 0;

    }

    int DisplayManager::getHorizontal() const {
        return m_window_horizontal_chars;
    }

    int DisplayManager::getVertical() const {
        return m_window_vertical_chars;
    }

    int DisplayManager::getHorizontalPixels() const {
        return m_window_horizontal_pixels;
    }

    int DisplayManager::getVerticalPixels() const {
        return m_window_vertical_pixels;
    }

    int DisplayManager::swapBuffers() {
        if (m_p_window == nullptr) 
            return -1;

        m_p_window->display();
        m_p_window->clear();
        return 0;
    }

    sf::RenderWindow* DisplayManager::getWindow() const {
        return m_p_window;
    }

    float DisplayManager::charHeight() {
        return (float) ((float) getVerticalPixels() / (float) getVertical());
    }

    float DisplayManager::charWidth() {
        return (float) ((float)getHorizontalPixels() / (float)getHorizontal());
    }

    Vector DisplayManager::spacesToPixels(Vector spaces)
    {
        return Vector(spaces.getX() * charWidth(), spaces.getY() * charHeight());
    }

    Vector DisplayManager::pixelsToSpaces(Vector pixels)
    {
        return Vector(pixels.getX() / charWidth(), pixels.getY() / charHeight());
    }

    int DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
        
        Vector starting_pos = pos;

        switch (just) {
        case CENTER_JUSTIFIED:
            starting_pos.setX(pos.getX() - str.size() / 2);
            break;
        case RIGHT_JUSTIFIED:
            starting_pos.setX(pos.getX() - str.size());
            break;
        case LEFT_JUSTIFIED:
        default:
            break;
        }

        // Draw string character by character
        for (size_t i = 0; i < str.size(); i++) {
            Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
            if (drawCh(temp_pos, str[i], color) != 0) {
                return -1; // Return -1 if drawing fails
            }
        }

        return 0;
    }

    bool DisplayManager::setBackgroundColor(Color new_color) {

        switch (new_color) {
        case BLACK:   
            m_window_background_color = sf::Color::Black; 
            break;
        case RED:     
            m_window_background_color = sf::Color::Red;
            break;
        case GREEN:  
            m_window_background_color = sf::Color::Green;
            break;
        case YELLOW:  
            m_window_background_color = sf::Color::Yellow;
            break;
        case BLUE:    
            m_window_background_color = sf::Color::Blue; 
            break;
        case MAGENTA: 
            m_window_background_color = sf::Color::Magenta;
            break;
        case CYAN:    
            m_window_background_color = sf::Color::Cyan;
            break;
        case WHITE:  
            m_window_background_color = sf::Color::White;
            break;
        default:     
            return false;
        }
        return true;
    }



    

}