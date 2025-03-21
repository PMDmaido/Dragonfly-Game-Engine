///
/// A "keyboard" event
/// 

#ifndef __EVENT_KEYBOARD_H__
#define __EVENT_KEYBOARD_H__

#include "Event.h"
#include <SFML/Window/Keyboard.hpp>

namespace df {

	const std::string KEYBOARD_EVENT = "df::keyboard";

	/// Types of keyboard actions Dragonfly recognizes.
	enum EventKeyboardAction {
		UNDEFINED_KEYBOARD_ACTION = -1, ///< Undefined
		KEY_PRESSED,			  ///< Was down
		KEY_RELEASED,			  ///< Was released
		//KEY_DOWN,			  ///< Is down
	};

	/// Keyboard namespace.
	namespace Keyboard {
		/// Keys Dragonfly recognizes.
		enum Key {
			UNDEFINED_KEY = -1,
			SPACE, RETURN, ESCAPE, TAB, LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW,
			PAUSE, MINUS, PLUS, TILDE, PERIOD, COMMA, SLASH,
			EQUAL, BACKSLASH, MULTIPLY, QUOTE, SEMICOLON,
			LEFTCONTROL, RIGHTCONTROL,
			LEFTSHIFT, RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0, 
			//BACKSPACE, QMARK, LBRACKET, RBRACKET, GRAVE,
		};
	} // end of namespace Keyboard

	class EventKeyboard : public Event {

	private:
		Keyboard::Key m_key_val;	          ///< Key value.
		EventKeyboardAction m_keyboard_action;  ///< Key action.

	public:
		EventKeyboard();

		/// Set key in event.
		virtual void setKey(Keyboard::Key new_key);

		/// Get key from event.
		virtual Keyboard::Key getKey() const;

		/// Set keyboard event action.
		virtual void setKeyboardAction(EventKeyboardAction new_action);

		/// Get keyboard event action.
		virtual EventKeyboardAction getKeyboardAction() const;

		/// Convert from SFML key to Dragonfly key.
		static Keyboard::Key convertFromSFML(sf::Keyboard::Key sfml_key); 
	};

} // end of namespace df
#endif // __EVENT_KEYBOARD_H__

