//
// EventMouse.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "LogManager.h"

namespace df {
	// Create Mouse Event.
	EventMouse::EventMouse() {
		setType(MSE_EVENT);
		m_mouse_action = UNDEFINED_MOUSE_ACTION;
		m_mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON;
		m_mouse_xy = Vector();
	}
	// Set mouse event's action.
	void EventMouse::setMouseAction(EventMouseAction new_mouse_action) {
		m_mouse_action = new_mouse_action;
	}
	// Get mouse event's action.
	EventMouseAction EventMouse::getMouseAction() const {
		return m_mouse_action;
	}
	// Set mouse event's button.
	void EventMouse::setMouseButton(Mouse::Button new_mouse_button) {
		m_mouse_button = new_mouse_button;
	}
	// Get mouse event's button.
	Mouse::Button EventMouse::getMouseButton() const {
		return m_mouse_button;
	}
	// Set mouse event's position.
	void EventMouse::setMousePosition(Vector new_mouse_xy) {
		m_mouse_xy = new_mouse_xy;
	}
	// Get mouse event's position.
	Vector EventMouse::getMousePosition() const {
		return m_mouse_xy;
	}
} // end of namespace df