//
// GameManager.h
//

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"

#define GM df::GameManager::getInstance()

namespace df {

	const int FRAME_TIME_DEFAULT = 33;  // In milliseconds.

	class GameManager : public Manager {

	private:
		GameManager();                      // Private constructor (singleton).
		GameManager(GameManager const&);    // Prevent copy.
		void operator=(GameManager const&); // Prevent assignment.
		bool game_over;  // Controls game loop.
		int frame_time;  // Target frame time (in ms).

	public:
		// Get the singleton instance of GameManager.
		static GameManager& getInstance();

		// Startup GameManager services.
		int startUp() override;

		// Shutdown GameManager services.
		void shutDown() override;

		// Run the game loop.
		void run();

		// Set game over flag (true = stop game loop).
		void setGameOver(bool new_game_over = true);

		// Get game over flag.
		bool getGameOver() const;

		// Get frame time (in ms).
		int getFrameTime() const;

	};
}

#endif // __GAME_MANAGER_H__