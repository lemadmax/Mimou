#include "mmpch.h"

#include "OpenGLContext.h"

#include "Mimou/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Mimou {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MM_CORE_ASSERT(status, "Failed to initialize Glad!");

		MM_CORE_INFO("Info:");
		MM_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		MM_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		MM_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
		
	}

	void OpenGLContext::SwapBuffers()
	{

		glfwSwapBuffers(m_WindowHandle);
	}

}