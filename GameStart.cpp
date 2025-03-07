//
// GameStart.cpp
//

// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameStart.h"
//#include "Hero.h"
#include "Music.h"
#include "Points.h"
//#include "Saucer.h"
#include "Fish.h"
#include "Grocer.h"
#include "Clam.h"
#include "Shark.h"
#include "Starfish.h"
#include "Life.h"

GameStart::GameStart() {
  setType("GameStart");

  // Link to "message" sprite.
  setSprite("gamestart");

  // Put in center of screen.
  setLocation(df::CENTER_CENTER);

  // Register for "keyboard" event.
#ifdef DF_REGISTER_INTEREST
  registerInterest(df::KEYBOARD_EVENT);
#endif
  
  time_animation = -1;

  // Play start music.
  p_music = RM.getMusic("ocean-background");
  playMusic();
}

// Play start music.
void GameStart::playMusic() {
  p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		if (getAnimation().getIndex() == time_animation -1) {
            start();
		}
		return 1;
	}



  if (p_e->getType() == df::KEYBOARD_EVENT) {
    df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::P: 			// play
	    setSprite("gamestart-sharkjaw");
        time_animation = getAnimation().getSprite()->getFrameCount();
      break;
    case df::Keyboard::Q:			// quit
      GM.setGameOver();
      break;
    default:
      break;
    }
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

void GameStart::start() {

  //// When game starts, destroy this object.
  WM.markForDelete(this);

    new Grocer;
    new Points;
    new Clam;
    new Shark;
    new Life();
    //new Starfish;
    for (int i = 0; i < 3; i++) {
        new Starfish;
    }
}

// Override default draw so as not to display "value".
int GameStart::draw() {
  df::Object::draw();
  return 0;
}
