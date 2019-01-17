#pragma once
#include "AzEventType.hpp"
#include "string/AzString.hpp"


namespace Az{namespace Event{
    #define AZ_EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type; }

    class Event{
            EventType   mEventType;
            String      mName;
        protected:
            Event(EventType type): mEventType(type){}
        public:
            EventType   GetType() const { return mEventType; }
            String      GetName() const { return mName; }
    };

}}