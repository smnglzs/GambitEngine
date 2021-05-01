#include "Tilemap.h"
#include "Graphics/Rendering/2D/Tilesheet.h"

namespace gb
{
	Tilemap::Tilemap(const uint16 widthInTiles, const uint16 heightInTiles, const std::vector<uint16>& mapData, Tilesheet& tilesheet) :
		m_mapData(mapData),
		m_tilesheet(tilesheet),
		m_widthInTiles(widthInTiles),
		m_heightInTiles(heightInTiles)
	{
		
	}

	Tilemap::~Tilemap()
	{

	}


}