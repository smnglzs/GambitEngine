#include "TextureManager.h"
#include "Base/LoggerManager/LoggerManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gb
{
	TextureManager::TextureManager()
	{

	}

	TextureManager::~TextureManager()
	{
		// TODO: unload textures?
	}

	void TextureManager::SetRootLoadPath(const std::string& loadPath)
	{
		if (loadPath.empty())
		{
			LOG(EChannelComponent::EngineInfo, "Texture load path is empty! Current path will be unchanged.");
		}
		else
		{
			m_rootLoadPath = loadPath;
		}
	}

	bool TextureManager::LoadTexture(const std::string& name, const std::string& imagePath, const bool flipVertically)
	{
		if (name.empty() || imagePath.empty())
		{
			LOG(EChannelComponent::EngineError, "Texture name or filepath is empty!");
			assert(false);
			return false;
		}

		bool loadResult = false;
		Image image(imagePath, flipVertically);
		if (image.IsValid())
		{
			// TODO: add other formats as needed
			const PixelFormat format = { EPixelDataFormat::RGBA, EPixelDataType::Uint8 }; 
			if (Unique<Texture> texture = std::make_unique<Texture>(name, std::move(image), format))
			{
				m_textureMap.insert(std::make_pair(name, std::move(texture)));
				loadResult = true;
			}
			else
			{
				LOG(EChannelComponent::EngineError, "Texture construction failed!");
				assert(false);
			}
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Image load failed!");
			throw Exceptions::LoadFailed();
		}
		return loadResult;
	}

	const Texture* TextureManager::BindTexture(const std::string& name)
	{
		const auto tex = m_textureMap.find(name);
		if (tex == m_textureMap.end())
		{
			LOG(EChannelComponent::EngineError, "Texture named '{}' does not exist!", name);
			assert(false);
			return &Texture::GetInvalidTexture();
		}
		else
		{
			tex->second->Bind();
			return tex->second.get();
		}
	}
}