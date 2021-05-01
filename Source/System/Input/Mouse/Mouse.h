#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "System/Export.h"
#include "System/Input/Mouse/MouseEvent.h"

struct GLFWwindow;
namespace gb
{
	class GAMBIT_SYSTEM_API Mouse final : public IEventDispatcher<MouseEvent>, public ISingleton
	{
		friend class InputManager;
	public:
		Mouse();
		virtual ~Mouse() override;

		GB_DEFINE_LISTENER(MouseEvent);
		virtual ListenerId AddEventListener(const uint8 eventCode, MouseEventListener&& listener) override;
		virtual void RemoveEventListener(const uint8 eventCode, ListenerId listenerId) override;

	private:
		GB_MULTICASTER(MouseEvent) m_eventCaster;
		virtual void DispatchEvent(const MouseEvent mouseEvent) override;

		static void OnButtonEvent(GLFWwindow* window, int button, int action, int mods);
		static void OnEnterContentArea(GLFWwindow* window, int entered);
		static void OnMove(GLFWwindow* window, double xpos, double ypos);
	};
}

GB_CREATE_SINGLETON_ACCESSOR(Mouse, Mouse, GAMBIT_SYSTEM_API);
#define gbMouse gb::GetMouse()
#define gbMouseAddListener(EventCode, Target, MethodName) gbMouse->AddEventListener((uint8)EventCode, Mouse::MouseEventListener::CreateRaw(Target, &MethodName))

/* TODO:
	- support different cursor modes (e.g. disabled, hidden..)
	- move GLFWwindow fwd decl to header
*/