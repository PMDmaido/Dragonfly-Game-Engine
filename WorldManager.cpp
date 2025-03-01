// WorldManager.cpp
// Implementation of WorldManager class.

#include "WorldManager.h"
#include "LogManager.h"

namespace df {

    // Constructor.
    WorldManager::WorldManager() { // Private since a singleton.
        setType("WorldManager");
        //m_updates = ObjectList();
        //m_deletions = ObjectList();
        m_boundary = Box(Vector(0, 0), 0, 0); // Initialize world boundary.
        m_view = Box(Vector(0, 0), 0, 0);     // Initialize view boundary.
        m_p_view_following = nullptr;           // Initialize view-following object.
    }

    // Get the one and only instance of the WorldManager.
    WorldManager& WorldManager::getInstance() {
        static WorldManager instance;
        return instance;
    }

    // Startup game world (initialize everything to empty).
    // Return 0 if ok, else -1.
    int WorldManager::startUp() {
        m_updates.clear();
        m_deletions.clear();

        if (m_updates.isEmpty() && m_deletions.isEmpty()) {
            //return 0;
            return Manager::startUp(); // Call parent startUp, return 0 if ok
            LM.writeLog("WorldManager::startUp(): started\n");
        }
        else {
            return -1;
        }
    }

    // Shutdown game world (delete all game world Objects).
    void WorldManager::shutDown() {
        LM.writeLog("WorldManager()::shutDown(): shutting down\n");
        ObjectList list = m_updates;
        for (int i = 0; i < list.getCount(); i++) {
            delete list[i];
        }
        LM.writeLog("WorldManager()::shutDown(): deleted all objects\n");
        // shutDown Manager
        Manager::shutDown(); // Call parent shutDown
    }

    // Insert Object into world. Return 0 if ok, else -1.
    int WorldManager::insertObject(Object* p_o) {
        if (m_updates.insert(p_o) == 0) {          
            return 0; // Success
        }
        else {
            return -1; // Failure
        }
    }

    // Remove Object from world. Return 0 if ok, else -1.
    int WorldManager::removeObject(Object* p_o) {
        return m_updates.remove(p_o); // Remove Object from m_updates list
    }

    // Return list of all Objects in world.
    ObjectList WorldManager::getAllObjects() const {
        return m_updates;
    }

    // Return list of all Objects in world o f matching type.
    // List is empty if none found.
    ObjectList WorldManager::objectsOfType(std::string type) const {
        ObjectList list;
        for (int i = 0; i < m_updates.getCount(); i++) {
            if (m_updates[i]->getType() == type) {
                list.insert(m_updates[i]);
            } // end if
        } // end for
        return list;
    }

    // Indicate Object is to be deleted at end of current game loop.
    // Return 0 if ok, else -1.
    int WorldManager::markForDelete(Object* p_o) {

        // Check if Object is already marked for deletion, so only add once.
        for (int i = 0; i < m_deletions.getCount(); i++) {
            if (m_deletions[i] == p_o) { // Object already in list.
                return 0; // This is still ok.
            } // end if
        } // end for

        // Object not in list, so add.
        LM.writeLog("WorldManager::markForDelete(): Marking object %s (ID %d) for deletion.\n", p_o->getType().c_str(), p_o->getId());
        return m_deletions.insert(p_o);
    }

    // Update world.
    // Update positions of Objects based on their velocities.
    // Delete Objects marked for deletion.
    void WorldManager::update() {
        LM.writeLog("WorldManager::update(): Updating world\n");

        // Iterate over all Objects in m_deletions list and delete each one.
        for (int i = 0; i < m_deletions.getCount(); i++) {
            Object* p_o = m_deletions[i];
            if (p_o != nullptr) {
                LM.writeLog("WorldManager::update(): Deleting object of type %s\n", p_o->getType().c_str());
                //m_deletions.remove(p_o);
                delete p_o;
            }
        }
        // Clear m_deletions list.
        m_deletions.clear();
        
        // Iterate over all Objects in m_updates list 
        // and update each object's positions based on velocities.
        for (int i = 0; i < m_updates.getCount(); i++) {
            Object* p_o = m_updates[i];
            if (p_o != nullptr) {                            
				p_o->updateVelocity(); // Update velocity based on acceleration.
                Vector new_pos = p_o->predictPosition();  //p_o->setPosition(new_position);
                if (p_o->getPosition().getX() != new_pos.getX() || p_o->getPosition().getY() != new_pos.getY()) { // if (new_pos != p_o->getPosition()) 
                    moveObject(p_o, new_pos); 
				}                
            }
        }
      
         
    }

    // Draw all Objects in the world.
    void WorldManager::draw() {
		// Iterate over all Objects in m_updates list and draw each one.
        for (int alt = 0; alt <= MAX_ALTITUDE; alt++) {
            for (int i = 0; i < m_updates.getCount(); i++) {
				Object* p_temp_o = m_updates[i];
                if (m_updates[i]->getAltitude() == alt) {
                    //m_updates[i]->draw(); // Draw Object at current altitude.

                    // Get the object's bounding box in world coordinates.
                    Box temp_box = getWorldBox(p_temp_o);
                    // Check if the object's bounding box intersects with the current view.
                    if (boxIntersectsBox(temp_box, getView()) || dynamic_cast<ViewObject*>(p_temp_o)) {
                        // Draw the object if it is visible in the view.
                        p_temp_o->draw();                       
                    }
                }
            }
        }
    }


	///// WorldManager extensions for collision support

