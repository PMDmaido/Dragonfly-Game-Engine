// Object.cpp

// Engine includes
#include "Object.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "LogManager.h"

namespace df {

	int Object::max_id = 0;


	// Construct object. Set default parameters and add to game world (WorldManager).
	Object::Object() {
		m_id = max_id++;			// Assign unique id.
		m_type = "Object"; // Default type
		m_position = Vector(0, 0); // Default position
		m_altitude = 2; // Default altitude
		m_direction = Vector(0, 0); // Default direction 
		m_speed = 0.0f; // Default speed
		m_solidness = HARD; // Default solidness
		//m_no_soft = false; // Default to allowing movement onto SOFT objects
		m_acceleration = Vector(0, 0); // Default acceleration
		m_mass = 1.0f; // Default mass (avoiding division by zero) 
	
		if (WM.insertObject(this) == 0) { // Insert into world.
			LM.writeLog("Object::Object(): Inserted object with ID: %d\n", getId());
		}
		else {
			LM.writeLog("Object::Object(): Failed to insert object with ID %d\n", getId());
		}
	}

	// Destroy object. Remove from game world (WorldManager).
	Object::~Object() {
		WM.removeObject(this);// Remove from world.
	}

	// Set object id.
	void Object::setId(int new_id) {
		m_id = new_id;
	}
	// Get object id.
	int Object::getId() const {
		return m_id;
	}
	// Set object type identifier.
	void Object::setType(std::string new_type) {
		m_type = new_type;
	}
	// Get object type identifier.
	std::string Object::getType() const {
		return m_type;
	}
	// Set object position.
	void Object::setPosition(Vector new_position) {
		m_position = new_position;
	}
	// Get object position.
	Vector Object::getPosition() const {
		return m_position;
	}

	// Handle event(default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int Object::eventHandler(const Event* p_e) {
		/*
				if (p_e->getType() == STEP_EVENT) {
					return 1;
				}
		*/
		return 0; // 
	}

	// Display Manager 
	// Draw all Objects.
	int Object::draw() {
		// // does nothing itself, but can be overridden by derived classes.
		m_position = getPosition();
		return m_animation.draw(m_position);
	};

	// Set altitude of object, with checks for range [0, MAX_ALTITUDE].
	// Return 0 if ok, else -1.
	// MAX_ALTITUDE is currently set to 4.
	int Object::setAltitude(int new_altitude) {
		if (new_altitude < 0 || new_altitude > MAX_ALTITUDE) {
			return -1; // Altitude out of range.
		}
		m_altitude = new_altitude;
		return 0;
	}

	// Get altitude of object.
	int Object::getAltitude() const { 
		return m_altitude; 
	}

	/////
	///// Object extensions to support kinematics
	/////

	// Set speed of object.
	void Object::setSpeed(float new_speed) {
		m_speed = new_speed;
	}

	// Get speed of object.
	float Object::getSpeed() const {
		return m_speed;
	}

	// Set direction of object.
	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}

	// Get direction of object.
	Vector Object::getDirection() const {
		return m_direction;
	}

	// Set direction and speed of object.
	void Object::setVelocity(Vector new_velocity) {
		m_speed = new_velocity.getMagnitude(); // Speed is the magnitude of the velocity.
		m_direction = new_velocity;
		m_direction.normalize(); // Normalize the direction vector. 
	}

	// Get velocity of object based on direction and speed.
	Vector Object::getVelocity() const {
		return m_direction.scale(m_speed); // Velocity = direction * speed.
	}

	// Predict object position based on speed and direction.
	// Return new position.
	Vector Object::predictPosition() const {
		// Add velocity to current position.
		Vector new_pos = m_position + getVelocity(); // New position = current position + velocity.
		
		// Return new position.
		return new_pos;
	}

	bool Object::isSolid() const {
		// True if HARD or SOFT, else false.
		if (m_solidness == HARD || m_solidness == SOFT) {
			return true;
		}
		else {
			return false;
		}
	}

	// Set solidness of object, with checks for consistency.
	// Return 0 if ok, else -1.
	int Object::setSolidness(Solidness new_solid) {
		if (new_solid == HARD || new_solid == SOFT || new_solid == SPECTRAL) {
			m_solidness = new_solid;
			return 0;
		}
		LM.writeLog("Object::setSolidness(): Invalid solidness value\n");  
		return -1; // Invalid solidness value
	}

	// Get solidness of object.
	Solidness Object::getSolidness() const {
		return m_solidness; 
	}

	/////
	///// Support for Newtonian Mechanics Physics.
	/////

	// Set and get acceleration.
	void Object::setAcceleration(Vector new_acceleration) {
		m_acceleration = new_acceleration;
	}
	Vector Object::getAcceleration() const {
		return m_acceleration;
	}
	// Set and get mass.
	void Object::setMass(float new_mass) {
		if (new_mass > 0) {
			m_mass = new_mass;
		}
	}
	float Object::getMass() const {
		return m_mass;
	}

	// Modify velocity based on acceleration.
	void Object::updateVelocity() {
		// v = v + a (update velocity using acceleration)
		Vector new_velocity = getVelocity() + m_acceleration;
		setVelocity(new_velocity);
	}

	// Enable physics-based movement.
	void Object::applyForce(Vector force) {
		// a = F / m (Newton's Second Law)
		// F is the applied force, m is the object mass and a is the acceleration
		if (m_mass > 0) {
			Vector new_acceleration = force.scale(1 / m_mass);
			setAcceleration(new_acceleration);
		}
	}

	/////
	///// Disallow Movement onto Soft Objects . Comment out if wish to disable.
	/////

	// Set 'no soft' setting (true - cannot move onto SOFT Objects).
	// Initialize as true.
/*
	void Object::setNoSoft(bool new_no_soft) {
		m_no_soft = new_no_soft;
	}

	// Get 'no_soft' setting (true - cannot move onto SOFT Objects).
	bool Object::getNoSoft() const {
		return m_no_soft;
	}
*/

	/// Object class extensions to support Sprites

	// Set sprite for this object to animate.
	// Return 0 if ok, else -1.
	int Object::setSprite(std::string sprite_label) {

		Sprite* p_sprite = RM.getSprite(sprite_label);

		// Check if the sprite was found.
		if (p_sprite == nullptr) {
			LM.writeLog("Object::setSprite(): Sprite '%s' not found in ResourceManager.", sprite_label.c_str());
			return -1; // Return error if sprite not found.
		}
		// Set the sprite for the animation.
		m_animation.setSprite(p_sprite);
		// Set the bounding box to match the sprite size.
		setBox(m_animation.getBox());

		return 0;
	}

	// Set Animation for this object to new one.
	// Set bounding box to size of associated Sprite.
	void Object::setAnimation(Animation animation_label) {

		m_animation = animation_label;

		// Get the sprite associated with the new animation.
		const Sprite* p_sprite = m_animation.getSprite();

		// If a sprite is associated, update the object's bounding box.
		//if (p_sprite != nullptr) {
		//	setBox(p_sprite->getBox());
		//}

		// Log the animation update.
		LM.writeLog("Object::setAnimation(): Animation set successfully with sprite '%s'.",
			m_animation.getName().c_str());

	}

	// Get Animation for this object.
	Animation Object::getAnimation() const {
		return m_animation;
	}

	///// Box functions

	// Set Object's bounding Box for this object.
	void Object::setBox(Box new_box) {
		m_box = new_box;
	}

	// Get object's bounding Box.
	Box Object::getBox() const {
		return m_box;
	}


} // end of namespace df	