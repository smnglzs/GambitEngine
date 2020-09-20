#pragma once
#include "Texture.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API TextureAtlas : public Texture
	{
	public:
		virtual ~TextureAtlas() override;

	private:
		// map names to texture regions?
	};
}