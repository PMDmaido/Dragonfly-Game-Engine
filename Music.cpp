#include "Music.h"

namespace df {

    // Constructor
    Music::Music() {}

    // Load music from file.
    int Music::loadMusic(std::string filename) {
        if (!m_music.openFromFile(filename)) {
            return -1; // Error loading music
        }
        return 0; // Success
    }

    // Set label associated with music.
    void Music::setLabel(std::string new_label) {
        m_label = new_label;
    }

    // Get label associated with music.
    std::string Music::getLabel() const {
        return m_label;
    }

    // Play music with optional looping.
    void Music::play(bool loop) {
        m_music.setLooping(loop);
        m_music.play();
    }

    // Stop music.
    void Music::stop() {
        m_music.stop();
    }

    // Pause music.
    void Music::pause() {
        m_music.pause();
    }

    // Return pointer to SFML music.
    sf::Music* Music::getMusic() {
        return &m_music;
    }

}