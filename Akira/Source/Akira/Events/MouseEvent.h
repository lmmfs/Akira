#pragma once

#include "Event.h"
#include <sstream>

/*
Events:
MousedMovedEvent
MouseButtonPressedEvent
MouseButtonReleasedEvent
MouseScrolledEvent
*/

namespace Akira
{

    class MousedMovedEvent : public Event
    {
        private:
            float m_Xpos;
            float m_Ypos;

        public:
            MousedMovedEvent(float xpos, float ypos) : m_Xpos(xpos), m_Ypos(ypos) {}

            float getX() const { return m_Xpos; }
            float getY() const { return m_Ypos; }

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MousedMovedEvent: " << m_Xpos << ", " << m_Ypos;
                return ss.str();
            }

		EVENT_CLASS_TYPE(MousedMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)
    };

        class MouseButtonEvent : public Event {
        protected:
            int m_ButtonCode;

            MouseButtonEvent(int buttoncode) : m_ButtonCode(buttoncode) {}

        public:
            int getButtonCode() const { return m_ButtonCode; }

            EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
        private:
            int m_ButtonCode;

        public:
            MouseButtonPressedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_ButtonCode;
                return ss.str();
		    }

            EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
        private:
            int m_ButtonCode;

        public:
            MouseButtonReleasedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
                return ss.str();
		    }

            EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class MouseScrolledEvent : public Event
    {
        private:
            float m_XOffset;
            float m_YOffset;

        public:
            MouseScrolledEvent(float xoffset, float yoffset) : m_XOffset(xoffset), m_YOffset(yoffset) {}

            float getX() const { return m_XOffset; }
            float getY() const { return m_YOffset; }

            std::string toString() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseScrolled)
		    EVENT_CLASS_CATEGORY(EventCategoryMouse)
    };

}
