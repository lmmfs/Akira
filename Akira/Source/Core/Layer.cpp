#include "Layer.h"

#include "Application.h"

namespace Core {

    void Layer::QueueTransition(std::unique_ptr<Layer> toLayer)
    {
        // TODO: fix this
        auto& layerStack = Application::Get().m_LayerStack;

        for (auto& layer : layerStack)
        {
            if (layer.get() == this)
            {
                layer = std::move(toLayer);
                return;
            }
        }

    }

}
