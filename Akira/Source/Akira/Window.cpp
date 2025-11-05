#include "Window.h"
#include "Logger.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include <glad/gl.h>

#include <assert.h>

namespace Akira {

	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		m_Handle = glfwCreateWindow(m_Specification.Width, m_Specification.Height,
			m_Specification.Title.c_str(), nullptr, nullptr);

		if (!m_Handle)
		{
			CORE_ERROR("Failed to create GLFW window");
			assert(false);
		}

		//glfwSetWindowUserPointer(m_Handle, this);

		glfwMakeContextCurrent(m_Handle);
		glfwSetWindowUserPointer(m_Handle, &m_Specification);
		gladLoadGL(glfwGetProcAddress);

		glfwSwapInterval(m_Specification.VSync ? 1 : 0);


		         // Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height) {
			WindowSpecification& data = *(WindowSpecification*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window) {
			WindowSpecification& data = *(WindowSpecification*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

        glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowSpecification& data = *(WindowSpecification*)glfwGetWindowUserPointer(window);

            switch(action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:{
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:{
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });


        glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods) {
            WindowSpecification& data = *(WindowSpecification*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:{
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xoffset, double yoffset) {
            WindowSpecification& data = *(WindowSpecification*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.eventCallback(event);
        });



        glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xpos, double ypos) {

			WindowSpecification& data = *(WindowSpecification*)glfwGetWindowUserPointer(window);

            MousedMovedEvent event((float)xpos, (float)ypos);
            data.eventCallback(event);
        });


	}

	void Window::Destroy()
	{
		if (m_Handle)
			glfwDestroyWindow(m_Handle);

		m_Handle = nullptr;
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Handle);
	}

	glm::vec2 Window::GetFramebufferSize()
	{
		int width, height;
		glfwGetFramebufferSize(m_Handle, &width, &height);
		return { width, height };
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_Handle) != 0;
	}

}
