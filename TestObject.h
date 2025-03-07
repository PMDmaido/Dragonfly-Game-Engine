#pragma once

#include "Object.h"

class TestObject : public df::Object {
private:
    int step_count; 

public:
    TestObject();
    ~TestObject();
    int eventHandler(const df::Event* p_e) override;
};
