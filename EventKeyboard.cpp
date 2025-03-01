// 
// EventKeyboard.cpp
//

// Engine includes.
#include "EventKeyboard.h"
#include "LogManager.h"

namespace df {
	// Create keyboard event.
	EventKeyboard::EventKeyboard() {
		setType(KEYBOARD_EVENT);
		m_key_val = Keyboard::UNDEFINED_KEY;
		m_keyboard_action = UNDEFINED_KEYBOARD_ACTION;
	}
	// Set key in event.
	void EventKeyboard::setKey(Keyboard::Key new_key) {
		m_key_val = new_key;
	}
	// Get key from event.
	Keyboard::Key EventKeyboard::getKey() const {
		return m_key_val;
	}
	// Set keyboard event action.
	void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) {
		m_keyboard_action = new_action;
	}
	// Get keyboard event action.
	EventKeyboardAction EventKeyboard::getKeyboardAction() const {
		return m_keyboard_action;
	}

	// Convert from SFML key to Dragonfly key.
	Keyboard::Key EventKeyboard::convertFromSFML(sf::Keyboard::Key sfml_key) {

		switch (sfml_key) {
			// Alphabetic keys
		case sf::Keyboard::Key::A: return Keyboard::Key::A;
		case sf::Keyboard::Key::B: return Keyboard::Key::B;
		case sf::Keyboard::Key::C: return Keyboard::Key::C;
		case sf::Keyboard::Key::D: return Keyboard::Key::D;
		case sf::Keyboard::Key::E: return Keyboard::Key::E;
		case sf::Keyboard::Key::F: return Keyboard::Key::F;
		case sf::Keyboard::Key::G: return Keyboard::Key::G;
		case sf::Keyboard::Key::H: return Keyboard::Key::H;
		case sf::Keyboard::Key::I: return Keyboard::Key::I;
		case sf::Keyboard::Key::J: return Keyboard::Key::J;
		case sf::Keyboard::Key::K: return Keyboard::Key::K;
		case sf::Keyboard::Key::L: return Keyboard::Key::L;
		case sf::Keyboard::Key::M: return Keyboard::Key::M;
		case sf::Keyboard::Key::N: return Keyboard::Key::N;
		case sf::Keyboard::Key::O: return Keyboard::Key::O;
		case sf::Keyboard::Key::P: return Keyboard::Key::P;
		case sf::Keyboard::Key::Q: return Keyboard::Key::Q;
		case sf::Keyboard::Key::R: return Keyboard::Key::R;
		case sf::Keyboard::Key::S: return Keyboard::Key::S;
		case sf::Keyboard::Key::T: return Keyboard::Key::T;
		case sf::Keyboard::Key::U: return Keyboard::Key::U;
		case sf::Keyboard::Key::V: return Keyboard::Key::V;
		case sf::Keyboard::Key::W: return Keyboard::Key::W;
		case sf::Keyboard::Key::X: return Keyboard::Key::X;
		case sf::Keyboard::Key::Y: return Keyboard::Key::Y;
		case sf::Keyboard::Key::Z: return Keyboard::Key::Z;
			// Numeric keys
		case sf::Keyboard::Key::Num0: return Keyboard::Key::NUM0;
		case sf::Keyboard::Key::Num1: return Keyboard::Key::NUM1;
		case sf::Keyboard::Key::Num2: return Keyboard::Key::NUM2;
		case sf::Keyboard::Key::Num3: return Keyboard::Key::NUM3;
		case sf::Keyboard::Key::Num4: return Keyboard::Key::NUM4;
		case sf::Keyboard::Key::Num5: return Keyboard::Key::NUM5;
		case sf::Keyboard::Key::Num6: return Keyboard::Key::NUM6;
		case sf::Keyboard::Key::Num7: return Keyboard::Key::NUM7;
		case sf::Keyboard::Key::Num8: return Keyboard::Key::NUM8;
		case sf::Keyboard::Key::Num9: return Keyboard::Key::NUM9;
			// Special keys
		case sf::Keyboard::Key::Escape: return Keyboard::Key::ESCAPE;
		case sf::Keyboard::Key::LControl: return Keyboard::Key::LEFTCONTROL;
		case sf::Keyboard::Key::LShift: return Keyboard::Key::LEFTSHIFT;
		case sf::Keyboard::Key::RControl: return Keyboard::Key::RIGHTCONTROL;
		case sf::Keyboard::Key::RShift: return Keyboard::Key::RIGHTSHIFT;
		case sf::Keyboard::Key::Space: return Keyboard::Key::SPACE;
		case sf::Keyboard::Key::Enter: return Keyboard::Key::RETURN; // Enter/Return key
		case sf::Keyboard::Key::Tab: return Keyboard::Key::TAB;
		case sf::Keyboard::Key::Left: return Keyboard::Key::LEFTARROW;
		case sf::Keyboard::Key::Right: return Keyboard::Key::RIGHTARROW;
		case sf::Keyboard::Key::Up: return Keyboard::Key::UPARROW;
		case sf::Keyboard::Key::Down: return Keyboard::Key::DOWNARROW;
		case sf::Keyboard::Key::Pause: return Keyboard::Key::PAUSE;

		case sf::Keyboard::Key::Subtract: return Keyboard::Key::MINUS; // -
		case sf::Keyboard::Key::Add: return Keyboard::Key::PLUS; // +
		case sf::Keyboard::Key::Grave: return Keyboard::Key::TILDE; // ~
		case sf::Keyboard::Key::Period: return Keyboard::Key::PERIOD; // .
		case sf::Keyboard::Key::Comma: return Keyboard::Key::COMMA; // ,
		case sf::Keyboard::Key::Slash: return Keyboard::Key::SLASH; // /
		case sf::Keyboard::Key::Equal: return Keyboard::Key::EQUAL; // =
		case sf::Keyboard::Key::Backslash: return Keyboard::Key::BACKSLASH; // \ //
		case sf::Keyboard::Key::Multiply: return Keyboard::Key::MULTIPLY; // *
		case sf::Keyboard::Key::Apostrophe: return Keyboard::Key::QUOTE; // '
		case sf::Keyboard::Key::Semicolon: return Keyboard::Key::SEMICOLON; // ;

			// F keys
		case sf::Keyboard::Key::F1: return Keyboard::Key::F1;
		case sf::Keyboard::Key::F2: return Keyboard::Key::F2;
		case sf::Keyboard::Key::F3: return Keyboard::Key::F3;
		case sf::Keyboard::Key::F4: return Keyboard::Key::F4;
		case sf::Keyboard::Key::F5: return Keyboard::Key::F5;
		case sf::Keyboard::Key::F6: return Keyboard::Key::F6;
		case sf::Keyboard::Key::F7: return Keyboard::Key::F7;
		case sf::Keyboard::Key::F8: return Keyboard::Key::F8;
		case sf::Keyboard::Key::F9: return Keyboard::Key::F9;
		case sf::Keyboard::Key::F10: return Keyboard::Key::F10;
		case sf::Keyboard::Key::F11: return Keyboard::Key::F11;
		case sf::Keyboard::Key::F12: return Keyboard::Key::F12;
		} // end switch
	} // end convertFromSFML
} // end of namespace df