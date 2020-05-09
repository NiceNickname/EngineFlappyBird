#include "Window.h"
#include "Input/Input.h"
#include <iostream>

namespace Engine
{
	Window::Window()
	{
		Init();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Init()
	{
		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return;
		}


		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
			std::cout << "glew not initialized" << std::endl;

		glEnable(GL_DEPTH_TEST);

		glfwSetKeyCallback(m_Window, Input::KeyCallBack);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glfwSwapInterval(1);

	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}