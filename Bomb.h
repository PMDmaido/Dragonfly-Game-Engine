//
// Bomb.h
//

#include "Object.h"

class Bomb : public df::Object {

private:
	void out();

public:
	Bomb();
	~Bomb();
	int eventHandler(const df::Event* p_e);
	int collide(const df::EventCollision* p_e);
};
