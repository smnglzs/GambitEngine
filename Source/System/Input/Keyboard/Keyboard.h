#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "System/Export.h"
#include "System/Input/Keyboard/KeyEvent.h"

struct GLFWwindow;
namespace gb
{
	class GAMBIT_SYSTEM_API Keyboard final : public IEventDispatcher<KeyEvent>, public ISingleton
	{
	public:
		Keyboard();
		virtual ~Keyboard() override;

		GB_DEFINE_LISTENER(KeyEvent);
		virtual ListenerId AddEventListener(const uint8 eventCode, EventClassListener&& listener) override;
		virtual void RemoveEventListener(const uint8 eventCode, ListenerId listenerId) override;

	private:
		GB_MULTICASTER(KeyEvent) m_eventCaster;
		virtual void DispatchEvent(const KeyEvent keyEvent) override;

		static void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

		friend class InputManager;
	};
}

GB_CREATE_SINGLETON_ACCESSOR(Keyboard, Keyboard, GAMBIT_SYSTEM_API);
#define gbKeyboard gb::GetKeyboard()
#define gbKeyboardAddListener(EventCode, Target, MethodName) gbKeyboard->AddEventListener((uint8)EventCode, Keyboard::KeyEventListener::CreateRaw(Target, &MethodName))
