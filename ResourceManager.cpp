//
// ResourceManager.cpp
//
#include "ResourceManager.h"
#include <fstream>
#include <cstdlib>
#include "LogManager.h"

namespace df {
    ResourceManager& ResourceManager::getInstance() {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager::ResourceManager() : m_sprite_count(0) {
        for (int i = 0; i < MAX_SPRITES; i++) {
            m_p_sprite[i] = nullptr;
        }
    }

    int ResourceManager::startUp() {
        m_sprite_count = 0;
        for (int i = 0; i < MAX_SPRITES; i++) {
            m_p_sprite[i] = nullptr;
        }
        return 0;
    }

    void ResourceManager::shutDown() {
        for (int i = 0; i < m_sprite_count; i++) {
            if (!m_p_sprite[i]) {
                delete m_p_sprite[i];
            }
        }
        m_sprite_count = 0;
        Manager::shutDown();
    }

    int ResourceManager::loadSprite(std::string filename, std::string label) {
        // Log function start
        //LM.writeLog("ResourceManager::loadSprite - Attempting to load sprite: %s", filename.c_str());

        // Check if room in array
        if (m_sprite_count >= MAX_SPRITES) {
            LM.writeLog("ResourceManager::loadSprite - Error: Sprite array is full.");
            return -1; // Error: No space left for new sprites.
        }

        std::ifstream file(filename);
        if (!file) {
            LM.writeLog("ResourceManager::loadSprite - Error: Failed to open file: %s", filename.c_str());
            return -1;
        }

        // Read sprite header
        std::string line;

        // Read number of frames
        if (!std::getline(file, line)) {
            LM.writeLog("ResourceManager::loadSprite - Error: Missing frame count.");
            return -1;
        }
        int frames = std::atoi(line.c_str());

        // Read width
        if (!std::getline(file, line)) {
            LM.writeLog("ResourceManager::loadSprite - Error: Missing width.");
            return -1;
        }
        int width = std::atoi(line.c_str());

        // Read height
        if (!std::getline(file, line)) {
            LM.writeLog("ResourceManager::loadSprite - Error: Missing height.");
            return -1;
        }
        int height = std::atoi(line.c_str());

        // Read slowdown factor
        if (!std::getline(file, line)) {
            LM.writeLog("ResourceManager::loadSprite - Error: Missing slowdown factor.");
            return -1;
        }
        int slowdown = std::atoi(line.c_str());

        // Read color (optional)
        Color color = BLACK;  // Default color
        if (std::getline(file, line)) {
            if (line == "black") color = BLACK;
            else if (line == "red") color = RED;
            else if (line == "green") color = GREEN;
            else if (line == "blue") color = BLUE;
            else if (line == "yellow") color = YELLOW;
            else if (line == "cyan") color = CYAN;
            else if (line == "magenta") color = MAGENTA;
            else if (line == "white") color = WHITE;
            else if (line == "cutom") color = CUSTOM;
            else {
                LM.writeLog("ResourceManager::loadSprite - Unrecognized color: %s. Using default BLACK.", line.c_str());
            }
        }
        else {
            LM.writeLog("ResourceManager::loadSprite - No color specified. Using default BLACK.");
        }

        // Log read values
        //LM.writeLog("ResourceManager::loadSprite - Frames: %d, Width: %d, Height: %d, Slowdown: %d, Color: %s",
            //frames, width, height, slowdown, line.c_str());

        // Create new sprite
        Sprite* p_sprite = new Sprite(frames);
        p_sprite->setWidth(width);
        p_sprite->setHeight(height);
        p_sprite->setSlowdown(slowdown);
        p_sprite->setColor(color);


        // Read and add frames to sprite
        for (int f = 1; f <= frames; f++) {
            std::string frame_str;
            for (int h = 1; h <= height; h++) {
                if (!std::getline(file, line)) {
                    LM.writeLog("ResourceManager::loadSprite - Error: Missing frame data for frame %d.", f);
                    delete p_sprite;
                    return -1;
                }
                frame_str += line;
            }

            Frame frame(width, height, frame_str);
            p_sprite->addFrame(frame);
            

        }

        file.close();

        // Assign label and add to ResourceManager
        p_sprite->setLabel(label);
        m_p_sprite[m_sprite_count] = p_sprite;
        m_sprite_count++;

        LM.writeLog("ResourceManager::loadSprite - Successfully loaded sprite: %s with label: %s", filename.c_str(), label.c_str());
        return 0;  // Success
    }

    int ResourceManager::unloadSprite(std::string label) {
        //LM.writeLog("ResourceManager::unloadSprite - Attempting to unload sprite: %s", label.c_str());

        // Loop through all loaded sprites
        for (int i = 0; i < m_sprite_count; i++) {
            if (m_p_sprite[i] && m_p_sprite[i]->getLabel() == label) {
                // Log before deletion
                LM.writeLog("ResourceManager::unloadSprite - Found sprite '%s' at index %d, deleting...", label.c_str(), i);

                // Delete the sprite
                delete m_p_sprite[i];

                // Shift remaining sprites down to fill the gap
                for (int j = i; j < m_sprite_count - 1; j++) {
                    m_p_sprite[j] = m_p_sprite[j + 1];
                }

                // Decrement sprite count
                m_sprite_count--;

                LM.writeLog("ResourceManager::unloadSprite - Successfully unloaded sprite: %s", label.c_str());
                return 0;  // Success
            }
        }

        // Log if sprite not found
        LM.writeLog("ResourceManager::unloadSprite - Error: Sprite '%s' not found.", label.c_str());
        return -1;  // Sprite not found
    }

    Sprite* ResourceManager::getSprite(std::string label) const {
        for (int i = 0; i < m_sprite_count; i++) {
            if (m_p_sprite[i] && m_p_sprite[i]->getLabel() == label) {
                return m_p_sprite[i];
            }
        }
        return nullptr; // Sprite not found.
    }

    int ResourceManager::loadSound(std::string filename, std::string label) {

        // Check if sound array is full
        if (sound_count >= MAX_SOUNDS) {
            LM.writeLog("ResourceManager::loadSound - Error: Sound array full.");
            return -1; // Error: Cannot load more sounds
        }

        // Attempt to load sound file
        if (sound[sound_count].loadSound(filename) == -1) {
            LM.writeLog("ResourceManager::loadSound - Error: Unable to load sound from file '%s'", filename.c_str());
            return -1; // Error: Failed to load sound
        }
        //LM.writeLog("Code reach this line");

        // Assign label and increment count
        sound[sound_count].setLabel(label);
        sound_count++;

        LM.writeLog("ResourceManager::loadSound - Successfully loaded sound: %s with label: %s", filename.c_str(), label.c_str());

        return 0; // Success
    }

    int ResourceManager::unloadSound(std::string label) {
        // Iterate through all loaded sounds
        for (int i = 0; i < sound_count; i++) {
            if (sound[i].getLabel() == label) {
                // Shift remaining sounds down to fill the gap
                for (int j = i; j < sound_count - 1; j++) {
                    sound[j] = sound[j + 1];
                }

                // Decrement the sound count
                sound_count--;

                LM.writeLog("ResourceManager::unloadSound - Successfully removed sound '%s'", label.c_str());
                return 0; // Success
            }
        }

        LM.writeLog("ResourceManager::unloadSound - Error: Sound '%s' not found", label.c_str());
        return -1; // Error: Sound not found
    }

    Sound* ResourceManager::getSound(std::string label) {
        // Iterate through all loaded sounds
        for (int i = 0; i < sound_count; i++) {
            if (sound[i].getLabel() == label) {
                return &sound[i]; // Return pointer to the sound
            }
        }

        // Log error if sound is not found
        LM.writeLog("ResourceManager::getSound - Error: Sound '%s' not found", label.c_str());
        return nullptr; // Sound not found
    }

    int ResourceManager::loadMusic(std::string filename, std::string label) {
        // Check if music array is full
        if (music_count >= MAX_MUSICS) {
            LM.writeLog("ResourceManager::loadMusic - Error: Music array full.");
            return -1; // Error: Cannot load more music
        }

        // Attempt to load music file
        if (music[music_count].loadMusic(filename) != 0) {
            LM.writeLog("ResourceManager::loadMusic - Error: Unable to load music from file '%s'", filename.c_str());
            return -1; // Error: Failed to load music
        }

        music[music_count].setLabel(label);
        music_count++; // Increment music count

        LM.writeLog("ResourceManager::loadMusic - Successfully loaded music: %s with label: %s", filename.c_str(), label.c_str());

        return 0; // Success
    }

    int ResourceManager::unloadMusic(std::string label) {
        // Iterate through all loaded musics
        for (int i = 0; i < music_count; i++) {
            if (music[i].getLabel() == label) {
                // Shift remaining musics down to fill the gap
                for (int j = i; j < music_count - 1; j++) {
                    music[j] = music[j + 1];
                }

                music_count--; // Decrement the music count
                LM.writeLog("ResourceManager::unloadMusic - Successfully removed music '%s'", label.c_str());
                return 0; // Success
            }
        }

        LM.writeLog("ResourceManager::unloadMusic - Error: Music '%s' not found", label.c_str());
        return -1; // Error: Music not found
    }

    Music* ResourceManager::getMusic(std::string label) {
        // Iterate through all loaded musics
        for (int i = 0; i < music_count; i++) {
            if (music[i].getLabel() == label) {
                return &music[i]; // Return pointer to the music
            }
        }

        LM.writeLog("ResourceManager::getMusic - Error: Music '%s' not found", label.c_str());
        return nullptr; // Music not found
    }
}