#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"

namespace gb
{
	class Tilesheet;
	class GAMBIT_GRAPHICS_API Tilemap final
	{
	public:
		Tilemap(const uint16 widthInTiles, const uint16 heightInTiles, const std::vector<uint16>& mapData, Tilesheet& tilesheet);
		~Tilemap();

		inline const Tilesheet& GetTilesheet()	   const { return m_tilesheet;	   }
		inline uint16		    GetWidthInTiles()  const { return m_widthInTiles;  }
		inline uint16			GetHeightInTiles() const { return m_heightInTiles; }

	private:
		std::vector<uint16>	m_mapData;
		Tilesheet&			m_tilesheet;
		uint16				m_widthInTiles;
		uint16				m_heightInTiles;
	};
}

/* TODO:
	
*/