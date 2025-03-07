#pragma once
//
// Fish.h
//

// System includes.
#include <string>

// Engine includes.
#include "Event.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "Object.h"

class Fish : public df::Object {

private:
	

	// Handle out events.
	int out(const df::EventOut* p_e);

	// Handle collision events.
	int collide(const df::EventCollision* p_e);

public:

	// Constructor - supply name of Fruit (matches Sprite).
	Fish(std::string name);

	// Destructor - if inside the game world, create explosion.
	~Fish();

	// Handle events.
	int eventHandler(const df::Event* p_e) override;

	// Setup starting conditions.
	void start(float speed);


};

