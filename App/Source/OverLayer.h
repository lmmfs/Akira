#pragma once

#include <stdint.h>

#include "Akira/Layer.h"
#include "Akira/Renderer/Renderer.h"
#include "Akira/Events/Event.h"

class OverlayLayer : public Akira::Layer
{
public:
    OverlayLayer();
    virtual ~OverlayLayer();

    virtual void OnUpdate(float ts) override;
    virtual void OnRender() override;
	virtual void OnEvent(Akira::Event& event) override;

private:
	uint32_t m_Shader = 0;
	uint32_t m_VertexArray = 0;
	uint32_t m_VertexBuffer = 0;
    uint32_t m_IndexBuffer = 0;
    Renderer::Texture m_Texture;

    bool m_IsHovered = false;
    bool m_Pressed = true;
};
