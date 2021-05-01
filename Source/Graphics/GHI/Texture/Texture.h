#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Image/Image.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/GHICommon.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Texture : public GHIResource
	{
	public:
		static Texture& GetInvalidTexture()
		{
			static Texture invalid;
			return invalid;
		}

	public:
		Texture();
		Texture(const std::string& name, Image&& image, const PixelFormat pixelFormat);
		virtual ~Texture();

		void Bind();

		inline virtual bool IsValid() const override { return m_valid; }

		inline const std::string& GetName()      const { return m_name;					}
		inline const Image&		  GetImage()     const { return m_image;			    }
		inline int32			  GetWidth()     const { return m_image.GetWidth();     }
		inline int32			  GetHeight()    const { return m_image.GetHeight();    }
		inline const byte*		  GetPixelData() const { return m_image.GetPixelData(); }

		// TODO: implement move & copy

	protected:
		virtual void Destroy() override;

	private:
		std::string	m_name;
		Image		m_image;
		PixelFormat m_pixelFormat;
		bool		m_valid;
	};

	class GAMBIT_GRAPHICS_API ArrayTexture : public Texture
	{
	public:
		virtual ~ArrayTexture() override;

	private:

	};
}