//
// EventCollision.h
//

#include "EventCollision.h"

namespace df {
    // Default constructor - initializes with null objects and (0,0) position.
    EventCollision::EventCollision() {
        setType(COLLISION_EVENT);
        m_p_obj1 = nullptr;
        m_p_obj2 = nullptr;
        m_pos = Vector(0, 0);
    }

    // Constructor - initializes with given objects and position.
    EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p) {
        setType(COLLISION_EVENT);
        m_p_obj1 = p_o1;
        m_p_obj2 = p_o2;
        m_pos = p;
    }

    // Set object that caused collision.
    void EventCollision::setObject1(Object* p_new_o1) {
        m_p_obj1 = p_new_o1;
    }

    // Return object that caused collision.
    Object* EventCollision::getObject1() const {
        return m_p_obj1;
    }

    // Set object that was collided with.
    void EventCollision::setObject2(Object* p_new_o2) {
        m_p_obj2 = p_new_o2;
    }

    // Return object that was collided with.
    Object* EventCollision::getObject2() const {
        return m_p_obj2;
    }

    // Set position of collision.
    void EventCollision::setPosition(Vector new_pos) {
        m_pos = new_pos;
    }

    // Return position of collision.
    Vector EventCollision::getPosition() const {
        return m_pos;
    }

}