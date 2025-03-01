// InputManager.cpp

#include <SFML/Window.hpp>

// Engine includes.
#include "InputManager.h"
#include "LogManager.h"

namespace df {
	InputManager::InputManager() {
		setType("InputManager");
	}

	InputManager& InputManager::getInstance() {
		static InputManager input_manager;
		return input_manager;
	}

	// Get window ready to capture input.
	// Return 0 if ok, else -1.
	int InputManager::startUp() {
		// Start up DisplayManager.
		if (!DM.isStarted()) { //DM.startUp() == -1
			LM.writeLog("InputManager::startUp(): DisplayManager startUp failed\n");
			return -1;
		}

		// Get the SFML window from DisplayManager.
		sf::RenderWindow* p_window = DM.getWindow();
		if (!p_window) {
			LM.writeLog("InputManager::startUp(): No DisplayManager found\n");
			return -1;
		}

		p_window->setKeyRepeatEnabled(false); // Disable key repeat in window. // decltype(p_window->setKeyRepeatEnabled(false));

		// Call parent to indicate successful startup.
		Manager::startUp();

		LM.writeLog("InputManager::startUp(): InputManager started\n");
		return 0;
	}

	// Revert back to normal window mode.
	void InputManager::shutDown() {
		// Re-enable key repeat.
		sf::RenderWindow* p_window = DM.getWindow();
		if (p_window) {
			p_window->setKeyRepeatEnabled(true);
		}

		LM.writeLog("InputManager::shutDown(): Shutting down InputManager\n");
		// Call parent to indicate successful shutdown.
		Manager::shutDown();
	}

	// Get input from the keyboard and mouse.
	// Pass event along to all interested Objects.
	void InputManager::getInput() const {
		sf::RenderWindow* window = DM.getWindow();
		if (!window || !window->isOpen()) {
			LM.writeLog("InputManager::getInput(): No valid window found.\n");
			return; // Exit the function if the window is invalid
		}

		while (const std::optional<sf::Event> p_event = DM.getWindow()->pollEvent()) {
			//const sf::Event& sf_event = p_event.value();
			const sf::Event* sf_event = &p_event.value();

			// if key pressed then...
			// const auto* sf_kb_event = sf_event.getIf<sf::Event::KeyPressed>();
			
			if (const sf::Event::KeyPressed* sf_kb_event = sf_event->getIf<sf::Event::KeyPressed>()) {
				// create EventKeyboard ( key and action )
				EventKeyboard kb_e;
				kb_e.setKeyboardAction(KEY_PRESSED);
				kb_e.setKey(EventKeyboard::convertFromSFML(sf_kb_event->code));
				LM.writeLog("InputManager::getInput(): Key Pressed - %d\n", sf_kb_event->code);

				// send EventKeyboard to all Objects
				WM.onEvent(&kb_e);
			}

			// if key released then ...
			else if (const sf::Event::KeyReleased* sf_kb_event = sf_event->getIf<sf::Event::KeyReleased>()) {
				// create EventKeyboard ( key and action )
				EventKeyboard kb_e;
				kb_e.setKeyboardAction(KEY_RELEASED);
				kb_e.setKey(EventKeyboard::convertFromSFML(sf_kb_event->code));
				LM.writeLog("InputManager::getInput(): Key Released - %d\n", sf_kb_event->code);

				// send EventKeyboard to all Objects
				WM.onEvent(&kb_e);
			}

			// if mouse moved then ...
			else if (const sf::Event::MouseMoved* sf_mouse_event = sf_event->getIf<sf::Event::MouseMoved>()) {
/*
				EventMouse mouse_e;
				mouse_e.setMouseAction(MOVED);
				mouse_e.setMousePosition(Vector(
					static_cast<float>(sf_mouse_event->position.x),
					static_cast<float>(sf_mouse_event->position.y)));
				LM.writeLog("InputManager::getInput(): Mouse Moved - X: %d, Y: %d\n",
					sf_mouse_event->position.x, sf_mouse_event->position.y);

				WM.onEvent(&mouse_e);
*/
				sf::RenderWindow* window = DM.getWindow();
				if (!window) return;

				// Convert pixel coordinates to game coordinates using existing function
				Vector game_pos = DM.pixelsToSpaces(Vector(
					static_cast<float>(sf_mouse_event->position.x),
					static_cast<float>(sf_mouse_event->position.y)
				));

				// Log converted coordinates for debugging
				//LM.writeLog("InputManager::getInput(): Mouse Moved - Screen: (%d, %d), Game: (%.2f, %.2f)\n",
					//sf_mouse_event->position.x, sf_mouse_event->position.y, game_pos.getX(), game_pos.getY());

				// Send converted game coordinates
				EventMouse mouse_e;
				mouse_e.setMouseAction(MOVED);
				mouse_e.setMousePosition(game_pos);
				WM.onEvent(&mouse_e);

			}

			// if mouse button pressed/clicked then ...
			else if (const sf::Event::MouseButtonPressed* sf_mouseb_event = sf_event->getIf<sf::Event::MouseButtonPressed>()) {
				sf::RenderWindow* window = DM.getWindow();
				if (!window) return;

				// Convert mouse click position from pixels to game world coordinates
				Vector game_pos = DM.pixelsToSpaces(Vector(
					static_cast<float>(sf_mouseb_event->position.x),
					static_cast<float>(sf_mouseb_event->position.y)
				));

				// Log converted position for debugging
				//LM.writeLog("InputManager::getInput(): Mouse Button Pressed - Button: %d, Screen: (%d, %d), Game: (%.2f, %.2f)\n",
					//sf_mouseb_event->button, sf_mouseb_event->position.x, sf_mouseb_event->position.y,
					//game_pos.getX(), game_pos.getY());

				// Send updated game coordinates
				EventMouse mouse_e;
				mouse_e.setMouseAction(CLICKED);
				mouse_e.setMouseButton(static_cast<Mouse::Button>(sf_mouseb_event->button));
				mouse_e.setMousePosition(game_pos);
				WM.onEvent(&mouse_e);
			}
			// if window closed then...
/*			else if (sf_event->getIf<sf::Event::Closed>()) { 
				LM.writeLog("InputManager::getInput(): Window closed event detected.\n"); 
				GM.setGameOver(true);
			}
*/
		} // end of while

	} // end of getInput

} // end of namespace df