#include "halpch.h"
#include "engine/Core.h"
#include "OpenGLContext.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Haleng {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		HALENG_ASSERT(m_Window, "GLFWwindow is null.");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HALENG_ASSERT(status, "Glad Failed to Iniatialize.");
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}
