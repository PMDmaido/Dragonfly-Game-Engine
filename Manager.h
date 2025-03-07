#pragma once
//
// Manager.h
//

#include <string>
#include "Event.h"

namespace df {

	class Manager {
	private:
		std::string m_type;
		bool m_is_started;

	protected:

		// Set type identifier of Manager.
		void setType(std::string type);

	public:
		Manager();
		virtual ~Manager();

		//Get type identifier of Manager.
		std::string getType() const;

		//Startup Manager.
		//Return of if ok, else negative number.
		virtual int startUp();

		//Shutdown Manager.
		virtual void shutDown();

		//Return true when startUp() was executed ok, else false.
		bool isStarted() const;

		//Send event to all Objects.
		//Return count of number of events sent.
		int onEvent(const Event* p_event);
};



} // end of namespace df