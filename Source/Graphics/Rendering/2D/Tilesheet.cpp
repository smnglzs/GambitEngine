#include "Tilesheet.h"

namespace gb
{
	Tilesheet::Tilesheet(const Texture* texture, const uint16 tileSize, const vec2f offset) :
		Texture(*texture),
		m_tileSize(tileSize),
		m_tintColor(Color::Magenta),
		m_offset(offset),
		m_widthInTiles(0u),
		m_heightInTiles(0u)
	{
		if (texture)
		{
			m_widthInTiles  = texture->GetWidth()  / tileSize;
			m_heightInTiles = texture->GetHeight() / tileSize;
		}
		else
		{
			assert(false && "Null Texture!");
		}
	}

	Tilesheet::~Tilesheet()
	{

	}
}