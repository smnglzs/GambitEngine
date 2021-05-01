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
			GLFWwindow* winPtr = window->GetGlfwWindow();

			// Mouse
			glfwSetMouseButtonCallback(winPtr, Mouse::OnButtonEvent);
			glfwSetCursorEnterCallback(winPtr, Mouse::OnEnterContentArea);
			glfwSetCursorPosCallback  (winPtr, Mouse::OnMove);

			// Keyboard
			glfwSetKeyCallback(winPtr, Keyboard::OnKeyEvent);

			// Gamepad
			glfwSetJoystickCallback(Gamepad::OnJoystickConnected);
		}
		else
		{
			// warning/info log: no window to bind to
		}
	}
}

