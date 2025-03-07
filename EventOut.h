#pragma once
//
// EventOut.h
//

#include <string>
#include "Event.h"

namespace df {
	
	const std::string OUT_EVENT = "df::out";
	class EventOut : public Event {
	public:
		EventOut();
	};
}
