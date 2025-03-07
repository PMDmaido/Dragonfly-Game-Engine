//
// WorldManager.h
//

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"
#include <string>

#define WM df::WorldManager::getInstance()

namespace df {

    const int MAX_ALTITUDE = 4;

    class WorldManager : public Manager {
    private:
      
        WorldManager();
        WorldManager(WorldManager const&);
        void operator=(WorldManager const&);
        ObjectList m_updates;           // List of all game objects.
        ObjectList m_deletions;         // List of objects marked for deletion.
        Box boundary;                   // World boundary.
        Box view;                       // Player view of game world.
        Object* p_view_following;       // Object view is following.

    public:
        // Get the singleton instance.
        static WorldManager& getInstance();

        // Start up the WorldManager (initialize everything). Return 0 if ok.
        int startUp() override;

        // Shut down the WorldManager (delete all objects).
        void shutDown() override;

        // Add Object to world. Return 0 if ok, else -1.
        int insertObject(Object* p_o);

        // Remove Object from world. Return 0 if ok, else -1.
        int removeObject(Object* p_o);

        // Return list of all Objects in the world.
        ObjectList getAllObjects() const;

        // Return list of Objects matching a given type.
        ObjectList objectsOfType(std::string type);

        // Update the world (process deletions).
        void update();

        // Mark an Object for deferred deletion. Return 0 if ok, else -1.
        int markForDelete(Object* p_o);

        void draw();

        // Return list of Objects collided with at position 'where'.
        // Collisions only with solid Objects.
        // Does not consider if 'p_o' is solid or not.
        ObjectList getCollisions(const Object* p_o, Vector where);

        // Move Object.
        // If collision with solid, send collision events.
        // If no collision with solid, move ok else don’t move Object.
        // If Object is Spectral, move ok.
        // Return 0 if move ok, else -1 if collision with solid.
        int moveObject(Object* p_o, Vector where);

        // Set the game world boundary.
        void setBoundary(Box new_boundary);

        // Get game world boundary.
        Box getBoundary() const;

        // Set player view of game world.
        void setView(Box new_view);

        // Get player view of game world.
        Box getView() const;

        // Set view to center window on position view_pos.
        // View edge will not go beyond world boundary.
        void setViewPosition(Vector view_pos);

        // Set view to center window on Object.
        // Set to NULL to stop following.
        // If p_new_view_following not legit, return -1 , else return 0.
        int setViewFollowing(Object* p_new_following);



    };

} // end of namespace df

#endif // __WORLD_MANAGER_H__
