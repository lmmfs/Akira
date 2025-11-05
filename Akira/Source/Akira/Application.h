#pragma once

#include "Layer.h"
#include "Window.h"
#include "Events/Event.h"

#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <functional>

namespace Akira {

	struct ApplicationSpecification
	{
		std::string Name = "Application";
		WindowSpecification WindowSpec;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification = ApplicationSpecification());
		~Application();

		void Run();
		void Stop();
		void onEvent(Event& event);

		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer()
		{
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}

		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		TLayer* GetLayer()
		{
			for (const auto& layer : m_LayerStack)
			{
				if (auto casted = dynamic_cast<TLayer*>(layer.get()))
				{
					return casted;
				}
			}
			return nullptr;
		}

		glm::vec2 GetFramebufferSize() const;

		std::shared_ptr<Window> GetWindow() const { return m_Window; }

		static Application& Get();
		static float GetTime();
	private:
		ApplicationSpecification m_Specification;
		std::shared_ptr<Window> m_Window;
		bool m_Running = false;
		std::vector<std::unique_ptr<Layer>> m_LayerStack;
		// comand queue to execute commands before layer update and draw
		// std::queue<std::function<void()>> m_CommandQueue;
		// use move only function is c++ 23
		// std::unique_ptr<Layer>, is move-only and not copyable.
		std::queue<std::move_only_function<void()>> m_CommandQueue;

		friend class Layer;
	};

}
