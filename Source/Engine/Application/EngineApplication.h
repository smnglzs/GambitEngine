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
		virtual void Start() = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void Render();
		virtual void Present();
		virtual void Stop() = 0;

		virtual bool IsRunning() = 0;
		virtual Window* GetWindow() { return m_window; }

		inline void SetAssetFolder(const std::string& assetFolder) { m_assetFolder = assetFolder; }

	protected:
		Window* m_window;
		std::string m_assetFolder;
	};
}