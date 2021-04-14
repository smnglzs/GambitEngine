#pragma once
#include "Base/GambitBasePCH.h"
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
		Texture(const std::string& name, const uint16 width, const uint16 height, const PixelFormat pixelFormat, const void* pixelData);
		virtual ~Texture();

		void Bind();

		virtual bool IsValid() const override { return m_valid; }
		inline const std::string& GetName() const { return m_name; }
		inline uint16 GetWidth() const { return m_width; }
		inline uint16 GetHeight() const { return m_height; }

		// TODO: implement move & copy

	protected:
		virtual void Destroy() override;

	private:
		std::string	m_name;
		uint16		m_width;
		uint16		m_height;
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