#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"

// Default frame time (game loop time) in milliseconds (33 ms = 30 fps).
const int FRAME_TIME_DEFAULT = 33;

namespace df {

#define GM df::GameManager::getInstance() // Two-letter acronym

	class GameManager : public df::Manager {
	private:
		GameManager(); // Private since a singleton.
		GameManager(GameManager const&); // Don't allow copy.
		void operator=(GameManager const&); // Don't allow assignment.

		bool game_over; // True then game loop stop.
		int frame_time; // Target time per game loop in ms.	

	public:
		// Get the one and only instance of the GameManager.
		static GameManager& getInstance();

		// Startup all GameManager services.
		int startUp();

		// Shutdown all GameManager services.
		void shutDown();

		// Run game loop.
		void run();

		// Indicate game is over.
		// When true, will stop game loop.
		void setGameOver(bool new_game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Get frame time in ms.
		int getFrameTime() const;
	};
} // end of namespace df

#endif // __GAME_MANAGER_H__