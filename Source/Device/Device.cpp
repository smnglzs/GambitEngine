#include <iostream>
#include "Device.h"
#include "GLFW/glfw3.h"

namespace gb
{
	Device::Device() :
		m_glfwInitialized(false)
	{

	}

	Device::~Device()
	{

	}

	void Device::StartUp()
	{
		glfwSetErrorCallback(OnGLFWError);

		m_glfwInitialized = glfwInit() == GLFW_TRUE;
		assert(m_glfwInitialized);
	}

	void Device::ShutDown()
	{
		glfwTerminate();
	}

	void Device::OnGLFWError(int error, const char* description)
	{
		printf("[GLFW ERROR]: %s\n", description); // TODO: use logger
	}
}