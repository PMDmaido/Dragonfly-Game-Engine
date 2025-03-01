//
// InputManager.h 
//

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "Manager.h"
#include "DisplayManager.h"
#include "Event.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"
#include "WorldManager.h"

//#include "EventKeyboard.h"

namespace df {

	class InputManager : public Manager {
		private:
			InputManager();                      ///< Private since a singleton.
			InputManager(InputManager const&);   ///< Don't allow copy.
			void operator=(InputManager const&); ///< Don't allow assignment.

	public:
		/// Get the one and only instance of the InputManager.
		static InputManager& getInstance();

		// Get window ready to capture input.
		// Return 0 if ok, else -1.
		int startUp() override;

		// Revert back to normal window mode.
		void shutDown() override;

		// Get input from the keyboard and mouse.
		// Pass event along to all interested Objects.
		void getInput() const;
	};

} // end of namespace df


#endif // __INPUT_MANAGER_H__
