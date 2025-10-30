#include "VoidLayer.h"
#include "AppLayer.h"

#include "Core/Application.h"

#include "Core/Renderer/Renderer.h"

void AppLayer::OnUpdate(float ts)
{
    if (glfwGetKey(Core::Application::Get().GetWindow()->GetHandle(), GLFW_KEY_2) == GLFW_PRESS) {
        TransitionTo<AppLayer>();
    }
}

void AppLayer::OnRender()
{
    glClearColor(0.8f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
