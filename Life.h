#pragma once
//
// Life.h
// 

#include "Event.h"		
#include "ViewObject.h"

#define LIFE_STRING "Life"

class Life : public df::ViewObject {

public:
	Life();
	int eventHandler(const df::Event* p_e) override;
	void loseLife();
	void lose();
	void gainLife();
};