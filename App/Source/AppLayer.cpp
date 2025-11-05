#include "AppLayer.h"
#include "Akira/Events/MouseEvent.h"
#include "VoidLayer.h"

#include "Akira/Application.h"
#include "Akira/Logger.h"

#include "Akira/Renderer/Renderer.h"
#include "Akira/Renderer/Shader.h"
#include "Akira/Events/Event.h"
#include "Akira/Events/KeyEvent.h"

#include <glm/glm.hpp>



AppLayer::AppLayer()
{
	APP_INFO("Starting app layer");

	// Create shaders
	m_Shader = Renderer::CreateGraphicsShader("Shaders/Vertex.glsl", "Shaders/Fragment.glsl");

	// Create geometry
	glCreateVertexArrays(1, &m_VertexArray);
	glCreateBuffers(1, &m_VertexBuffer);

	struct Vertex
	{
		glm::vec2 Position;
		glm::vec2 TexCoord;
	};

	Vertex vertices[] = {
		{ {-1.0f, -1.0f }, { 0.0f, 0.0f } },  // Bottom-left
		{ { 3.0f, -1.0f }, { 2.0f, 0.0f } },  // Bottom-right
		{ {-1.0f,  3.0f }, { 0.0f, 2.0f } }   // Top-left
	};

	glNamedBufferData(m_VertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the VBO to VAO at binding index 0
	glVertexArrayVertexBuffer(m_VertexArray, 0, m_VertexBuffer, 0, sizeof(Vertex));

	// Enable attributes
	glEnableVertexArrayAttrib(m_VertexArray, 0); // position
	glEnableVertexArrayAttrib(m_VertexArray, 1); // uv

	// Format: location, size, type, normalized, relative offset
	glVertexArrayAttribFormat(m_VertexArray, 0, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, Position)));
	glVertexArrayAttribFormat(m_VertexArray, 1, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, TexCoord)));

	// Link attribute locations to binding index 0
	glVertexArrayAttribBinding(m_VertexArray, 0, 0);
	glVertexArrayAttribBinding(m_VertexArray, 1, 0);
}

AppLayer::~AppLayer()
{
	if (m_VertexArray != 0)
	{
		glDeleteVertexArrays(1, &m_VertexArray);
		m_VertexArray = 0;
	}

	if (m_VertexBuffer != 0)
	{
		glDeleteBuffers(1, &m_VertexBuffer);
		m_VertexBuffer = 0;
	}

	if (m_Shader != 0)
	{
		glDeleteProgram(m_Shader);
		m_Shader = 0;
	}
}

void AppLayer::OnUpdate(float ts)
{

}

void AppLayer::OnRender()
{
	glUseProgram(m_Shader);

	// Uniforms
	glUniform1f(0, Akira::Application::GetTime());

	glm::vec2 framebufferSize = Akira::Application::Get().GetFramebufferSize();
	glUniform2f(1, framebufferSize.x, framebufferSize.y);

	glViewport(0, 0, static_cast<GLsizei>(framebufferSize.x), static_cast<GLsizei>(framebufferSize.y));

	// Render
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(m_VertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void AppLayer::OnEvent(Akira::Event& event)
{
	Akira::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Akira::KeyPressedEvent>([this](Akira::KeyPressedEvent& event)
    {
		switch (event.getKeyCode()) {
			case GLFW_KEY_1 :
				APP_INFO("Transition to void layer");
				TransitionTo<VoidLayer>();
				break;
			default:
				APP_INFO("Key pressed: {0}", event.getKeyCode());
				break;
		}
        return true;
    });
	dispatcher.dispatch<Akira::MousedMovedEvent>([this](Akira::MousedMovedEvent& event)
	{
		return true;
	});
}
