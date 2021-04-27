#include "EngineApplication.h"
#include "System/Window/Window.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"

namespace gb
{
	EngineApplication::EngineApplication() :
		m_window(nullptr),
		m_running(false)
	{

	}

	EngineApplication::~EngineApplication()
	{

	}

	bool EngineApplication::LoadAssets()
	{
		return true;
	}

	void EngineApplication::Present()
	{
		if (m_window)
			m_window->SwapBuffers();
	}
}