#include "VoidLayer.h"
#include "AppLayer.h"

#include "Akira/Application.h"
#include "Akira/Logger.h"

#include "Akira/Renderer/Renderer.h"

VoidLayer::VoidLayer()
{
    // Initialization logic for VoidLayer can go here
}

void VoidLayer::OnUpdate(float ts)
{
    if (glfwGetKey(Akira::Application::Get().GetWindow()->GetHandle(), GLFW_KEY_2) == GLFW_PRESS) {
        APP_INFO("Transition to app layer");
        TransitionTo<AppLayer>();
    }
}

void VoidLayer::OnRender()
{
    glClearColor(0.8f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
