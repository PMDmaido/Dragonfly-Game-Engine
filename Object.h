#ifndef __OBJECT_H__
#define __OBJECT_H__

// System includes
#include <string>

// Engine includes
#include "Vector.h" 
#include "Event.h" 
#include "Animation.h"
#include "Box.h"

namespace df {    
	const int MAX_ALTITUDE = 4;  // Default maximum altitude. 

	enum Solidness {
		HARD,		/// Object causes collisions and impedes.
		SOFT,		/// Object causes collisions, but doesn't impede.
		SPECTRAL	/// Object doesn't cause collisions.
	};

	class Object {

	public:
		static int max_id;	        /// Monotonically increasing identifier.
		//static const int MAX_ALTITUDE = 4;  // Default maximum altitude. 

	private:
		int m_id; // Unique game engine defined identifier.
		std::string m_type; // Game programmer defined type.
		Vector m_position; // Position in game world.
		int m_altitude; // 0 to MAX_ALTITUDE supported (lower drawn first). 

		Vector m_direction; // Direction vector.
		float m_speed; // Object speed in direction.

		Solidness m_solidness; // Solidness of object. 

		// Support for Newtonian Mechanics Physics.
		Vector m_acceleration; // Acceleration vector.
		float m_mass; // Mass of the object.

		// Support for Disallow Movement onto Soft Objects. Comment out if wish to disable.
		//bool m_no_soft; // True if won’t move onto soft objects.

		Animation m_animation; // Animation for the object.	
		Box m_box; // Box for sprite boundary and collisions.


	public:

		// Construct object. Set default parameters and add to game world (WorldManager).
		Object(); 

		// Destroy object. Remove from game world (WorldManager).
		virtual ~Object();

		// Set object id.
		void setId(int new_id);

		// Get object id.
		int getId() const;

		// Set object type identifier.
		void setType(std::string new_type);

		// Get object type identifier.
		std::string getType() const;

		// Set object position.
		void setPosition(Vector new_position);

		// Get object position.
		Vector getPosition() const;

		virtual int eventHandler(const Event* p_e);

		// Display Manager 
		// Draw all Objects.
		virtual int draw(); 

		// Set altitude of object, with checks for range [0, MAX_ALTITUDE].
		// Return 0 if ok, else -1.
		int setAltitude(int new_altitude);

		// Get altitude of object.
		int getAltitude() const;

		/////
		///// Object extensions to support kinematics
		/////
		
		// Set speed of object.
		void setSpeed(float new_speed);

		// Get speed of object.
		float getSpeed() const;

		// Set direction of object.
		void setDirection(Vector new_direction);

		// Get direction of object.
		Vector getDirection() const;

		// Set direction and speed of object.
		void setVelocity(Vector new_velocity);

		// Get velocity of object based on direction and speed.
		Vector getVelocity() const;

		// Predict object position based on speed and direction.
		// Return predicted position.
		Vector predictPosition() const; // const

		bool isSolid() const; // True if HARD or SOFT, else false. 

		// Set solidness of object, with checks for consistency.
		// Return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);
		 
		// Get solidness of object.
		Solidness getSolidness() const;

		/////
		///// Support for Newtonian Mechanics Physics.
		/////
		
		// Set and get acceleration.
		void setAcceleration(Vector new_acceleration);
		Vector getAcceleration() const;

		// Set and get mass.
		void setMass(float new_mass);
		float getMass() const;

		// Modify velocity based on acceleration.
		void updateVelocity();

		// Enable physics-based movement.
		void applyForce(Vector force);

		/////
		///// Disallow Movement onto Soft Objects . Comment out if wish to disable.
		/////

		// Set 'no soft' setting (true - cannot move onto SOFT Objects).
		// Initialize as true.
		//void setNoSoft(bool new_no_soft = true); 

		// Get 'no_soft' setting (true - cannot move onto SOFT Objects).
		//bool getNoSoft() const;


		///  Object class extensions to support Sprites

		// Set sprite for this object to animate.
		// Return 0 if ok, else -1.
		int setSprite(std::string sprite_label);

		// Set Animation for this object to new one.
		// Set bounding box to size of associated Sprite.
		void setAnimation(Animation animation_label);

		// Get Animation for this object.
		Animation getAnimation() const;

		// Draw Object Animation
		// Return 0 if ok, else -1.
		//virtual int draw(); // Already defined above.

		///// Box functions	

		// Set Object's bounding Box for this object.
		void setBox(Box new_box);

		// Get object's boundding Box.
		Box getBox() const;
	};
} // end of namespace df
#endif // __OBJECT_H__