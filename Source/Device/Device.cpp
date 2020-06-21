#include "Device.h"

#include "GLFW/glfw3.h"

namespace gb
{
	Device::Device() :
		m_ready(false)
	{

	}

	Device::~Device()
	{

	}

	bool Device::StartUp()
	{
		m_ready = glfwInit() == GLFW_TRUE;
		assert(m_ready && "glfwInit failed!");

		glfwSetErrorCallback(HandleGLFWError);

		return m_ready;
	}

	void Device::ShutDown()
	{
		glfwTerminate();
	}

	void Device::HandleGLFWError(int error, const char* description)
	{
		
	}
}