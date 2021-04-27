#include "InputManager.h"
#include "GLFW/glfw3.h"

namespace gb
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{
		
	}

	void InputManager::Init(const Window* window)
	{
		if (window)
		{
			GLFWwindow* winPtr = window->GetWindowPtr();

			// Mouse callbacks
			glfwSetMouseButtonCallback(winPtr, Mouse::OnButtonEvent);
			glfwSetCursorEnterCallback(winPtr, Mouse::OnEnterContentArea);
			glfwSetCursorPosCallback(  winPtr, Mouse::OnMove);

			// Keyboard callbacks
			glfwSetKeyCallback(winPtr, Keyboard::OnKeyEvent);
		}
		else
		{
			// warning/info log: no window to bind to
		}
	}
}

