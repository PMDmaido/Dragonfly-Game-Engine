//
// WorldManager.cpp
//

#include "WorldManager.h"
#include "LogManager.h"
#include "EventCollision.h"
#include "utility.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "ViewObject.h"

namespace df {

    WorldManager::WorldManager() {
    }

    WorldManager& WM {
        static WorldManager instance;
        return instance;
    }

    int WorldManager::startUp() {
        m_updates.clear();   // Initialize empty object list.
        m_deletions.clear(); // Initialize empty deletions list.
        return Manager::startUp();
    }

    void WorldManager::shutDown() {

        ObjectList list = m_updates;
        for (int i = 0; i < list.getCount(); i++) {
            delete list[i];
        }
        m_updates.clear();
        m_deletions.clear();
        Manager::shutDown();
    }

    int WorldManager::insertObject(Object* p_o) {
        if (!p_o)
            return -1; // Null object

        return m_updates.insert(p_o);
    }

    int WorldManager::removeObject(Object* p_o) {
        if (!p_o)
            return -1; // Null object

        return m_updates.remove(p_o);
    }

    ObjectList WorldManager::getAllObjects() const {
        return m_updates;
    }

    // Get all objects of a specific type.
    ObjectList WorldManager::objectsOfType(std::string type) {
        ObjectList result;
        for (int i = 0; i < m_updates.getCount(); i++) {
            if (m_updates[i]->getType() == type) {
                result.insert(m_updates[i]);
            }
        }
        return result;
    }

    void WorldManager::update() {

        // Remove and delete all marked objects.
        for (int i = 0; i < m_deletions.getCount(); i++) {
            Object* obj = m_deletions[i];
            delete obj;
        }
        m_deletions.clear(); // Clear deletion list.

        // Move objects
        for (int i = 0; i < m_updates.getCount(); i++) {
            // Add new velocity to  position.
            Vector new_pos = m_updates[i]->predictPosition();

            if (new_pos.getX() != m_updates[i]->getPosition().getX() ||
                new_pos.getY() != m_updates[i]->getPosition().getY()) {
                moveObject(m_updates[i], new_pos);

            }
        }
    }

    int WorldManager::markForDelete(Object* p_o) {
        // Check if the object is already in the deletion list
        for (int i = 0; i < m_deletions.getCount(); i++) {
            if (m_deletions[i] == p_o) {
                return 0;  // Object already marked for deletion
            }
        }

        // Object not in list, so add
        if (m_deletions.insert(p_o) == 0) {
            return 0;  // Successfully added to deletion list
        }

        return -1;  // Failed to add object
    }

    void WorldManager::draw() {

        for (int alt = 0; alt < MAX_ALTITUDE; alt++) {
            // Iterate through all objects in m_updates
            for (int i = 0; i < m_updates.getCount(); i++) {
                Object* p_temp_o = m_updates[i];

                // Draw only objects that match the current altitude
                if (p_temp_o->getAltitude() == alt + 1) {

                    // Get the object's world position bounding box.
                    Box temp_box = getWorldBox(p_temp_o, p_temp_o->getPosition());

                    // Only draw if the object would be visible on the screen (intersects view).
                    if (boxIntersectsBox(temp_box, view) || dynamic_cast<ViewObject*>(p_temp_o)) {
                        p_temp_o->draw();
                        //LM.writeLog("p_temp_o type: %s", (p_temp_o->getType()).c_str());
                    }
                }
            }
        }
    }

    // Return list of Objects collided with at position 'where'.
    // Only considers solid Objects.
    ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) {

        ObjectList collisions;

        // Get world position bounding box for the object at 'where'
        Box b = getWorldBox(p_o, where);

        // Iterate through all objects in the world.
        for (int i = 0; i < m_updates.getCount(); i++) {
            Object* p_temp_o = m_updates[i];

            // Don't check collision with itself.
            if (!(p_temp_o == p_o)) {

                // Get world position bounding box for the other object.
                Box b_temp = getWorldBox(p_temp_o);

                // Check for bounding box intersection and if the other object is solid.
                if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()) {
                    collisions.insert(p_temp_o);
                }
            }

            
        }
        return collisions;
    }

    // Move an Object to a new position.
    int WorldManager::moveObject(Object* p_o, Vector where) {

        // Get original bounding box before moving.
        Box orig_box = getWorldBox(p_o);

        if (p_o->isSolid()) {
            ObjectList collisions = getCollisions(p_o, where);

            if (!collisions.isEmpty()) {
                bool do_move = true;

                for (int i = 0; i < collisions.getCount(); i++) {

                    Object* p_temp_o = collisions[i];

                    // Create a collision event.
                    EventCollision c(p_o, p_temp_o, where);
                    p_o->eventHandler(&c);
                    p_temp_o->eventHandler(&c);

                    // If both HARD, then cannot move
                    if (p_temp_o->getSolidness() == Solidness::HARD && p_o->getSolidness() == Solidness::HARD) {
                        do_move = false;
                    }
                }

                // Move not allowed
                if (!do_move) {
                    return -1;
                }
            }
        }


        p_o->setPosition(where);

        Box new_box = getWorldBox(p_o, where);
        
        if (boxIntersectsBox(orig_box, boundary) && !boxIntersectsBox(new_box, boundary)) {
            // Create and send an EventOut.
            EventOut out_event;
            p_o->eventHandler(&out_event);
        }

        // If view is following this object, adjust view.
        if (p_view_following == p_o) {
            setViewPosition(p_o->getPosition());
        }

        return 0;
    }

    void WorldManager::setBoundary(Box new_boundary) {
        boundary = new_boundary;
    }

    Box WorldManager::getBoundary() const { 
        return boundary;
    }

    void WorldManager::setView(Box new_view) {
        view = new_view;
    }

    Box WorldManager::getView() const {
        return view;
    }

    void WorldManager::setViewPosition(Vector view_pos) {

        // Ensure the view does not go beyond the world boundary horizontally
        float x = view_pos.getX() - view.getHorizontal() / 2;
        if (x + view.getHorizontal() > boundary.getHorizontal()) {
            x = boundary.getHorizontal() - view.getHorizontal();
        }
        if (x < 0) {
            x = 0;
        }

        // Ensure the view does not go beyond the world boundary vertically
        float y = view_pos.getY() - view.getVertical() / 2;
        if (y + view.getVertical() > boundary.getVertical()) {
            y = boundary.getVertical() - view.getVertical();
        }
        if (y < 0) {
            y = 0;
        }

        // Set the new view position
        Vector new_corner(x, y);
        view.setCorner(new_corner);
    }

    int WorldManager::setViewFollowing(Object* p_new_view_following) {
        // Set to NULL to turn 'off' following.
        if (p_new_view_following == nullptr) {
            p_view_following = nullptr;
            return 0; // Success
        }

        // Check if the object exists in the world.
        bool found = false;
        for (int i = 0; i < m_updates.getCount(); i++) {
            if (m_updates[i] == p_new_view_following) {
                found = true;
                break;
            }
        }

        // If found, adjust attribute and set view position.
        if (found) {
            p_view_following = p_new_view_following;
            setViewPosition(p_view_following->getPosition());
            return 0; // Success
        }

        return -1; // Error: Object not found
    }



} // namespace df
