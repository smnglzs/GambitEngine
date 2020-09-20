#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"
#include "Graphics/GraphicsModule.h"

namespace gb
{
	class Texture;
	class GAMBIT_GRAPHICS_API TextureManager final : public ISingleton
	{
	public:
		TextureManager();
		~TextureManager();

		bool LoadTexture(const std::string& name, const std::string& filePath, const bool flipHorizontally);
		void BindFallbackTexture();
		void BindTexture(const std::string& name);

	private:
		friend void GraphicsModule::Load();
		bool CreateFallbackTextures();

		StringHashmap<Unique<Texture>> m_textureMap;
	};
}

CREATE_SINGLETON_ACCESSOR(TextureManager, TextureManager, GAMBIT_GRAPHICS_API);