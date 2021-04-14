#include "GraphicsModule.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "System/Window/WindowManager.h"
#include "Graphics/GHI/GHI.h"
#include "Graphics/GHI/Buffer/VertexArrayManager.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"
#include "Graphics/Rendering/2D/Renderer2D.h"

namespace gb
{
	DEFINE_SINGLETON(ShaderManager,		 ShaderManager,		  GAMBIT_GRAPHICS_API)
	DEFINE_SINGLETON(TextureManager,	 TextureManager,	  GAMBIT_GRAPHICS_API)
	DEFINE_SINGLETON(VertexArrayManager, VertexArrayManager,  GAMBIT_GRAPHICS_API)
	DEFINE_SINGLETON(Renderer2D,		 Renderer2D,		  GAMBIT_GRAPHICS_API);

	GraphicsModule::GraphicsModule()
	{

	}

	GraphicsModule::~GraphicsModule()
	{
		// assert in ~IModule that we are unloaded
	}

	void GraphicsModule::RegisterSingletons()
	{
		REGISTER_SINGLETON(ShaderManager,	   ShaderManager)
		REGISTER_SINGLETON(TextureManager,	   TextureManager)
		REGISTER_SINGLETON(VertexArrayManager, VertexArrayManager)
		REGISTER_SINGLETON(Renderer2D,		   Renderer2D);
	}

	void GraphicsModule::Load()
	{
		IModule::Load();

		// load default assets
	}

	void GraphicsModule::Init()
	{
		//GetWindowManager()->Create

		if (!GHI::Init())
		{
			LOG(gb::EChannelComponent::EngineError, "Init failed!");
			assert(false);
		}

		// We can now destroy our transient (function-loading) context.
		GetWindowManager()->DestroyTransientWindow();
	}

	void GraphicsModule::Unload()
	{
		IModule::Unload();

		// tear down GHI
	}
}