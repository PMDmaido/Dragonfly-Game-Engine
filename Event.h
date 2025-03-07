#pragma once
//
// Event.h
//

#include <string>

namespace df {

    const std::string UNDEFINED_EVENT = "UNDEFINED";

    class Event {
    private:
        std::string m_type;  

    public:
        Event();
        virtual ~Event();

        // Set the event type
        void setType(std::string new_type);

        // Get the event type
        std::string getType() const;
    };

} // end namespace df
