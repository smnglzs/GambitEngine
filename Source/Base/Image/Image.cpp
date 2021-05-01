#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gb
{
	Image::Image(const std::string& imagePath, const bool flipVertically) :
		m_valid(false)
	{
		LoadFromFile(imagePath, flipVertically);
	}

	Image::~Image()
	{
		FreePixelData();
	}

	bool Image::LoadFromFile(const std::string& filePath, const bool flipVertically)
	{
		int32 channels = 0;
		int32 desiredChannels = 4;
		stbi_set_flip_vertically_on_load(flipVertically);
		if (m_pixelData = stbi_load(filePath.c_str(), &m_width, &m_height, &channels, desiredChannels))
		{
			gbCheckRange(m_width > 0 && m_height > 0);
			m_valid = true;
		}
		else
		{
			m_valid = false;
			throw Exceptions::LoadFailed();
		}
		return m_valid;
	}

	void Image::FreePixelData()
	{
		stbi_image_free((void*)m_pixelData);
	}
}