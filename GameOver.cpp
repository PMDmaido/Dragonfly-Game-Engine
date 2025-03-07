//
// GameOver.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameOver.h"
#include "GameStart.h"
#include "Fish.h"
#include "Bomb.h"

GameOver::GameOver(bool win) {

  setType("GameOver");

  // Link to "message" sprite.
  if (win)
      if (setSprite("shark-won") == 0)
      time_to_live = getAnimation().getSprite()->getFrameCount() * 15;
  else
      time_to_live = 0;
  else
      if (setSprite("gameover") == 0)
          time_to_live = getAnimation().getSprite()->getFrameCount() * 15;
      else
          time_to_live = 0;

  // Put in center of window.
  setLocation(df::CENTER_CENTER);
  
  // Register for step event.
#ifdef DF_REGISTER_INTEREST
  registerInterest(df::STEP_EVENT);
#endif
  
  // Play "game over" sound.
  df::Sound *p_sound = RM.getSound("game over");
  p_sound->play();
}

// When done, game over so shut down.
GameOver::~GameOver() {
  WM.markForDelete(this);
  GM.setGameOver();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// Count down to end of message.
void GameOver::step() {
  time_to_live--;
  if (time_to_live <= 0) { 
    WM.markForDelete(this);
  }
}

// Override default draw so as not to display "value".
int GameOver::draw() {
	df::ObjectList ol = WM.getAllObjects();

    for (int i = 0; i < ol.getCount(); i++) {
        df::Object* p_o = ol[i];
        if (dynamic_cast<Fish*>(p_o) || dynamic_cast<Bomb*>(p_o)) {
            WM.markForDelete(p_o);
        }
    }
  df::Object::draw();
  return 0;
}
