//
// Object.cpp
//

#include "Object.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

static int next_id = 0;

namespace df {

	Object::Object() {
		m_id = next_id++;
		m_type = "undefined";
		m_position = Vector(0, 0);
		m_altitude = MAX_ALTITUDE / 2;
		m_solidness = df::Solidness::HARD;
		m_speed = 0;
		m_direction = Vector(0, 0);
		WM.insertObject(this);
	}

	Object::~Object() {
		WM.removeObject(this);
	}

	int df::Object::eventHandler(const Event* p_e) {
		return 0;
	}

	void Object::setId(int new_id) {
		m_id = new_id;
	}

	int Object::getId() const {
		return m_id;
	}

	void Object::setType(std::string new_type) {
		m_type = new_type;
	}

	std::string Object::getType() const {
		return m_type;
	}

	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}

	Vector Object::getPosition() const {
		return m_position;
	}

	int Object::draw() {
		Vector pos = getPosition();
		return m_animation.draw(pos);
	}

	int Object::setAltitude(int new_altitude){
		m_altitude = new_altitude;
		return 0;
	}

	int Object::getAltitude() const {
		return m_altitude;
	}

	// Sets the speed of the object.
	void Object::setSpeed(float new_speed) {
		m_speed = new_speed;
	}

	// Gets the speed of the object.
	float Object::getSpeed() const {
		return m_speed;
	}

	// Sets the direction of the object.
	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}

	// Gets the direction of the object.
	Vector Object::getDirection() const {
		return m_direction;
	}

	// Sets the velocity of the object (direction and speed).
	void Object::setVelocity(Vector new_velocity) {
		m_speed = new_velocity.getMagnitude();
		new_velocity.normalize();
		m_direction = new_velocity;
	}

	// Gets the velocity of the object based on direction and speed.
	Vector Object::getVelocity() const {
		return Vector(m_direction.getX() * m_speed, m_direction.getY() * m_speed);
	}

	// Predicts the object's position based on speed and direction.
	Vector Object::predictPosition() const {
		return m_position + getVelocity();
	}

	bool Object::isSolid() const {
		return m_solidness == HARD || m_solidness == SOFT;
	}

	int Object::setSolidness(Solidness new_solid) {
		m_solidness = new_solid;
		return 0;
	}

	Solidness Object::getSolidness() const {
		return m_solidness;
	}

	int Object::setSprite(std::string sprite_label) {

		Sprite* p_sprite = RM.getSprite(sprite_label);
		if (!p_sprite) return -1;
		m_animation.setSprite(p_sprite);
		setBox(m_animation.getBox());
		return 0;
	}

	void Object::setAnimation(Animation new_animation) {
		m_animation = new_animation;
	}

	Animation Object::getAnimation() const {
		return m_animation;
	}

	void Object::setBox(Box new_box) {	
		m_box = new_box;
	}

	Box Object::getBox() const {
		return m_box;
	}

	
}