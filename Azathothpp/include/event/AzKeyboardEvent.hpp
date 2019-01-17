#include "AzEvent.hpp"



namespace Az{
    namespace Event{
       class KeyboardEvent : public Event{
            public:
                KeyboardEvent() : Event(EventType::KeyboardEvent){}       
                AZ_EVENT_TYPE(KeyboardEvent)
       };
    }
}