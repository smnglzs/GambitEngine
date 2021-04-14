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

	bool TextureManager::LoadTexture(const std::string& name, const std::string& filePath, const bool flipVertically)
	{
		if (name.empty() || filePath.empty())
		{
			LOG(EChannelComponent::EngineError, "Texture name or filepath is empty!");
			assert(false);
			return false;
		}

		stbi_set_flip_vertically_on_load(flipVertically);

		bool loadResult	= false;
		int32 width = 0, height = 0, channels = 0, desiredChannels = 4; // TODO: replace with mapping (NB: will likely always be 4 because RGBA is preferred)
		if (const uint8* pixelData = stbi_load((m_rootLoadPath + filePath).c_str(), &width, &height, &channels, desiredChannels))
		{
			const PixelFormat format = { EPixelDataFormat::RGBA, EPixelDataType::Uint8 }; // TODO: other formats as needed
			if (auto texture = std::make_unique<Texture>(name, width, height, format, pixelData))
			{
				m_textureMap.insert(std::make_pair(name, std::move(texture)));
				loadResult = true;
			}
			else
			{
				LOG(EChannelComponent::EngineError, "Texture construction failed!");
				assert(false);
			}
			stbi_image_free((void*)pixelData);
		}
		else
		{
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