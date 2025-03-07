//
// InputManager.cpp
//

// Engine includes
#include "InputManager.h"
#include <SFML/Window.hpp>
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventMouse.h"
#include "LogManager.h"

namespace df {

	InputManager::InputManager() {
		setType("InputManager");
	}

	InputManager& InputManager::getInstance() {
		static InputManager instance;
		return instance;
	}

	int InputManager::startUp() {
        if (!DM.startUp()) {
            return -1;
        }

        sf::RenderWindow* window = DM.getWindow();


        // Disable keyboard repeat
        window->setKeyRepeatEnabled(false);

        //window->setMouseCursorVisible(true);

		Manager::startUp();

		return 0;
	}

	void InputManager::shutDown() {

		sf::RenderWindow* window = DM.getWindow();
		window->setKeyRepeatEnabled(true);

		Manager::shutDown();

	}

    void InputManager::getInput() const {
       
        while (const std::optional<sf::Event> p_event = DM.getWindow()->pollEvent()) {

            if (p_event->is<sf::Event::Closed>()) {
                GM.setGameOver();
            }
            else {

                sf::Event e = p_event.value();

                if (const auto* keyPressed = p_event->getIf<sf::Event::KeyPressed>()) {

                    sf::Keyboard::Key key = keyPressed->code;

                    EventKeyboard event_keyboard;
                    event_keyboard.setKeyboardAction(KEY_PRESSED);

                    switch (key) {
                    case sf::Keyboard::Key::A:
                        event_keyboard.setKey(Keyboard::Key::A);
                        break;
                    case sf::Keyboard::Key::B:
                        event_keyboard.setKey(Keyboard::Key::B);
                        break;
                    case sf::Keyboard::Key::C:
                        event_keyboard.setKey(Keyboard::Key::C);
                        break;
                    case sf::Keyboard::Key::D:
                        event_keyboard.setKey(Keyboard::Key::D);
                        break;
                    case sf::Keyboard::Key::E:
                        event_keyboard.setKey(Keyboard::Key::E);
                        break;
                    case sf::Keyboard::Key::F:
                        event_keyboard.setKey(Keyboard::Key::F);
                        break;
                    case sf::Keyboard::Key::G:
                        event_keyboard.setKey(Keyboard::Key::G);
                        break;
                    case sf::Keyboard::Key::H:
                        event_keyboard.setKey(Keyboard::Key::H);
                        break;
                    case sf::Keyboard::Key::I:
                        event_keyboard.setKey(Keyboard::Key::I);
                        break;
                    case sf::Keyboard::Key::J:
                        event_keyboard.setKey(Keyboard::Key::J);
                        break;
                    case sf::Keyboard::Key::K:
                        event_keyboard.setKey(Keyboard::Key::K);
                        break;
                    case sf::Keyboard::Key::L:
                        event_keyboard.setKey(Keyboard::Key::L);
                        break;
                    case sf::Keyboard::Key::M:
                        event_keyboard.setKey(Keyboard::Key::M);
                        break;
                    case sf::Keyboard::Key::N:
                        event_keyboard.setKey(Keyboard::Key::N);
                        break;
                    case sf::Keyboard::Key::O:
                        event_keyboard.setKey(Keyboard::Key::O);
                        break;
                    case sf::Keyboard::Key::P:
                        event_keyboard.setKey(Keyboard::Key::P);
                        break;
                    case sf::Keyboard::Key::Q:
                        event_keyboard.setKey(Keyboard::Key::Q);
                        break;
                    case sf::Keyboard::Key::R:
                        event_keyboard.setKey(Keyboard::Key::R);
                        break;
                    case sf::Keyboard::Key::S:
                        event_keyboard.setKey(Keyboard::Key::S);
                        break;
                    case sf::Keyboard::Key::T:
                        event_keyboard.setKey(Keyboard::Key::T);
                        break;
                    case sf::Keyboard::Key::U:
                        event_keyboard.setKey(Keyboard::Key::U);
                        break;
                    case sf::Keyboard::Key::V:
                        event_keyboard.setKey(Keyboard::Key::V);
                        break;
                    case sf::Keyboard::Key::W:
                        event_keyboard.setKey(Keyboard::Key::W);
                        break;
                    case sf::Keyboard::Key::X:
                        event_keyboard.setKey(Keyboard::Key::X);
                        break;
                    case sf::Keyboard::Key::Y:
                        event_keyboard.setKey(Keyboard::Key::Y);
                        break;
                    case sf::Keyboard::Key::Z:
                        event_keyboard.setKey(Keyboard::Key::Z);
                        break;
                    case sf::Keyboard::Key::Num1:
                        event_keyboard.setKey(Keyboard::Key::NUM1);
                        break;
                    case sf::Keyboard::Key::Num2:
                        event_keyboard.setKey(Keyboard::Key::NUM2);
                        break;
                    case sf::Keyboard::Key::Num3:
                        event_keyboard.setKey(Keyboard::Key::NUM3);
                        break;
                    case sf::Keyboard::Key::Num4:
                        event_keyboard.setKey(Keyboard::Key::NUM4);
                        break;
                    case sf::Keyboard::Key::Num5:
                        event_keyboard.setKey(Keyboard::Key::NUM5);
                        break;
                    case sf::Keyboard::Key::Num6:
                        event_keyboard.setKey(Keyboard::Key::NUM6);
                        break;
                    case sf::Keyboard::Key::Num7:
                        event_keyboard.setKey(Keyboard::Key::NUM7);
                        break;
                    case sf::Keyboard::Key::Num8:
                        event_keyboard.setKey(Keyboard::Key::NUM8);
                        break;
                    case sf::Keyboard::Key::Num9:
                        event_keyboard.setKey(Keyboard::Key::NUM9);
                        break;
                    case sf::Keyboard::Key::Num0:
                        event_keyboard.setKey(Keyboard::Key::NUM0);
                        break;
                    case sf::Keyboard::Key::Space:
                        event_keyboard.setKey(Keyboard::Key::SPACE);
                        break;
                    case sf::Keyboard::Key::Enter:
                        event_keyboard.setKey(Keyboard::Key::RETURN);
                        break;
                    case sf::Keyboard::Key::Escape:
                        event_keyboard.setKey(Keyboard::Key::ESCAPE);
                        break;
                    case sf::Keyboard::Key::Tab:
                        event_keyboard.setKey(Keyboard::Key::TAB);
                        break;
                    case sf::Keyboard::Key::Left:
                        event_keyboard.setKey(Keyboard::Key::LEFTARROW);
                        break;
                    case sf::Keyboard::Key::Right:
                        event_keyboard.setKey(Keyboard::Key::RIGHTARROW);
                        break;
                    case sf::Keyboard::Key::Up:
                        event_keyboard.setKey(Keyboard::Key::UPARROW);
                        break;
                    case sf::Keyboard::Key::Down:
                        event_keyboard.setKey(Keyboard::Key::DOWNARROW);
                        break;
                    case sf::Keyboard::Key::Pause:
                        event_keyboard.setKey(Keyboard::Key::PAUSE);
                        break;
                    case sf::Keyboard::Key::Subtract:
                        event_keyboard.setKey(Keyboard::Key::MINUS);
                        break;
                    case sf::Keyboard::Key::Equal:
                        event_keyboard.setKey(Keyboard::Key::PLUS);
                        break;
                    case sf::Keyboard::Key::Grave:
                        event_keyboard.setKey(Keyboard::Key::TILDE);
                        break;
                    case sf::Keyboard::Key::Period:
                        event_keyboard.setKey(Keyboard::Key::PERIOD);
                        break;
                    case sf::Keyboard::Key::Comma:
                        event_keyboard.setKey(Keyboard::Key::COMMA);
                        break;
                    case sf::Keyboard::Key::Slash:
                        event_keyboard.setKey(Keyboard::Key::SLASH);
                        break;
                    case sf::Keyboard::Key::LControl:
                        event_keyboard.setKey(Keyboard::Key::LEFTCONTROL);
                        break;
                    case sf::Keyboard::Key::RControl:
                        event_keyboard.setKey(Keyboard::Key::RIGHTCONTROL);
                        break;
                    case sf::Keyboard::Key::LShift:
                        event_keyboard.setKey(Keyboard::Key::LEFTSHIFT);
                        break;
                    case sf::Keyboard::Key::RShift:
                        event_keyboard.setKey(Keyboard::Key::RIGHTSHIFT);
                        break;
                    case sf::Keyboard::Key::F1:
                        event_keyboard.setKey(Keyboard::Key::F1);
                        break;
                    case sf::Keyboard::Key::F2:
                        event_keyboard.setKey(Keyboard::Key::F2);
                        break;
                    case sf::Keyboard::Key::F3:
                        event_keyboard.setKey(Keyboard::Key::F3);
                        break;
                    case sf::Keyboard::Key::F4:
                        event_keyboard.setKey(Keyboard::Key::F4);
                        break;
                    case sf::Keyboard::Key::F5:
                        event_keyboard.setKey(Keyboard::Key::F5);
                        break;
                    case sf::Keyboard::Key::F6:
                        event_keyboard.setKey(Keyboard::Key::F6);
                        break;
                    case sf::Keyboard::Key::F7:
                        event_keyboard.setKey(Keyboard::Key::F7);
                        break;
                    case sf::Keyboard::Key::F8:
                        event_keyboard.setKey(Keyboard::Key::F8);
                        break;
                    case sf::Keyboard::Key::F9:
                        event_keyboard.setKey(Keyboard::Key::F9);
                        break;
                    case sf::Keyboard::Key::F10:
                        event_keyboard.setKey(Keyboard::Key::F10);
                        break;
                    case sf::Keyboard::Key::F11:
                        event_keyboard.setKey(Keyboard::Key::F11);
                        break;
                    case sf::Keyboard::Key::F12:
                        event_keyboard.setKey(Keyboard::Key::F12);
                        break;
                    default:
                        event_keyboard.setKey(Keyboard::Key::UNDEFINED_KEY);
                        break;
                    }

                    WM.onEvent(&event_keyboard);

                    // Check which key is pressed
                    switch (key) {
                    case sf::Keyboard::Key::A:
                        LM.writeLog("Key Pressed A");
                        break;
                    case sf::Keyboard::Key::B:
                        LM.writeLog("Key Pressed B");
                        break;
                    case sf::Keyboard::Key::C:
                        LM.writeLog("Key Pressed C");
                        break;
                    case sf::Keyboard::Key::D:
                        LM.writeLog("Key Pressed D");
                        break;
                    case sf::Keyboard::Key::E:
                        LM.writeLog("Key Pressed E");
                        break;
                    case sf::Keyboard::Key::F:
                        LM.writeLog("Key Pressed F");
                        break;
                    case sf::Keyboard::Key::G:
                        LM.writeLog("Key Pressed G");
                        break;
                    case sf::Keyboard::Key::H:
                        LM.writeLog("Key Pressed H");
                        break;
                    case sf::Keyboard::Key::I:
                        LM.writeLog("Key Pressed I");
                        break;
                    case sf::Keyboard::Key::J:
                        LM.writeLog("Key Pressed J");
                        break;
                    case sf::Keyboard::Key::K:
                        LM.writeLog("Key Pressed K");
                        break;
                    case sf::Keyboard::Key::L:
                        LM.writeLog("Key Pressed L");
                        break;
                    case sf::Keyboard::Key::M:
                        LM.writeLog("Key Pressed M");
                        break;
                    case sf::Keyboard::Key::N:
                        LM.writeLog("Key Pressed N");
                        break;
                    case sf::Keyboard::Key::O:
                        LM.writeLog("Key Pressed O");
                        break;
                    case sf::Keyboard::Key::P:
                        LM.writeLog("Key Pressed P");
                        break;
                    case sf::Keyboard::Key::Q:
                        LM.writeLog("Key Pressed Q");
                        break;
                    case sf::Keyboard::Key::R:
                        LM.writeLog("Key Pressed R");
                        break;
                    case sf::Keyboard::Key::S:
                        LM.writeLog("Key Pressed S");
                        break;
                    case sf::Keyboard::Key::T:
                        LM.writeLog("Key Pressed T");
                        break;
                    case sf::Keyboard::Key::U:
                        LM.writeLog("Key Pressed U");
                        break;
                    case sf::Keyboard::Key::V:
                        LM.writeLog("Key Pressed V");
                        break;
                    case sf::Keyboard::Key::W:
                        LM.writeLog("Key Pressed W");
                        break;
                    case sf::Keyboard::Key::X:
                        LM.writeLog("Key Pressed X");
                        break;
                    case sf::Keyboard::Key::Y:
                        LM.writeLog("Key Pressed Y");
                        break;
                    case sf::Keyboard::Key::Z:
                        LM.writeLog("Key Pressed Z");
                        break;
                    case sf::Keyboard::Key::Num1:
                        LM.writeLog("Key Pressed 1");
                        break;
                    case sf::Keyboard::Key::Num2:
                        LM.writeLog("Key Pressed 2");
                        break;
                    case sf::Keyboard::Key::Num3:
                        LM.writeLog("Key Pressed 3");
                        break;
                    case sf::Keyboard::Key::Num4:
                        LM.writeLog("Key Pressed 4");
                        break;
                    case sf::Keyboard::Key::Num5:
                        LM.writeLog("Key Pressed 5");
                        break;
                    case sf::Keyboard::Key::Num6:
                        LM.writeLog("Key Pressed 6");
                        break;
                    case sf::Keyboard::Key::Num7:
                        LM.writeLog("Key Pressed 7");
                        break;
                    case sf::Keyboard::Key::Num8:
                        LM.writeLog("Key Pressed 8");
                        break;
                    case sf::Keyboard::Key::Num9:
                        LM.writeLog("Key Pressed 9");
                        break;
                    case sf::Keyboard::Key::Num0:
                        LM.writeLog("Key Pressed 0");
                        break;
                    case sf::Keyboard::Key::Space:
                        LM.writeLog("Key Pressed SPACE");
                        break;
                    case sf::Keyboard::Key::Enter:
                        LM.writeLog("Key Pressed RETURN");
                        break;
                    case sf::Keyboard::Key::Escape:
                        LM.writeLog("Key Pressed ESCAPE");
                        break;
                    case sf::Keyboard::Key::Tab:
                        LM.writeLog("Key Pressed TAB");
                        break;
                    case sf::Keyboard::Key::Left:
                        LM.writeLog("Key Pressed LEFT ARROW");
                        break;
                    case sf::Keyboard::Key::Right:
                        LM.writeLog("Key Pressed RIGHT ARROW");
                        break;
                    case sf::Keyboard::Key::Up:
                        LM.writeLog("Key Pressed UP ARROW");
                        break;
                    case sf::Keyboard::Key::Down:
                        LM.writeLog("Key Pressed DOWN ARROW");
                        break;
                    case sf::Keyboard::Key::Pause:
                        LM.writeLog("Key Pressed PAUSE");
                        break;
                    case sf::Keyboard::Key::Subtract:
                        LM.writeLog("Key Pressed MINUS");
                        break;
                    case sf::Keyboard::Key::Equal:
                        LM.writeLog("Key Pressed PLUS");
                        break;
                    case sf::Keyboard::Key::Grave:
                        LM.writeLog("Key Pressed TILDE");
                        break;
                    case sf::Keyboard::Key::Period:
                        LM.writeLog("Key Pressed PERIOD");
                        break;
                    case sf::Keyboard::Key::Comma:
                        LM.writeLog("Key Pressed COMMA");
                        break;
                    case sf::Keyboard::Key::Slash:
                        LM.writeLog("Key Pressed SLASH");
                        break;
                    case sf::Keyboard::Key::LControl:
                        LM.writeLog("Key Pressed LEFT CONTROL");
                        break;
                    case sf::Keyboard::Key::RControl:
                        LM.writeLog("Key Pressed RIGHT CONTROL");
                        break;
                    case sf::Keyboard::Key::LShift:
                        LM.writeLog("Key Pressed LEFT SHIFT");
                        break;
                    case sf::Keyboard::Key::RShift:
                        LM.writeLog("Key Pressed RIGHT SHIFT");
                        break;
                    case sf::Keyboard::Key::F1:
                        LM.writeLog("Key Pressed F1");
                        break;
                    case sf::Keyboard::Key::F2:
                        LM.writeLog("Key Pressed F2");
                        break;
                    case sf::Keyboard::Key::F3:
                        LM.writeLog("Key Pressed F3");
                        break;
                    case sf::Keyboard::Key::F4:
                        LM.writeLog("Key Pressed F4");
                        break;
                    case sf::Keyboard::Key::F5:
                        LM.writeLog("Key Pressed F5");
                        break;
                    case sf::Keyboard::Key::F6:
                        LM.writeLog("Key Pressed F6");
                        break;
                    case sf::Keyboard::Key::F7:
                        LM.writeLog("Key Pressed F7");
                        break;
                    case sf::Keyboard::Key::F8:
                        LM.writeLog("Key Pressed F8");
                        break;
                    case sf::Keyboard::Key::F9:
                        LM.writeLog("Key Pressed F9");
                        break;
                    case sf::Keyboard::Key::F10:
                        LM.writeLog("Key Pressed F10");
                        break;
                    case sf::Keyboard::Key::F11:
                        LM.writeLog("Key Pressed F11");
                        break;
                    case sf::Keyboard::Key::F12:
                        LM.writeLog("Key Pressed F12");
                        break;
                    default:
                        LM.writeLog("Key Pressed UNDEFINED");
                        break;
                    }
                    

                } else if (const auto* keyReleased = p_event->getIf<sf::Event::KeyReleased>()) {
                    
                    sf::Keyboard::Key key = keyReleased->code;

                    EventKeyboard event_keyboard;
                    event_keyboard.setKeyboardAction(KEY_RELEASED);

                    switch (key) {
                    case sf::Keyboard::Key::A:
                        event_keyboard.setKey(Keyboard::Key::A);
                        break;
                    case sf::Keyboard::Key::B:
                        event_keyboard.setKey(Keyboard::Key::B);
                        break;
                    case sf::Keyboard::Key::C:
                        event_keyboard.setKey(Keyboard::Key::C);
                        break;
                    case sf::Keyboard::Key::D:
                        event_keyboard.setKey(Keyboard::Key::D);
                        break;
                    case sf::Keyboard::Key::E:
                        event_keyboard.setKey(Keyboard::Key::E);
                        break;
                    case sf::Keyboard::Key::F:
                        event_keyboard.setKey(Keyboard::Key::F);
                        break;
                    case sf::Keyboard::Key::G:
                        event_keyboard.setKey(Keyboard::Key::G);
                        break;
                    case sf::Keyboard::Key::H:
                        event_keyboard.setKey(Keyboard::Key::H);
                        break;
                    case sf::Keyboard::Key::I:
                        event_keyboard.setKey(Keyboard::Key::I);
                        break;
                    case sf::Keyboard::Key::J:
                        event_keyboard.setKey(Keyboard::Key::J);
                        break;
                    case sf::Keyboard::Key::K:
                        event_keyboard.setKey(Keyboard::Key::K);
                        break;
                    case sf::Keyboard::Key::L:
                        event_keyboard.setKey(Keyboard::Key::L);
                        break;
                    case sf::Keyboard::Key::M:
                        event_keyboard.setKey(Keyboard::Key::M);
                        break;
                    case sf::Keyboard::Key::N:
                        event_keyboard.setKey(Keyboard::Key::N);
                        break;
                    case sf::Keyboard::Key::O:
                        event_keyboard.setKey(Keyboard::Key::O);
                        break;
                    case sf::Keyboard::Key::P:
                        event_keyboard.setKey(Keyboard::Key::P);
                        break;
                    case sf::Keyboard::Key::Q:
                        event_keyboard.setKey(Keyboard::Key::Q);
                        break;
                    case sf::Keyboard::Key::R:
                        event_keyboard.setKey(Keyboard::Key::R);
                        break;
                    case sf::Keyboard::Key::S:
                        event_keyboard.setKey(Keyboard::Key::S);
                        break;
                    case sf::Keyboard::Key::T:
                        event_keyboard.setKey(Keyboard::Key::T);
                        break;
                    case sf::Keyboard::Key::U:
                        event_keyboard.setKey(Keyboard::Key::U);
                        break;
                    case sf::Keyboard::Key::V:
                        event_keyboard.setKey(Keyboard::Key::V);
                        break;
                    case sf::Keyboard::Key::W:
                        event_keyboard.setKey(Keyboard::Key::W);
                        break;
                    case sf::Keyboard::Key::X:
                        event_keyboard.setKey(Keyboard::Key::X);
                        break;
                    case sf::Keyboard::Key::Y:
                        event_keyboard.setKey(Keyboard::Key::Y);
                        break;
                    case sf::Keyboard::Key::Z:
                        event_keyboard.setKey(Keyboard::Key::Z);
                        break;
                    case sf::Keyboard::Key::Num1:
                        event_keyboard.setKey(Keyboard::Key::NUM1);
                        break;
                    case sf::Keyboard::Key::Num2:
                        event_keyboard.setKey(Keyboard::Key::NUM2);
                        break;
                    case sf::Keyboard::Key::Num3:
                        event_keyboard.setKey(Keyboard::Key::NUM3);
                        break;
                    case sf::Keyboard::Key::Num4:
                        event_keyboard.setKey(Keyboard::Key::NUM4);
                        break;
                    case sf::Keyboard::Key::Num5:
                        event_keyboard.setKey(Keyboard::Key::NUM5);
                        break;
                    case sf::Keyboard::Key::Num6:
                        event_keyboard.setKey(Keyboard::Key::NUM6);
                        break;
                    case sf::Keyboard::Key::Num7:
                        event_keyboard.setKey(Keyboard::Key::NUM7);
                        break;
                    case sf::Keyboard::Key::Num8:
                        event_keyboard.setKey(Keyboard::Key::NUM8);
                        break;
                    case sf::Keyboard::Key::Num9:
                        event_keyboard.setKey(Keyboard::Key::NUM9);
                        break;
                    case sf::Keyboard::Key::Num0:
                        event_keyboard.setKey(Keyboard::Key::NUM0);
                        break;
                    case sf::Keyboard::Key::Space:
                        event_keyboard.setKey(Keyboard::Key::SPACE);
                        break;
                    case sf::Keyboard::Key::Enter:
                        event_keyboard.setKey(Keyboard::Key::RETURN);
                        break;
                    case sf::Keyboard::Key::Escape:
                        event_keyboard.setKey(Keyboard::Key::ESCAPE);
                        break;
                    case sf::Keyboard::Key::Tab:
                        event_keyboard.setKey(Keyboard::Key::TAB);
                        break;
                    case sf::Keyboard::Key::Left:
                        event_keyboard.setKey(Keyboard::Key::LEFTARROW);
                        break;
                    case sf::Keyboard::Key::Right:
                        event_keyboard.setKey(Keyboard::Key::RIGHTARROW);
                        break;
                    case sf::Keyboard::Key::Up:
                        event_keyboard.setKey(Keyboard::Key::UPARROW);
                        break;
                    case sf::Keyboard::Key::Down:
                        event_keyboard.setKey(Keyboard::Key::DOWNARROW);
                        break;
                    case sf::Keyboard::Key::Pause:
                        event_keyboard.setKey(Keyboard::Key::PAUSE);
                        break;
                    case sf::Keyboard::Key::Subtract:
                        event_keyboard.setKey(Keyboard::Key::MINUS);
                        break;
                    case sf::Keyboard::Key::Equal:
                        event_keyboard.setKey(Keyboard::Key::PLUS);
                        break;
                    case sf::Keyboard::Key::Grave:
                        event_keyboard.setKey(Keyboard::Key::TILDE);
                        break;
                    case sf::Keyboard::Key::Period:
                        event_keyboard.setKey(Keyboard::Key::PERIOD);
                        break;
                    case sf::Keyboard::Key::Comma:
                        event_keyboard.setKey(Keyboard::Key::COMMA);
                        break;
                    case sf::Keyboard::Key::Slash:
                        event_keyboard.setKey(Keyboard::Key::SLASH);
                        break;
                    case sf::Keyboard::Key::LControl:
                        event_keyboard.setKey(Keyboard::Key::LEFTCONTROL);
                        break;
                    case sf::Keyboard::Key::RControl:
                        event_keyboard.setKey(Keyboard::Key::RIGHTCONTROL);
                        break;
                    case sf::Keyboard::Key::LShift:
                        event_keyboard.setKey(Keyboard::Key::LEFTSHIFT);
                        break;
                    case sf::Keyboard::Key::RShift:
                        event_keyboard.setKey(Keyboard::Key::RIGHTSHIFT);
                        break;
                    case sf::Keyboard::Key::F1:
                        event_keyboard.setKey(Keyboard::Key::F1);
                        break;
                    case sf::Keyboard::Key::F2:
                        event_keyboard.setKey(Keyboard::Key::F2);
                        break;
                    case sf::Keyboard::Key::F3:
                        event_keyboard.setKey(Keyboard::Key::F3);
                        break;
                    case sf::Keyboard::Key::F4:
                        event_keyboard.setKey(Keyboard::Key::F4);
                        break;
                    case sf::Keyboard::Key::F5:
                        event_keyboard.setKey(Keyboard::Key::F5);
                        break;
                    case sf::Keyboard::Key::F6:
                        event_keyboard.setKey(Keyboard::Key::F6);
                        break;
                    case sf::Keyboard::Key::F7:
                        event_keyboard.setKey(Keyboard::Key::F7);
                        break;
                    case sf::Keyboard::Key::F8:
                        event_keyboard.setKey(Keyboard::Key::F8);
                        break;
                    case sf::Keyboard::Key::F9:
                        event_keyboard.setKey(Keyboard::Key::F9);
                        break;
                    case sf::Keyboard::Key::F10:
                        event_keyboard.setKey(Keyboard::Key::F10);
                        break;
                    case sf::Keyboard::Key::F11:
                        event_keyboard.setKey(Keyboard::Key::F11);
                        break;
                    case sf::Keyboard::Key::F12:
                        event_keyboard.setKey(Keyboard::Key::F12);
                        break;
                    default:
                        event_keyboard.setKey(Keyboard::Key::UNDEFINED_KEY);
                        break;
                    }

                    WM.onEvent(&event_keyboard);

                    LM.writeLog("Keyboard Released");
                
                } else if (const auto* mouseMoved = p_event->getIf<sf::Event::MouseMoved>()) {

                    Vector mouse;
                    mouse.setX(mouseMoved->position.x);
                    mouse.setY(mouseMoved->position.y);
                    
                    //LM.writeLog("Mouse (%d, %d)", mouseMoved->position.x, mouseMoved->position.y);

                    EventMouse event_mouse;
                    event_mouse.setMouseAction(MOVED);
                    event_mouse.setMousePosition(DM.pixelsToSpaces(mouse));
                    WM.onEvent(&event_mouse);


                } else if (const auto* mousePresssed = p_event->getIf<sf::Event::MouseButtonPressed>()) {

                    sf::Mouse::Button mouse = mousePresssed->button;

                    EventMouse event_mouse;
                    event_mouse.setMouseAction(CLICKED);

                    switch (mouse) {
                    case sf::Mouse::Button::Left:
                        event_mouse.setMouseButton(Mouse::Button::LEFT);
                        LM.writeLog("Mouse clicked Button LEFT");
                        break;
                    case sf::Mouse::Button::Right:
                        event_mouse.setMouseButton(Mouse::Button::RIGHT);
                        LM.writeLog("Mouse clicked Button RIGHT");
                        break;
                    case sf::Mouse::Button::Middle:
                        event_mouse.setMouseButton(Mouse::Button::MIDDLE);
                        LM.writeLog("Mouse clicked Button MIDDLE");
                        break;
                    default:
                        event_mouse.setMouseButton(Mouse::Button::UNDEFINED_MOUSE_BUTTON);
                        LM.writeLog("Mouse clicked Button UNDEFINED_MOUSE_BUTTON");
                        break;
                    }

                    Vector mousePos;
                    mousePos.setX(mousePresssed->position.x);
                    mousePos.setY(mousePresssed->position.y);

                    event_mouse.setMousePosition(DM.pixelsToSpaces(mousePos));
                    WM.onEvent(&event_mouse);

                }

                
            }
        }


    }





}