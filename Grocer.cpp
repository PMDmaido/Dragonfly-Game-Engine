//
// Grocer.cpp
//

// System includes.
#include <stdlib.h>    // for rand()

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameOver.h"
#include "Grocer.h"
#include "Points.h"
#include <iostream>
#include "Fish.h"
#include "game.h"

Grocer::Grocer() {
    setType(GROCER_STRING);
    setSolidness(df::SPECTRAL);
    m_wave = 1;
    m_wave_end = WAVE_LEN;
    m_wave_speed = WAVE_SPEED; // Starting speed (spaces/tick).
    m_wave_spawn = WAVE_SPAWN; // Starting spawn rate (ticks).
    m_spawn = m_wave_spawn;
}

// Handle event.
// Return 0 if ignored, else 1.
int Grocer::eventHandler(const df::Event* p_e) {

    // Step event.
    if (p_e->getType() == df::STEP_EVENT)
        return step((df::EventStep*)p_e);

    // If get here, have ignored this event.
    return 0;
}

// Handle step event.
int Grocer::step(const df::EventStep* p_e) {

    m_spawn -= 1;
    if (m_spawn < 0) {
        int mod = m_wave + 1 > NUM_FISH ? NUM_FISH : m_wave + 1;

        //std::string selected_fruit = FISH[rand() % NUM_FISH];

        // Weighted random selection
        int r = rand() % 10; // Generates a number between 0-9
        std::string selected_fish;

        if (r < 6) {
            selected_fish = FISH[0]; // 50% chance for "1"
        }
        else if (r < 9) {
            selected_fish = FISH[1]; // 30% chance for "2"
        }
        else {
            selected_fish = FISH[2]; // 20% chance for "3"
        }

        Fish* p_f = new Fish(selected_fish);

        if (!p_f) {
            LM.writeLog("Grocer::step(): Error! Unable to allocate Fish.");
            return 0;
        }

        p_f->start(m_wave_speed);

        m_spawn = m_wave_spawn;
    }
    

    return 1;
}

void Grocer::addTime() {
    m_wave_end += 150; // Add 5s to the current wave. 
}

int Grocer::draw()
{
    return 0;
}


