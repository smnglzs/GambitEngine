#include "Texture.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	Texture::Texture() :
		m_valid(false),
		m_name("InvalidTexture"),
		m_width(0u),
		m_height(0u),
		m_pixelFormat()
	{

	}

	Texture::Texture(const std::string& name, const uint16 width, const uint16 height, const PixelFormat pixelFormat, const void* pixelData) :
		m_valid(false),
		m_name(name),
		m_width(width),
		m_height(height),
		m_pixelFormat(pixelFormat)
	{
		// TODO: Support more texture types. Also, possibly store pixelData.
		if (pixelData && width > 0u && height > 0u)
		{
			if (m_handle = GHI::CreateTexture(ETextureType::Texture2D, width, height, pixelFormat, pixelData))
			{
				m_valid = GHI::IsTexture(m_handle);
			}
		}
		assert(m_valid && "Texture creation requires valid pixel data and non-zero dimensions.");
	}

	Texture::~Texture()
	{
		Destroy();
	}

	void Texture::Destroy()
	{
		GHI::DeleteTexture(m_handle);
		m_handle = 0u;
		m_width = 0u;
		m_height = 0u;
		m_name = "";
	}

	void Texture::Bind()
	{
		// Check IsValid() here or in Bind() call sites?
		GHI::BindTexture(m_handle);
	}

	ArrayTexture::~ArrayTexture()
	{
		// We don't call Destroy because the parent GHIResource (Texture) does.
	}
}