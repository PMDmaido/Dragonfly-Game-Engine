#include "Manager.h"
#include "LogManager.h"
#include "Event.h"
#include "WorldManager.h"


//df::DisplayManager display_manager;
//df::LogManager log_manager;

//df::LogManager& log_manager = df::LogManager::getInstance();

namespace df {

	Manager::Manager() : m_type("Manager"), m_is_started(false) {
	}

	Manager::~Manager() {
		// If manager is still started when destroyed, call shutDown
		if (m_is_started) {
			shutDown();
		}
	}

	void Manager::setType(std::string new_type) {
		m_type = new_type;
	}

	std::string Manager::getType() const {
		return m_type;
	}

	int Manager::startUp() {
		m_is_started = true;
		return 0; // startUp successful	
	}

	void Manager::shutDown() {
		m_is_started = false;
	}

	bool Manager::isStarted() const {
		return m_is_started;
	}
	
	int Manager::onEvent(const Event* p_event) const {
		int count = 0;

		ObjectList all_objects = WM.getAllObjects();

		for (int i = 0; i < all_objects.getCount(); i++) {
			all_objects[i]->eventHandler(p_event);
			count++;
		}// end for

		return count;
	}
	
} // end of namespace df