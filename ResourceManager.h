///
/// The resource manager
///

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// System includes.
#include <string>

// Engine includes.
#include "Manager.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"

// Two-letter acronym for easier access to manager.
#define RM df::ResourceManager::getInstance()

namespace df {

	// Delimiters used to parse Sprite files -
	// the ResourceManager "knows" file format.
#define HEADER_TOKEN "HEADER"
#define BODY_TOKEN "BODY"
#define FOOTER_TOKEN "FOOTER"
#define FRAMES_TOKEN "frames"
#define TRANSPARENCY_TOKEN "transparency"
#define HEIGHT_TOKEN "height"
#define WIDTH_TOKEN "width"
#define COLOR_TOKEN "color"
#define SLOWDOWN_TOKEN "slowdown"
#define END_FRAME_TOKEN "end"
#define VERSION_TOKEN "version"

// Maximum number of unique assets in game.
	const int MAX_SPRITES = 1000;
	const int MAX_SOUNDS = 100;
	const int MAX_MUSICS = 50;

	class ResourceManager : public Manager {

	private:
		ResourceManager(ResourceManager const&); ///< Don't allow copy.
		void operator=(ResourceManager const&);  ///< Don't allow assignment.
		ResourceManager();	           ///< Private since a singleton.
		Sprite* m_p_sprite[MAX_SPRITES]; ///< Array of (pointers to) Sprites. 
		int m_sprite_count;	           ///< Count of number of loaded sprites.

#ifndef NO_SOUND
		Sound m_sound[MAX_SOUNDS];	   ///< Array of sound buffers.
		int m_sound_count;	           ///< Count of number of loaded sounds.
		Music m_music[MAX_MUSICS];	   ///< Array of music buffers. //used to have no *
		int m_music_count;	           ///< Count of number of loaded musics.
#endif

		// Load Sprite assuming robust sprite format in file.
		// Return Sprite if found, else NULL.
		//Sprite* loadRobustSprite(std::ifstream* p_file);

		// Load Sprite assuming simple sprite format in file.
		// Return Sprite if found, else NULL.
		//Sprite* loadSimpleSprite(std::ifstream* p_file);

	public:
		/// Get the one and only instance of the ResourceManager.
		static ResourceManager& getInstance();

		/// Get ResourceManager ready to manage resources.
		int startUp() override;

		/// Shut down manager, freeing up any allocated Sprites, Music and Sounds.
		void shutDown() override;

		/// Load Sprite from file.
		/// Assign indicated label to Sprite.
		/// Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		/// Unload Sprite with indicated label.
		/// Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		/// Find Sprite with indicated label.
		/// Return pointer to it if found, else NULL.
		Sprite* getSprite(std::string label) const;

		/// Load sound from file.
		/// Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		/// Remove Sound with indicated label.
		/// Return 0 if ok, else -1.
		int unloadSound(std::string label);

		/// Find Sound with indicated label.
		/// Return pointer to it if found, else NULL.
		Sound* getSound(std::string label);

		/// Associate file with Music.
		/// Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		/// Remove label for Music with indicated label.
		/// Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		/// Find Music with indicated label.
		/// Return pointer to it if found, else NULL.
		Music* getMusic(std::string label);
	};

} // end of namespace df
#endif //__RESOURCE_MANAGER_H__
