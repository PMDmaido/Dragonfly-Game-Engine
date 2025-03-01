#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "Object.h"

class TestObject : public df::Object {

public:
	TestObject();
	~TestObject();
	int eventHandler(const df::Event* p_e);
	int draw() override;
};

#endif