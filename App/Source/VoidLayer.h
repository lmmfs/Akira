#pragma once

#include "Akira/Layer.h"

class VoidLayer : public Akira::Layer
{
public:
	VoidLayer();
	virtual ~VoidLayer() = default;

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
};
