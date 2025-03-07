#pragma once
//
// InputManager.h
//

// Engine Includes.
#include "Manager.h"
#include "EventKeyboard.h"
#include <SFML/Window.hpp>

#define IM df::InputManager::getInstance()

namespace df {

    class InputManager : public Manager {
    private:
        
        InputManager();             // Private
        InputManager(const InputManager&);
        void operator=(const InputManager&);

    public:
        // Get the singleton instance of InputManager
        static InputManager& getInstance();

        // Get window ready to capture input.
        // Returns 0 if ok, else -1.
        int startUp();

        // Revert back to normal window mode.
        void shutDown();

        // Get input from keyboard and mouse.
        // Pass events to all Objects.
        void getInput() const;

    };
}

