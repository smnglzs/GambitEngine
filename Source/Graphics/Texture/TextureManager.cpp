#include "TextureManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/Texture/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gb
{
	static const char* g_FallbackTextureName = "FallbackTexture";

	TextureManager::TextureManager()
	{

	}

	TextureManager::~TextureManager()
	{

	}

	bool TextureManager::CreateFallbackTextures()
	{
		if (LoadTexture(g_FallbackTextureName, "D:/Projects/2020/GambitEngine/Assets/Textures/QuestionBlock.jfif", true))
		{
			LOG(EChannelComponent::EngineInfo, "Successfully created fallback textures.");
			return true;
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Fallback texture creation was unsuccessful!");
			assert(false);
			return false;
		}
	}

	void TextureManager::BindFallbackTexture()
	{
		BindTexture(g_FallbackTextureName);
	}

	bool TextureManager::LoadTexture(const std::string& name, const std::string& filePath, const bool flipHorizontally = true)
	{
		if (name.empty() || filePath.empty())
		{
			LOG(EChannelComponent::EngineError, "Texture name or filepath is empty!");
			assert(false);
			return false;
		}

		bool loadResult = false;
		int32 width = 0;
		int32 height = 0;
		int32 channels = 0;
		int32 desiredChannels = 4; // TODO: replace with mapping (NB: will likely always be 4 because RGBA is preferred)

		stbi_set_flip_vertically_on_load(flipHorizontally);
		const uint8* pixelData = stbi_load(filePath.c_str(), &width, &height, &channels, desiredChannels);
		std::vector<char> img;
		std::copy(&pixelData[0], &pixelData[width * height], std::back_inserter(img));
		if (pixelData)
		{
			const PixelFormat format = { EPixelDataFormat::RGBA, EPixelDataType::Uint8 };
			Unique<Texture> texture = std::make_unique<Texture>(name, width, height, format, pixelData);
			if (texture)
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
			LOG(EChannelComponent::EngineError, "Texture image load failed!");
			assert(false);
		}

		return loadResult;
	}

	void TextureManager::BindTexture(const std::string& name)
	{
		const auto tex = m_textureMap.find(name);
		if (tex == m_textureMap.end())
		{
			LOG(EChannelComponent::EngineError, "Texture named '{}' does not exist!", name);
			assert(false);
		}
		else
		{
			tex->second->Bind();
		}
	}
}