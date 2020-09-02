#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"

namespace gb
{
	class Texture;
	class GAMBIT_GRAPHICS_API TextureManager final : public ISingleton
	{
	public:
		TextureManager();
		~TextureManager();

		bool LoadTexture(const std::string& name, const std::string& filePath);
		void BindTexture(const std::string& name);

	private:
		Hashmap<Unique<Texture>> m_textureMap;
	};
}

CREATE_SINGLETON_ACCESSOR(TextureManager, TextureManager, GAMBIT_GRAPHICS_API);