    // Return a list of Objects collided with at position "where".
    // Collisions only with SOLID Objects.
    // Does not consider if p_o is solid or not.
    ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) {
        
        // Make empty list
        ObjectList collision_list;

        // Get world bounding box for object at position 'where'
		Box b = getWorldBox(p_o, where); // Get world box for object at position 'where'

		// Iterate over all Objects in m_updates list and check for collisions.
        for (int i = 0; i < m_updates.getCount(); i++) {
            Object* p_temp_o = m_updates[i];

			if (p_temp_o != p_o) {          // Do not consider self collision
				
/*
                // Same location and both solid?
                if (positionsIntersect(p_temp_o->getPosition(), where)
                    // boxIntersectsBox()
                    && p_temp_o->isSolid()) {
                        collision_list.insert(p_temp_o);// Add p_temp_o to collision_list
                }
*/
                // Get world-aligned bounding box for the other object
                Box b_temp = getWorldBox(p_temp_o);

                // Check if the bounding boxes overlap and the other object is solid
                if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()) {
                    collision_list.insert(p_temp_o);
                }
			} // end if 
              // Not self collision and No solid collisions
		
        } // end for
        return collision_list;
    }

    // Move Object.
        // If collision with solid, send collision events.
        // If no collision with solid, move ok; else don't move Object.
        // If Object is Spectral, move ok.
        // Return 0 if move ok, else -1 if collision with solid.
    int WorldManager::moveObject(Object* p_o, Vector where) { 
        // Get original bounding box before moving
        Box orig_box = getWorldBox(p_o);

		if (p_o->isSolid()) { // Need to be solid for collision

			// Get collisions.
            ObjectList c_list = getCollisions(p_o, where);

			if (!c_list.isEmpty()) { // If there are collisions
                
				bool do_move = true; // Assume can move 

				// Iterate over all Objects in collisions_list and send collision events.
                for (int i = 0; i < c_list.getCount(); i++) {
                    
                    Object *p_temp_o = c_list[i];
                    
					// Create collision event.
                    EventCollision c_event(p_o, p_temp_o, where);
					// Send collision event to both Objects.
                    p_o->eventHandler(&c_event);
                    p_temp_o->eventHandler(&c_event);

					// If both Objects are HARD, then can't move.
                    if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
						do_move = false; // Can't move
					} // end if

                    // Disallow movement onto SOFT objects if no_soft is enabled
                    //if (p_o->getNoSoft() && p_temp_o->getSolidness() == SOFT) {
                    //    do_move = false; 
                    //}

				} // end for
                
				if (!do_move) return -1; // Move not allowed

			} // end if there are collisions
		} // end if Solid

		/*
        * // If here, no collision between two HARD objects, so allowed move.
        Vector old_position = p_o->getPosition();

		p_o->setPosition(where); // Set new position

        // Check if object moved out of bounds
        if (old_position.getX() >= 0 && old_position.getX() < DM.getHorizontal() &&
            old_position.getY() >= 0 && old_position.getY() < DM.getVertical() &&
            (where.getX() < 0 || where.getX() >= DM.getHorizontal() ||
                where.getY() < 0 || where.getY() >= DM.getVertical())) {
			// Generate out of bounds event and send to object
            EventOut out_event;
            p_o->eventHandler(&out_event);
        }
        */

        // Move the object
        p_o->setPosition(where);

        // Get new bounding box after moving
        Box new_box = getWorldBox(p_o);

        // Check if object moved from inside to outside the world boundary
        if (boxIntersectsBox(orig_box, getBoundary()) &&  // Was inside boundary?
            !boxIntersectsBox(new_box, getBoundary())) {  // Now outside boundary?

            // Generate out-of-bounds event and send it to the object
            EventOut out_event;
            p_o->eventHandler(&out_event);
        }
        // If view is following this object, adjust view.
        if (m_p_view_following == p_o) {
            setViewPosition(p_o->getPosition());
        }

		// All is well.
		return 0; // Move was ok

	} // end of moveObject

    /// Boundary extension

    // Set game world boundary.
    void WorldManager::setBoundary(Box new_boundary) {
        m_boundary = new_boundary;
    }

    // Get game world boundary.
    Box WorldManager::getBoundary() const {
        return m_boundary;
    }

    // Set player view of game world.
    void WorldManager::setView(Box new_view) {
        m_view = new_view;
    }

    // Get player view of game world.
    Box WorldManager::getView() const {
        return m_view;
    }

    // Set view to center window on position view_pos.
    // View edge will not go beyond world boundary.
    void WorldManager::setViewPosition(Vector view_pos) {
        // Make sure horizontal not out of world boundary
        float x = view_pos.getX() - m_view.getHorizontal() / 2;
        float y = view_pos.getY() - m_view.getVertical() / 2;

        if (x + m_view.getHorizontal() > m_boundary.getHorizontal()) {
            x = m_boundary.getHorizontal() - m_view.getHorizontal();
        }
        if (x < 0) {
            x = 0;
        }

        if (y + m_view.getVertical() > m_boundary.getVertical()) {
            y = m_boundary.getVertical() - m_view.getVertical();
        }
        if (y < 0) {
            y = 0;
        }
        Vector new_corner(x, y);
        m_view.setCorner(new_corner); 
    }

    // Set view to center window on Object.
    // Set to NULL to stop following.
    // If p_new_view_following is not valid, return -1, else return 0.
    int WorldManager::setViewFollowing(Object* p_new_view_following) {
		// Set to NULL to stop following.
        if (p_new_view_following == nullptr) {
            m_p_view_following = nullptr;
            return 0;
        }

/*
        for (int i = 0; i < m_updates.getCount(); i++) {
            if (m_updates[i] == p_new_view_following) {
                m_p_view_following = p_new_view_following;
                setViewPosition(p_new_view_following->getPosition());
                return 0;
            }
        }*/

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
            m_p_view_following = p_new_view_following;
            setViewPosition(m_p_view_following->getPosition());
            return 0; // Success
        }


        return -1;
    }

} // end of namespace df