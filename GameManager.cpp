//
// GameManager.cpp
//

#include "GameManager.h"
#include "LogManager.h"
#include "Clock.h"
#include "thread"
#include "WorldManager.h"
#include "EventStep.h"
#include "time.h"
#include "windows.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

namespace df {

	GameManager::GameManager() {
		setType("GameManager");
		game_over = false;
		frame_time = FRAME_TIME_DEFAULT;
		
		
	}

	GameManager& GameManager::getInstance() {
		static GameManager instance;
		return instance;
	}

	int GameManager::startUp() {
		Manager::startUp(); 
		LM.startUp();
		DM.startUp();
		WM.setBoundary(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
		WM.setView(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
		IM.startUp();
		RM.startUp();
		game_over = false;
		return 0;
	}

	void GameManager::shutDown() {
		setGameOver(true);
		LM.shutDown();
		Manager::shutDown();
	}

	void GameManager::run() {
		
		LM.writeLog("GameManager is running");

		EventStep event_step;

		Clock clock;


		while (!game_over) {

			clock.delta(); 
			ObjectList wo = WM.getAllObjects();

			int step_count = event_step.getStepCount();

			EventStep s;
			onEvent(&s);

			IM.getInput();

			WM.update();

			WM.draw();

			DM.swapBuffers();

			/*for (int i = 0; i < wo.getCount(); i++) {
				wo[i]->eventHandler(&event_step);
			}*/

			event_step.setStepCount(step_count + 1);

			long int elapsed_time = clock.split(); 

			// Sleep to maintain 30 Hz (always sleep for at least 33ms)
			if (elapsed_time < frame_time) {
				int sleep_time = frame_time - elapsed_time;

				timeBeginPeriod(1);
				std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
				timeEndPeriod(1);
			}
			else {
				LM.writeLog("WARNING: Frame took too long! %ld ms", elapsed_time);
			}

			 
		}

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

	
}