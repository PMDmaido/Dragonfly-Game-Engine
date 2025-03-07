#pragma once
//
// ResourceManager.h
//

#include <string>
#include "Manager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

#define RM df::ResourceManager::getInstance()

namespace df {

    const int MAX_SPRITES = 500;
    const int MAX_SOUNDS = 50;
    const int MAX_MUSICS = 50;


    class ResourceManager : public Manager {
    private:
        // Private constructor for Singleton pattern.
        ResourceManager();
        // Prevent copying.
        ResourceManager(ResourceManager const&);
        void operator=(ResourceManager const&);

        Sprite* m_p_sprite[MAX_SPRITES];     // Array of loaded sprites.
        int m_sprite_count;                 // Count of loaded sprites.
        Sound sound[MAX_SOUNDS];            // Array of sound buffers.
        int sound_count;                    // Count of number of loaded sounds.
        Music music[MAX_MUSICS];            // Array of music buffers.
        int music_count;                    // Count of number of loaded musics.

    public:
        // Get the single instance of ResourceManager.
        static ResourceManager& getInstance();

        // Initialize the ResourceManager for resource management.
        int startUp();

        // Shut down ResourceManager, freeing allocated sprites.
        void shutDown();

        // Load a sprite from a file and assign it the given label.
        // Return 0 if ok, else -1.
        int loadSprite(std::string filename, std::string label);

        // Unload the sprite with the given label.
        // Return 0 if ok, else -1.
        int unloadSprite(std::string label);

        // Find a sprite with the given label.
        // Returns a pointer to the sprite if found, else NULL.
        Sprite* getSprite(std::string label) const;

        // Load Sound from file.
        // Return 0 if ok, else -1.
        int loadSound(std::string filename, std::string label);

        // Remove Sound with indicated label.
        // Return 0 if ok, else -1.
        int unloadSound(std::string label);

        // Find Sound with indicated label.
        // Return pointer to it if found, else NULL.
        Sound* getSound(std::string label);

        // Associate file with Music.
        // Return 0 if ok, else -1.
        int loadMusic(std::string filename, std::string label);

        // Remove label for Music with indicated label.
        // Return 0 if ok, else -1.
        int unloadMusic(std::string label);

        // Find Music with indicated label.
        // Return pointer to it if found, else NULL.
        Music* getMusic(std::string label);
    };
}