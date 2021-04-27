#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "System/Export.h"
#include "System/Input/Keyboard/Keyboard.h"
#include "System/Input/Mouse/Mouse.h"
#include "System/Window/Window.h"

namespace gb
{
	class GAMBIT_SYSTEM_API InputManager final : public ISingleton
	{
	public:
		InputManager();
		~InputManager();

		static void Init(const Window* window);
	};
}

GB_CREATE_SINGLETON_ACCESSOR(InputManager, InputManager, GAMBIT_SYSTEM_API);
#define gbInput gb::GetInputManager()