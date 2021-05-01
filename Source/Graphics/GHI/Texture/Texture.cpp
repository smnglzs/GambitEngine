#include "Texture.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	Texture::Texture() :
		m_valid(false),
		m_name("InvalidTexture"),
		m_pixelFormat(),
		m_image({})
	{

	}

	Texture::Texture(const std::string& name, Image&& image, const PixelFormat pixelFormat) :
		m_valid(false),
		m_name(name),
		m_image(image),
		m_pixelFormat(pixelFormat)
	{
		// TODO: Support more texture types. Also, possibly store pixelData.
		if (GetPixelData() && GetWidth() > 0u && GetHeight() > 0u)
		{
			if (m_handle = GHI::CreateTexture(ETextureType::Texture2D, GetWidth(), GetHeight(), pixelFormat, GetPixelData()))
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