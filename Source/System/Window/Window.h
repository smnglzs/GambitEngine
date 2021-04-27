#pragma once

#include "Base/GambitBasePCH.h"
#include "Base/Image/Image.h"
#include "System/Export.h"
#include "System/Window/Backend/OpenGL/GLContextSettings.h"
#include "System/Window/WindowEvent.h"
#include "System/Window/WindowSettings.h"

struct GLFWwindow;
namespace gb
{
	class GAMBIT_SYSTEM_API Window : public IEventDispatcher<WindowEvent>
	{
		friend class WindowManager;
	public:
		Window(const WindowSettings& winSettings, const GLContextSettings ctxSettings);
		virtual ~Window();

		void BindContext();
		void UnbindContext();
		void PollEvents();
		void SwapBuffers();
		void GiveFocus();
		void ResetIcon();
		void RequestAttention();
		void ToggleFullscreen();

	#pragma region Event-handling
		GB_DEFINE_LISTENER(WindowEvent);
		virtual ListenerId AddEventListener(const uint8 eventCode, WindowEventListener&& listener) override;
		virtual void RemoveEventListener(const uint8 eventCode, ListenerId listenerId) override;
	#pragma endregion

	#pragma region Getters
		bool ShouldClose()  const;					  
		bool IsDecorated()  const;
		bool IsFocused()	const;
		bool IsMaximized()  const;
		bool IsMinimized()  const;
		bool IsResizable()  const;
		bool IsVisible()	const;

		inline bool		   IsFullscreen() const { return m_isFullscreen; }
		inline float	   GetOpacity()	  const { return m_opacity;		 }
		inline vec2i	   GetSize()	  const { return m_size;		 }
		inline int32	   GetWidth()	  const { return m_size.x;		 }
		inline int32	   GetHeight()    const { return m_size.y;		 }
		inline GLFWwindow* GetWindowPtr() const { return m_windowPtr;	 }
	#pragma endregion

	#pragma region Setters
		void SetAspectRatio(const int32 width, const int32 height);
		void SetFullscreen(const bool fullscreen);
		void SetIcon(const Image& image);
		void SetOpacity(const float opacity);
		void SetPosition(const int32 posX, const int32 posY);
		void SetPosition(const vec2i& position);
		void SetSize(const int32 width, const int32 height);
		void SetSize(const vec2i& size);
		void SetSizeLimits(const int32 minWidth, const int32 minHeight, const int32 maxWidth, const int32 maxHeight);
		void SetSizeLimits(const vec2i& minSize, const vec2i& maxSize);
		void SetTitle(const std::string& title);
	#pragma endregion

	private:
	#pragma region Callbacks
		static void OnSetFocus(GLFWwindow* window, int focused);
		static void OnSetClose(GLFWwindow* window);
		void SetCallbacks();
	#pragma endregion

		GB_MULTICASTER(WindowEvent) m_eventCaster;
		virtual void DispatchEvent(const WindowEvent winEvent) override;

		int32 GetAttrib(int32 glfwAttrib) const;

		static Window* GetGambitPointer(GLFWwindow* window);
	private:
		GLFWwindow* m_windowPtr;
		std::string	m_title;
		vec2i		m_position;
		vec2i		m_size;
		float		m_opacity;
		bool		m_isContextBound;
		bool		m_isFullscreen;
		bool		m_updateViewport;
	};
}

#define gbWindowAddListener(WinPtr, EventCode, Target, MethodName) WinPtr->AddEventListener((uint8)EventCode, Window::WindowEventListener::CreateRaw(Target, &MethodName))
