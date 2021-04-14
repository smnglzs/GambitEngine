#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/Texture/Texture.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API TextureManager final : public ISingleton
	{
	public:
		TextureManager();
		~TextureManager();

		void SetRootLoadPath(const std::string& loadPath);
		bool LoadTexture(const std::string& name, const std::string& filePath, const bool flipHorizontally = true);

		const Texture* BindTexture(const std::string& name);

	private:
		StringHashmap<Unique<Texture>> m_textureMap;
		std::string	m_rootLoadPath;
	};
}

GB_CREATE_SINGLETON_ACCESSOR(TextureManager, TextureManager, GAMBIT_GRAPHICS_API);