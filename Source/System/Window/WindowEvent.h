#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	class Window;
	struct GAMBIT_SYSTEM_API WindowEvent : public Event
	{
		WindowEvent() :
			window(nullptr),
			focused(false)
		{
		}

		enum class Code : uint8
		{
			FocusChanged,
			NeedsRefresh,
			Count
		};

		Window* window;
		bool	focused;
	};
}