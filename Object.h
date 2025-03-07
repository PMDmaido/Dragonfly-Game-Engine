#pragma once
//
// Object.h
//

#include "Vector.h"
#include <string>
#include "Event.h"
#include "Animation.h"
#include "Box.h"


namespace df {

	enum Solidness {
		HARD,		// Object causes collisions and impedes.
		SOFT,		// Object causes collisions, but doesn't impede.
		SPECTRAL,	// Object doesn't cause collisions. 
	};

	class Object {



	private:
		int m_id;					// Unique game engine defined identifier.
		std::string m_type;			// Game programmer defined type.
		Vector m_position;			// Position in game world.
		int m_altitude;				// 0 to MAX supported (lower drawn first).
		Vector m_direction;			// Direction vector.
		float m_speed;				// Object speed  in direction.
		Solidness m_solidness;		// Solidness of object. 
		Animation m_animation;		// Animation associated with Objects.
		Box m_box;					// Box for sprite  boundary & collisions.

	public:

		// Construct Object. Set default parameters and
		// add to game world (WorldManager).
		Object();

		// Destroy Object.
		// REmove from game world (WorldManager).
		virtual ~Object();

		// Handle event(default is to ignore everything).
		// Return 0 if ignored, else 1 if handled.
		virtual int eventHandler(const Event* p_e);

		// Set Object id.
		void setId(int new_id);

		// Get Object id.
		int getId() const;

		// Set type identifier of Object.
		void setType(std::string new_type);

		// Get type identifier of Object.
		std::string getType() const;

		// Set position of Object.
		void setPosition(Vector new_pos);

		// Get position of Ojbect.
		Vector getPosition() const;

		// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
		// Return 0 is ok, else -1.
		int setAltitude(int new_altitude);

		// Return altitude of Object.
		int getAltitude() const;

		// Sets the speed of the object.
		void setSpeed(float new_speed);

		// Gets the speed of the object.
		float getSpeed() const;

		// Sets the direction of the object.
		void setDirection(Vector new_direction);

		// Gets the direction of the object.
		Vector getDirection() const;

		// Sets the velocity of the object (both direction and speed).
		void setVelocity(Vector new_velocity);

		// Gets the velocity of the object based on direction and speed.
		Vector getVelocity() const;

		// Predicts the object's position based on speed and direction.
		// Returns the predicted position.
		Vector predictPosition() const;

		// True if HARD or SOFT, else false.
		bool isSolid() const; 

		// Set object colidness, with checks for consistency.
		// Return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);

		// Return object soliness.
		Solidness getSolidness() const;

		// Set Sprite for this Objects to animate.
		// Return 0 if ok, else -1.
		int setSprite(std::string sprite_label);

		// Set Animation for this Object to new one.
		// Set bouding box to size of associated Sprite.
		void setAnimation(Animation new_animation);

		// Get Animation for this Object.
		Animation getAnimation() const;

		// Draw Object Animation.
		// Return 0 if ok, else -1.
		virtual int draw();

		// Set Object's bounding box.
		void setBox(Box new_box);

		// Get Object's bounding box.
		Box getBox() const;
	};

}