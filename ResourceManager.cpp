//
// ResourceManager.cpp
//

// System includes.
#include <iostream>
#include <fstream>
#include <string>

// Engine includes.
#include "ResourceManager.h"
#include "LogManager.h"

namespace df {
	// Private constructor.
	ResourceManager::ResourceManager() {
		m_sprite_count = 0;
		for (int i = 0; i < MAX_SPRITES; i++) {
			m_p_sprite[i] = nullptr;
		}
		m_sound_count = 0;
		m_music_count = 0;
	}

	// Get the one and only instance of the ResourceManager.
	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager resource_manager;
		return resource_manager;
	}

	// Start up the ResourceManager.
	int ResourceManager::startUp() {
		m_sprite_count = 0;
		for (int i = 0; i < MAX_SPRITES; i++) {
			m_p_sprite[i] = nullptr;
		}
		LM.writeLog("ResourceManager::startUp(): Successfully started.");
		return Manager::startUp();
	}

	// Shut down the ResourceManager.
	// Freeing up any allocated Sprites, Music and Sounds.
	void ResourceManager::shutDown() {
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i] != NULL) {
				delete m_p_sprite[i];
			}
		}
		m_sprite_count = 0;
		Manager::shutDown();
	}

/*
	// Remove the carriage return (\r) from line (if present).
	void discardCR(std::string& str) {
		if (!str.empty() && str.back() == '\r') {
			str.erase(str.size() - 1);
		}
	}
*/

	// Load Sprite from file.
	// Assign indicated label to Sprite.
	// Return 0 if ok, else -1.
	int ResourceManager::loadSprite(std::string filename, std::string label) {
		
		// Check if Sprite array is full.
		if (m_sprite_count >= MAX_SPRITES)
			return -1;

		// Open file.
		std::ifstream myfile(filename);
		if (!myfile.is_open()) {
			std::cout << "unable to open file" << std::endl;
			return -1;
		}
		
		std::string line;
		int frames, width, height, slowdown;
		Color color;

/*		getline(myfile, line);
		frames = std::atoi(line.c_str());

		getline(myfile, line);
		width = std::atoi(line.c_str());

		getline(myfile, line);
		height = std::atoi(line.c_str());

		getline(myfile, line);
		slowdown = std::atoi(line.c_str());
*/
		// Read sprite header.
		if (!getline(myfile, line) || (frames = std::atoi(line.c_str())) <= 0) {
			std::cerr << "Error: Invalid frame count in " << filename << std::endl;
			return -1;
		}
		if (!getline(myfile, line) || (width = std::atoi(line.c_str())) <= 0) {
			std::cerr << "Error: Invalid width in " << filename << std::endl;
			return -1;
		}
		if (!getline(myfile, line) || (height = std::atoi(line.c_str())) <= 0) {
			std::cerr << "Error: Invalid height in " << filename << std::endl;
			return -1;
		}
		if (!getline(myfile, line) || (slowdown = std::atoi(line.c_str())) < 0) {
			std::cerr << "Error: Invalid slowdown in " << filename << std::endl;
			return -1;
		}
/*
		if (!getline(myfile, line)) {
			std::cerr << "Error: Missing color information in " << filename << std::endl;
			return -1;
		}
*/

		//discardCR(line);
		color = COLOR_DEFAULT;

		if (getline(myfile, line)) {
			if (line == "black")   color = BLACK;
			else if (line == "red")     color = RED;
			else if (line == "green")   color = GREEN;
			else if (line == "yellow")  color = YELLOW;
			else if (line == "blue")    color = BLUE;
			else if (line == "magenta") color = MAGENTA;
			else if (line == "cyan")    color = CYAN;
			else if (line == "white")   color = WHITE;
			else if (line == "custom")  color = CUSTOM;
			else {
				//std::cout << "invalid color" << std::endl;
				//std::cerr << "Error: Unknown color in " << filename << std::endl;
				//return -1;
				LM.writeLog("ResourceManager::loadSprite - Unrecognized color: %s. Using COLOR_DEFAULT: WHITE.\n", line.c_str());
			}
		}
		else {
			//std::cerr << "Error: Missing color information in " << filename << std::endl;
			//return -1;
			LM.writeLog("ResourceManager::loadSprite - No color specified. Using default COLOR_DEFAULT: WHITE.\n");
		}
		// Log read values
		LM.writeLog("ResourceManager::loadSprite - Frames: %d, Width: %d, Height: %d, Slowdown: %d, Color: %s \n",
			frames, width, height, slowdown, line.c_str()); 

		// Create new Sprite.
		Sprite* p_sprite = new Sprite(frames);
		p_sprite->setWidth(width);
		p_sprite->setHeight(height);
		p_sprite->setSlowdown(slowdown);
		p_sprite->setColor(color);

		// Read and add frames to Sprite.
		for (int f = 0; f < frames; f++) { 
			std::string frame_str; 
			for (int h = 0; h < height; h++) {

				// getline(myfile, line);
				if (!getline(myfile, line)) {
/*|| line.length() != (size_t)width)
					std::cerr << "Error: Line " << (f * height + h + 6) << " in " << filename
						<< " has incorrect width (expected " << width << ", got "
						<< line.length() << ")\nLine is: \"" << line << "\"" << std::endl;
*/
					delete p_sprite;
					return -1;
				} 
				//discardCR(line);  // Remove any carriage return.

				frame_str += line; // Add line to frame string.
			}
			Frame frame(width, height, frame_str);
			//p_sprite->addFrame(frame); // Add frame to Sprite.
			if (p_sprite->addFrame(frame) == -1) {
				LM.writeLog("ResourceManager::loadSprite - Error: Failed to add frame %d \n", f);
				delete p_sprite;
				return -1;
			}
		}

		// Close file.
		myfile.close();

		// if no errors, add Sprite to ResourceManager.
		p_sprite->setLabel(label);
		m_p_sprite[m_sprite_count] = p_sprite; 
		m_sprite_count++; 

		LM.writeLog("ResourceManager::loadSprite - Successfully loaded sprite: %s with label: %s. \n", filename.c_str(), label.c_str());

		return 0;
	}


	/// Unload Sprite with indicated label.
	/// Return 0 if ok, else -1.
	int ResourceManager::unloadSprite(std::string label) {
		for (int i = 0; i < m_sprite_count; i++) {

			if (m_p_sprite[i]->getLabel() == label) {
				// Log before deletion
				LM.writeLog("ResourceManager::unloadSprite - Found sprite '%s' at index %d, deleting...\n", label.c_str(), i);

				delete m_p_sprite[i];

				// Scoot over remaining Sprites.
				for (int j = i; j < (m_sprite_count - 1); j++) {
					m_p_sprite[j] = m_p_sprite[j + 1];
				}  

				// Nullify last pointer after shifting
				m_p_sprite[m_sprite_count - 1] = nullptr;

				m_sprite_count--;
				LM.writeLog("ResourceManager::unloadSprite - Successfully unloaded sprite: %s.\n", label.c_str());

				return 0;
			}
		}
		LM.writeLog("ResourceManager::unloadSprite - Error: Sprite '%s' not found.\n", label.c_str());
		return -1; // Sprite not found.
	}

	/// Find Sprite with indicated label.
	/// Return pointer to it if found, else NULL.
	Sprite* ResourceManager::getSprite(std::string label) const {
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				return m_p_sprite[i];
			}
		}
		return NULL; // Sprite not found.
	}

	// Load Sound from file.
	int ResourceManager::loadSound(std::string filename, std::string label) {
		if (m_sound_count >= MAX_SOUNDS) {
			LM.writeLog("ResourceManager::loadSound: Sound array full.");
			return -1; // Error: Exceeded max sound limit
		}

		if (m_sound[m_sound_count].loadSound(filename) == -1) {
			LM.writeLog("ResourceManager::loadSound: Unable to load sound %s.", filename); 
			return -1; // Error: Failed to load sound
		}

		// All is well.
		m_sound[m_sound_count].setLabel(label);
		m_sound_count++;
		return 0; // Success
	}

	// Remove Sound with indicated label.
	int ResourceManager::unloadSound(std::string label) {
		for (int i = 0; i < m_sound_count; i++) {
			if (m_sound[i].getLabel() == label) {
				// Shift remaining sounds down
				for (int j = i; j < m_sound_count - 1; j++) {
					m_sound[j] = m_sound[j + 1];
				}
				m_sound_count--;
				return 0; // Success
			}
		}
		return -1; // Error: Sound not found
	}

	// Find Sound with indicated label.
	Sound* ResourceManager::getSound(std::string label) {
		for (int i = 0; i < m_sound_count; i++) {
			if (m_sound[i].getLabel() == label) {
				return &m_sound[i];
			}
		}
		LM.writeLog("ResourceManager::getSound:Error: Sound '%s' not found", label.c_str());
		return nullptr; // Not found
	}

	// Load Music from file.
	int ResourceManager::loadMusic(std::string filename, std::string label) {
		if (m_music_count >= MAX_MUSICS) {
			LM.writeLog("ResourceManager::loadMusic: Music array full.");
			return -1; // Error: Exceeded max music limit
		}

		if (m_music[m_music_count].loadMusic(filename) != 0) {
			LM.writeLog("ResourceManager::loadMusic: Unable to load music %s.", filename); 
			return -1; // Error: Failed to load music 
		}

		m_music[m_music_count].setLabel(label);
		m_music_count++;
		return 0; // Success
	}

	// Remove Music with indicated label.
	int ResourceManager::unloadMusic(std::string label) {
		for (int i = 0; i < m_music_count; i++) {
			if (m_music[i].getLabel() == label) {
				// Music is not	copyable, the elements cannot be “scooted over” in the array
				// Instead of shifting elements, just mark it as unloaded by setting an empty label.
				m_music[i].setLabel("");

				LM.writeLog("ResourceManager::unloadMusic - Successfully unloaded music: %s", label.c_str());
				return 0; // Success
			}
		}

		LM.writeLog("ResourceManager::unloadMusic - Error: Music '%s' not found.", label.c_str());
		return -1; // Error: Music not found
	}

	Music* ResourceManager::getMusic(std::string label) {
		// Iterate through all loaded music
		for (int i = 0; i < m_music_count; i++) {
			if (m_music[i].getLabel() == label) {
				return &m_music[i]; // Return pointer to the music
			}
		}

		// Log error if music is not found
		LM.writeLog("ResourceManager::getMusic - Error: Music '%s' not found", label.c_str());
		return nullptr; // Music not found
	}


}