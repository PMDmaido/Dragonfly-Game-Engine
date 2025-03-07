#pragma once
//
// game.h
//

#ifndef GAME_H
#define GAME_H

// System includes.
#include <string>

const float VERSION = 1.1f;

// Fruit settings.
const int NUM_FISH = 3;
const std::string FISH[NUM_FISH] = {
  "little-fish",
  "small-fish",
  "medium-fish",
};
const int EXPLOSION_AGE = 45;        // in ticks
const float EXPLOSION_SPEED = 0.05f; // in spaces/tick
const float EXPLOSION_ROTATE = 1.0f; // in degrees

// Sound settings.
const int NUM_SPLATS = 6;
const int NUM_SWIPES = 7;
const int NUM_KUDOS = 10;

// Wave settings.
const int NUM_WAVES = NUM_FISH;
const int WAVE_LEN = 250;      // in ticks
const int WAVE_SPAWN = 10;     // in ticks
const float WAVE_SPEED = 0.2f; // in ticks
const float SPEED_INC = 0.1f;  // in spaces/tick
const int SPAWN_INC = -5;     // in ticks

// Point Settings.
const int PLUS_POINT = 15;
const int LITTLE_PLUS_POINT = 10;
const int SMALL_PLUS_POINT = 30;
const int MEDIUM_PLUS_POINT = 50;

const int MINUS_POINT = 25;
const int BONUS_POINT = 50;

const int MEDIUM_SHARK_BAR = 300;//300
const int LARGE_SHARK_BAR = 1000;//1000
const int BOMB_BAR = 1200;
const int DIVER_BAR = 3000;//3000


#endif // GAME_H
