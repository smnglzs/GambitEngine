#include "GraphicsModule.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/RHI/RHI.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"

namespace gb
{
	DEFINE_SINGLETON(RHI, RHI, GAMBIT_GRAPHICS_API);
	DEFINE_SINGLETON(ShaderManager, ShaderManager, GAMBIT_GRAPHICS_API);
	DEFINE_SINGLETON(TextureManager, TextureManager, GAMBIT_GRAPHICS_API);
	DEFINE_SINGLETON(Renderer, Renderer, GAMBIT_GRAPHICS_API);

	GraphicsModule::GraphicsModule()
	{

	}

	GraphicsModule::~GraphicsModule()
	{
		// assert that Unload was called before dtor
	}

	void GraphicsModule::RegisterSingletons()
	{
		IModule::RegisterSingletons();

		REGISTER_SINGLETON(RHI, RHI);
		REGISTER_SINGLETON(ShaderManager, ShaderManager);
		REGISTER_SINGLETON(TextureManager, TextureManager);
		REGISTER_SINGLETON(Renderer, Renderer);
	}

	void GraphicsModule::Load()
	{
		// Create RHI, Renderer, ShaderManager, and TextureManager
		RegisterSingletons();

		auto& shaderManager  = *GetShaderManager();
		auto& textureManager = *GetTextureManager();

		shaderManager.SetRootLoadPath("D:/Projects/2020/GambitEngine/Assets/Shaders/");

		const bool hasFallbacks = shaderManager.CreateFallbackShaders() && textureManager.CreateFallbackTextures();
		assert(hasFallbacks);

		// GetShaderManager()->CreateShaders(); // TODO: load shader assets from config/manifest
		// GetTextureManager()->Create...
	}

	void GraphicsModule::Unload()
	{
		IModule::Unload();

		// destroy managers
		// destroy renderer
		// destroy RHI
	}
}