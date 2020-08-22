#include "Texture.h"
#include "Graphics/RHI/RHI.h"

namespace gb
{
	Texture::Texture(const std::string& name, const uint16 width, const uint16 height, const PixelFormat pixelFormat, const void* pixelData) :
		m_name(name),
		m_width(width),
		m_height(height),
		m_pixelFormat(pixelFormat)
		// pixelData
	{

	}

	Texture::~Texture()
	{
		Destroy();
	}

	void Texture::Destroy()
	{
		m_RHI->DeleteTexture(m_id);
		m_id = 0;
	}

	const std::string& Texture::GetName() const
	{
		return m_name;
	}
}