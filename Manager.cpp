//
// Manager.cpp
//

#include "Manager.h"
#include "ObjectList.h"
#include "WorldManager.h"

namespace df {

	Manager::Manager() {
		m_type = "";
		m_is_started = false;
	}

	Manager::~Manager() {

	}

	void Manager::setType(std::string type) {
		m_type = type;
	}

	std::string Manager::getType() const {
		return m_type;
	}

	int Manager::startUp() {
		if (!m_is_started) {
			m_is_started = true;
			return 0;
		}
		return -1; // Already started
	}

	void Manager::shutDown() {
		m_is_started = false;
	}

	bool Manager::isStarted() const {
		return m_is_started;
	
	}

	int Manager::onEvent(const Event* p_event) {
		int count = 0;

		ObjectList all_objects = WM.getAllObjects();

		for (int i = 0; i < all_objects.getCount(); i++) {

			if (all_objects[i]->eventHandler(p_event)) {
				count++;
			}
		}

		return count;

	}
}







