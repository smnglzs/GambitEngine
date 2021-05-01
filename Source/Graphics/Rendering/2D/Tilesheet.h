#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Common/Color.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/Texture/Texture.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Tilesheet final : public Texture
	{
	public:
		Tilesheet(const Texture* texture, const uint16 tileSize, const vec2f offset = {0.0f, 0.0f});
		~Tilesheet();

		inline const Texture& GetTexture()		 const { return *this; }
		inline uint16		  GetWidthInTiles()	 const { return m_widthInTiles; }
		inline uint16		  GetHeightInTiles() const { return m_heightInTiles; }
		inline uint16		  GetNumTiles()		 const { return m_widthInTiles * m_heightInTiles; }
		inline float		  GetTileSize()		 const { return m_tileSize; }

		inline vec2f GetTexCoords(const uint16 tileX, const uint16 tileY) const 
		{ 
			return { m_tileSize * tileX * ScaleX(), m_tileSize * tileY * ScaleY() };
		}

	private:
		inline float ScaleX() const { return 1.0f / GetWidth();  }
		inline float ScaleY() const { return 1.0f / GetHeight(); }

	private:
		Color	m_tintColor;
		vec2f	m_offset;
		float	m_tileSize;
		uint16	m_widthInTiles;
		uint16	m_heightInTiles;
	};
}

/* TODO:
	- Uniform vs varying sizes, i.e. (no) fixed tile size?

	- Get all coords for tiles of the requested type
	  GetCoordsOfType(name? ID?)

	- Resize on window/RT resize
	  Resize(...)

	- Sparse tilesheet? Different sizes?
	  StringHashmap<ViewportRect> m_tiles;
*/