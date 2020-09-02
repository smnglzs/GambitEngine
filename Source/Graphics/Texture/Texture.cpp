#include "Texture.h"
#include "Graphics/RHI/RHI.h"

namespace gb
{
	Texture::Texture(const std::string& name, const uint16 width, const uint16 height, const PixelFormat pixelFormat, const void* pixelData) :
		m_name(name),
		m_width(width),
		m_height(height),
		m_pixelFormat(pixelFormat)
	{
		// TODO: Support more texture types. Also, possibly store pixelData.
		m_id = m_RHI->CreateTexture(ETextureType::Texture2D, width, height, pixelFormat, pixelData);
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

	void Texture::Bind()
	{
		m_RHI->BindTexture(m_id);
	}

	const std::string& Texture::GetName() const
	{
		return m_name;
	}
}