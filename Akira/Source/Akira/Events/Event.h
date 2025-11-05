#pragma once

#include <string>
#include <functional>

namespace Akira {

	#define BIT(x) (1 << x)

	// The events are made to be blocking meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

    enum class EventType {
        none = 0,
        WindowClose, WindowResize, windowFocus, windowLostFocus, WindowMoved,
        AppTick, AppRender, AppUpdate,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MousedMoved, MouseScrolled
    };

    enum EventCategory {
        none = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

	#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;

        public:
            virtual EventType getEventType() const = 0;
            virtual const char* getName() const = 0;
            virtual int getCategoryFlags() const = 0;
            virtual std::string toString() const { return getName(); }

            inline bool hasCategory(EventCategory catgegory) {
                return getCategoryFlags() & catgegory;
            }

            bool m_Handled = false;
    };

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

        private:
            Event& m_Event;

        public:
            EventDispatcher(Event& event) : m_Event(event) {}

            template<typename T>
            bool dispatch(EventFn<T> func) {
                if (m_Event.getEventType() == T::getStaticType()) {
                    m_Event.m_Handled = func(*(T*)&m_Event);
                    return true;
                }
                return false;
            }

    };

   //By defining this function, you are telling fmt
   //how to convert Event objects to strings.
   inline std::string format_as(const Event& e) {
        return e.toString();
   }

}
