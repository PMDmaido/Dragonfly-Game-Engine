// System includes
#include <Windows.h>
#include <mmsystem.h>

// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Clock.h"
#include "EventStep.h"
#include "ObjectList.h"
#include "Object.h"
#include "DisplayManager.h"
#include <iostream>
#include "InputManager.h"

namespace df {
	GameManager::GameManager() {
		setType("GameManager");
		game_over = false;
		frame_time = FRAME_TIME_DEFAULT; // Sets frame_time to 33 milliseconds for 30 fps.
	}

	GameManager& GameManager::getInstance() {
		static GameManager instance;
		return instance;
	}

	int GameManager::startUp() {
		if (Manager::startUp() != 0) {
			return -1;
		}
		std::cout << "GameManager:: Manager started up." << std::endl;

		// 1. Start up the LogManager.
		if (LM.startUp() != 0) {
			return -1;
		}
		std::cout << "GameManager:: LogManager started up." << std::endl;

		// 1. Start up the WorldManager.
		if (WM.startUp() != 0) {
			return -1;
		}
		std::cout << "GameManager:: WorldManager started up." << std::endl;

		// Start up DisplayManager.
		if (DM.startUp() != 0) {
			return -1;
		}
		std::cout << "GameManager:: DisplayManager started up." << std::endl;

		// Start up InputManager.
		if (InputManager::getInstance().startUp() != 0) { 
			return -1;
		}
		std::cout << "GameManager:: InputManager started up." << std::endl;

		WM.setBoundary(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
		WM.setView(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));

		// Set timer resolution to minimum (1 ms).
		timeBeginPeriod(1);

		game_over = false;
		LM.writeLog("GameManager, LogManager, WorldManager, DisplayManager, and InputManager started up\n");
		return 0;
	}

	void GameManager::shutDown() {
		LM.writeLog("GameManager shutting down...\n");
		// Indicate game is over.
		setGameOver(true);

		// Reset timer resolution to default.
		timeEndPeriod(1);

		InputManager::getInstance().shutDown(); // Shut down the InputManager.
		LM.writeLog("InputManager: shut down.\n");

		DM.shutDown(); // Shut down the DisplayManager.
		LM.writeLog("DisplayManager: shut down.\n"); 

		// 7. Shut down the WorldManager.
		WM.shutDown();
		LM.writeLog("WorldManager: shut down.\n");
		// Shut down the LogManager.
		LM.shutDown();



		//Manager::shutDown();
	}

	// 3. Run game loop.
	void GameManager::run() {
		// 3. GM executes the game loop with controlled timing (using the Clock class).
		Clock clock;
		long int loop_time;
		EventStep event_step; 

		while (!game_over) {
			clock.delta();

			// 3. WM sending each Object a step event.
			WM.onEvent(&event_step); // Send to all Objects.  //onEvent(&event_step)

				int step_count = event_step.getStepCount();
				LM.writeLog("Step count: %d\n", step_count);

			// Get Input
			InputManager::getInstance().getInput(); 
			
			// 4. Update game world state
			WM.update();

			// Draw current scene to back buffer
			WM.draw();

			// Swap back buffer to current buffer
			DM.swapBuffers();

			// Measure loop_time
			loop_time = clock.split(); // Get time elapsed in loop.

			// Sleep for (TARGET_TIME - loop_time)
				// If loop is too fast, sleep.
				// Sleep for the remaining time to achieve the TARGET_TIME frame.
			long int sleep_time = (frame_time * 1000) - loop_time; // convert frame_time to microseconds.
			if (sleep_time > 0) {
				Sleep(sleep_time / 1000); // convert sleep_time to milliseconds.
				// sleep ( TARGET_TIME - loop_time )
			}

			// Step count increment
			event_step.setStepCount(step_count + 1);

		} // end while
	}

	void GameManager::setGameOver(bool new_game_over) {
		game_over = new_game_over;
	}

	bool GameManager::getGameOver() const {
		return game_over;
	}

	int GameManager::getFrameTime() const {
		return frame_time;
	}

} // end of namespace df

/*
while ( game not over ) do
 Get input // e . g . , from keyb o a r d /mouse
 Update game world state
 Draw current scene to back buffer
 Swap back buffer to current buffer
end while

while ( game not over ) do
 Get input // e . g . , keyb o a r d /mouse
 Update game world state
 Draw current scene to back buffer
 Swap back buffer to current buffer
 Measure loop_time // i . e . , how above steps took
 Sleep for ( TARGET_TIME - loop_time )
end while

*/