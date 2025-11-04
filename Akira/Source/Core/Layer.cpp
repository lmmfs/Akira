#include "Layer.h"

#include "Application.h"
#include <iostream>

namespace Core {

    void Layer::QueueTransition(std::unique_ptr<Layer> toLayer)
    {
        auto& commandQueue = Application::Get().m_CommandQueue;
        auto& layerStack = Application::Get().m_LayerStack;
        size_t index = 0;
        for (; index < layerStack.size(); ++index) {
            if (layerStack[index].get() == this) break;
        }
        commandQueue.push([index, toLayer = std::move(toLayer)]() mutable {
            auto& stack = Application::Get().m_LayerStack;
            if (index < stack.size()) {
                stack[index] = std::move(toLayer);
            }
        });
    }

}
