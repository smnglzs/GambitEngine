#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIDefinitions.h"
#include "Graphics/RHI/RHIObject.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Texture : public RHIObject
	{
	public:
		// TODO: add ETextureType ?
		Texture(const std::string& name, const uint16 width, const uint16 height, const PixelFormat pixelFormat, const void* pixelData);
		virtual ~Texture();

		void Bind();
		const std::string& GetName() const;

	protected:
		virtual void Destroy() override;

	private:
		std::string	m_name;
		uint16		m_width;
		uint16		m_height;
		PixelFormat m_pixelFormat;
	};
}