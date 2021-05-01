#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Delegate/Delegate.h"
#include "Base/Event/Event.h"

#define GB_DEFINE_LISTENER(EventClass) using EventClass##Listener = Delegate<void, EventClass>;
#define GB_MULTICASTER(EventClass) std::array<MulticastDelegate<EventClass>, (size_t)EventClass::ECode::Count>

namespace gb
{
	template<class EventClass>
	class GAMBIT_BASE_API IEventDispatcher : public NonCopyable
	{
	public:
		IEventDispatcher()			= default;
		virtual ~IEventDispatcher() = default;

		using ListenerId = DelegateHandle;
		GB_DEFINE_LISTENER(EventClass);

		virtual ListenerId AddEventListener(const uint8 eventCode, EventClassListener&& listener) = 0;
		virtual void RemoveEventListener(const uint8 eventCode, ListenerId listenerId) = 0;

	protected:
		virtual void DispatchEvent(const EventClass e) = 0;
	};

	template class IEventDispatcher<struct KeyEvent>;
	template class IEventDispatcher<struct MouseEvent>;
	template class IEventDispatcher<struct WindowEvent>;
	template class IEventDispatcher<struct GamepadEvent>;
}

