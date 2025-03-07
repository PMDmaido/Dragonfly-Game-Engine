//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
 
// Game includes.
#include "GameStart.h"
#include "DisplayManager.h"

#include "utility.h"
#include "EventView.h"
#include "WorldManager.h"

#include "Fish.h"
#include "Grocer.h"
#include "Clam.h"
#include "Shark.h"
#include "Points.h"
#include "Star.h"
#include "Life.h"
#include "Pearl.h"


// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();

  // Run game (this blocks until game loop is over).
  GM.run();
 
  // Shut everything down.
  //GM.shutDown();
}
 
// Load resources (sprites, sound effects, music).
void loadResources(void) {

  // Load sprites
  RM.loadSprite("sprites-simple/gamestart-shark-spr.txt", "gamestart");
  RM.loadSprite("sprites-simple/gamestart-sharkjaw-spr.txt", "gamestart-sharkjaw");
  RM.loadSprite("sprites-simple/gameover-spr.txt", "gameover");

  RM.loadSprite("sprites-simple/little-fish-right-spr.txt", "little-fish-right");
  RM.loadSprite("sprites-simple/small-fish-right-spr.txt", "small-fish-right");
  RM.loadSprite("sprites-simple/medium-fish-right-spr.txt", "medium-fish-right");

  RM.loadSprite("sprites-simple/little-fish-left-spr.txt", "little-fish-left");
  RM.loadSprite("sprites-simple/small-fish-left-spr.txt", "small-fish-left");
  RM.loadSprite("sprites-simple/medium-fish-left-spr.txt", "medium-fish-left");

  RM.loadSprite("sprites-simple/small-shark-right-spr.txt", "small-shark-right");
  RM.loadSprite("sprites-simple/medium-shark-right-spr.txt", "medium-shark-right");
  RM.loadSprite("sprites-simple/large-shark-right-spr.txt", "large-shark-right");

  RM.loadSprite("sprites-simple/small-shark-left-spr.txt", "small-shark-left");
  RM.loadSprite("sprites-simple/medium-shark-left-spr.txt", "medium-shark-left");
  RM.loadSprite("sprites-simple/large-shark-left-spr.txt", "large-shark-left");

  RM.loadSprite("sprites-simple/starfish-bubble-spr.txt", "bubble");
  RM.loadSprite("sprites-simple/diver-spr.txt", "diver");
  RM.loadSprite("sprites-simple/clam-spr.txt", "clam");
  RM.loadSprite("sprites-simple/c-clam-spr.txt", "c-clam");
  RM.loadSprite("sprites-simple/pearl-spr.txt", "pearl");
  RM.loadSprite("sprites-simple/bomb-spr.txt", "bomb");
  RM.loadSprite("sprites-simple/shark-won-spr.txt", "shark-won");


  // Load sounds
  RM.loadSound("sounds/eat.wav", "eat");
  RM.loadSound("sounds/game-over.wav", "game over");
  RM.loadSound("sounds/starfish.wav", "starfish");
  RM.loadSound("sounds/boost.wav", "boost");
  RM.loadSound("sounds/hit.wav", "hit");
  RM.loadSound("sounds/yay.wav", "yay");

  RM.loadMusic("sounds/start-music.wav", "start music");
  RM.loadMusic("sounds/ocean-background.wav", "ocean-background");
}
 
// Populate world with some objects.
void populateWorld(void) {

    for (int i = 0; i < 16; i++) {
		new Star;
	}

	new GameStart();

    //new Clam();
    

  // Spawn some Stars.
  //for (int i = 0; i < 16; i++) {

    //Fish* p_f = new Fish("little-fish");
	//p_f->start(0.25);
    //p_f->setPosition(df::Vector(12, 12));
  //}
    //new Life();
    //new Pearl(df::Vector(10, 10));
    //new Shark();
}
