#pragma once
#include "Base/GambitBasePCH.h"
#include "Engine/Export.h"

namespace gb
{
	class Window;
	class GAMBIT_ENGINE_API EngineApplication
	{
	public:
		EngineApplication();
		virtual ~EngineApplication();

		virtual void Init() = 0;
		virtual void SetWindow(Window* window) { m_window = window; }
		virtual bool LoadAssets();
		virtual void Start() { m_running = true; }
		virtual void Update(const float deltaTime) { }
		virtual void Render() { };
		virtual void Present();
		virtual void Stop() { m_running = false; }

		virtual bool IsRunning() { return m_running; }
		virtual Window* GetWindow() { return m_window; }

		inline const std::string& GetAssetFolder() const { return m_assetFolder; }
		inline void SetAssetFolder(const std::string& assetFolder) { m_assetFolder = assetFolder; }

	protected:
		std::string m_assetFolder;
		Window*		m_window;
		bool		m_running;
	};
}