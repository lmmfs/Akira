# include "OverLayer.h"

#include "Akira/Application.h"
#include "Akira/Logger.h"
#include "Akira/Renderer/Renderer.h"
#include "Akira/Renderer/Shader.h"

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "AppLayer.h"
#include "VoidLayer.h"

OverlayLayer::OverlayLayer()
{
    APP_INFO("Created new OverLayer");

    // Create shaders
	m_Shader = Renderer::CreateGraphicsShader("Shaders/Transform.vert.glsl", "Shaders/Texture.frag.glsl");

	// Create geometry
	glCreateVertexArrays(1, &m_VertexArray);
	glCreateBuffers(1, &m_VertexBuffer);
    glCreateBuffers(1, &m_IndexBuffer);

    struct Vertex
	{
		glm::vec2 Position;
		glm::vec2 TexCoord;
	};

    Vertex vertices[] = {
        { {-0.5f, -0.5f}, {0.0f, 0.0f} }, //Bottom-left
        { { 0.5f, -0.5f}, {1.0f, 0.0f} }, //Bottom-right
        { { 0.5f,  0.5f}, {1.0f, 1.0f} }, //Top-right
        { {-0.5f,  0.5f}, {0.0f, 1.0f} }  //Top-left
    };

    glNamedBufferData(m_VertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    glNamedBufferData(m_IndexBuffer, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind the VBO to VAO at binding index 0
	glVertexArrayVertexBuffer(m_VertexArray, 0, m_VertexBuffer, 0, sizeof(Vertex));
    glVertexArrayElementBuffer(m_VertexArray, m_IndexBuffer);

	// Enable attributes
	glEnableVertexArrayAttrib(m_VertexArray, 0); // position
	glEnableVertexArrayAttrib(m_VertexArray, 1); // uv

    // Format: location, size, type, normalized, relative offset
	glVertexArrayAttribFormat(m_VertexArray, 0, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, Position)));
	glVertexArrayAttribFormat(m_VertexArray, 1, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, TexCoord)));

	// Link attribute locations to binding index 0
	glVertexArrayAttribBinding(m_VertexArray, 0, 0);
	glVertexArrayAttribBinding(m_VertexArray, 1, 0);

    m_Texture = Renderer::LoadTexture("Textures/button.png");
}


OverlayLayer::~OverlayLayer()
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

void OverlayLayer::OnUpdate(float ts)
{

}

void OverlayLayer::OnRender()
{
	glUseProgram(m_Shader);

    glUniform1i(glGetUniformLocation(m_Shader, "ourTexture"), 0);

    // bind texture

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture.Handle);

	// Render
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OverlayLayer::OnEvent(Akira::Event& event)
{

}
