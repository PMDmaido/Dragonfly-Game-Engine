#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <string>
#include "Event.h" 

namespace df {

	class Manager {

	private:
		std::string m_type; // Manager type identifier .
		bool m_is_started; // True when stared successfully.

	protected:
		// Set type identifier of Manager.
		void setType(std::string new_type);

	public:
		Manager();
		virtual ~Manager();

		// Return type identifier of Manager.
		std::string getType() const;

		// Start up Manager.
		// Return 0 if ok, else -1.
		virtual int startUp();

		// Shut down Manager.
		virtual void shutDown();

		// Return true when startUp() was executed ok, else false.
		bool isStarted() const;

		int onEvent(const Event* p_event) const;
	};
} // end of namespace df
#endif // __MANAGER_H__
