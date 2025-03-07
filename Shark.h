#pragma once
//
// Reticle.h
//

#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"

class Shark : public df::Object {
private:
	bool diver; //if diver is in the game
	bool bomb;

	float old_x;

public:
	Shark();
	~Shark();
	int eventHandler(const df::Event* p_e);

	int step(const df::EventStep* p_e);

	int collide(const df::EventCollision* p_c);
};
