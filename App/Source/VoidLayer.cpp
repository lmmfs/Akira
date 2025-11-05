#include "VoidLayer.h"
#include "AppLayer.h"

#include "Akira/Application.h"
#include "Akira/Logger.h"

#include "Akira/Renderer/Renderer.h"
#include "Akira/Events/KeyEvent.h"

VoidLayer::VoidLayer()
{
    // Initialization logic for VoidLayer can go here
}

void VoidLayer::OnUpdate(float ts)
{
}

void VoidLayer::OnRender()
{
    glClearColor(0.8f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void VoidLayer::OnEvent(Akira::Event& event)
{
	Akira::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Akira::KeyPressedEvent>([this](Akira::KeyPressedEvent& event)
    {
		switch (event.getKeyCode()) {
			case GLFW_KEY_2 :
				APP_INFO("Transition to app layer");
				TransitionTo<AppLayer>();
				break;
			default:
				APP_INFO("Key pressed: {0}", event.getKeyCode());
				break;
		}
        return true;
    });
}
