#pragma once
//
// Music.h
//

#include <string>
#include <SFML/Audio.hpp>

namespace df {
    class Music {
    private:
        
        sf::Music m_music;   // The SFML music.
        std::string m_label; // Text label to identify the music.

    public:
        // Constructor
        Music();

        // Prevent copying and assignment (SFML doesn't allow it).
        void operator=(Music const&);
        Music(Music const&);

        // Load music from file.
        // Return 0 if successful, else -1.
        int loadMusic(std::string filename);

        // Set label associated with music.
        void setLabel(std::string new_label);

        // Get label associated with music.
        std::string getLabel() const;

        // Play music.
        // If loop is true, repeat play when done.
        void play(bool loop = true);

        // Stop music.
        void stop();

        // Pause music.
        void pause();

        // Return pointer to SFML music.
        sf::Music* getMusic();
    };
}