//
// Star.h
//

#include "Object.h"

#define STAR_CHAR '@'

class Starfish : public df::Object {

private:
	void out();

public:
	Starfish();
	~Starfish();
	int draw(void);
	int eventHandler(const df::Event* p_e);
	int collide(const df::EventCollision* p_e);
};
