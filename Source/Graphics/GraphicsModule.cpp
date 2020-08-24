#include "GraphicsModule.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/RHI/RHI.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"

namespace gb
{
	DEFINE_SINGLETON(RHI, RHI, GAMBIT_GRAPHICS_API);
	DEFINE_SINGLETON(Renderer, Renderer, GAMBIT_GRAPHICS_API);
	DEFINE_SINGLETON(ShaderManager, ShaderManager, GAMBIT_GRAPHICS_API);
	DEFINE_SINGLETON(TextureManager, TextureManager, GAMBIT_GRAPHICS_API);

	GraphicsModule::GraphicsModule() :
		m_RHI(nullptr)
	{

	}

	GraphicsModule::~GraphicsModule()
	{
		// assert that ShutDown was called before dtor
	}

	void GraphicsModule::RegisterSingletons()
	{
		IModule::RegisterSingletons();

		REGISTER_SINGLETON(RHI, RHI);
		m_RHI = GetRHI();

		REGISTER_SINGLETON(Renderer, Renderer);
		REGISTER_SINGLETON(ShaderManager, ShaderManager);
		REGISTER_SINGLETON(TextureManager, TextureManager);
	}

	void GraphicsModule::Unload()
	{
		IModule::Unload();

		// destroy managers
		// destroy renderer
		// destroy RHI
	}
}