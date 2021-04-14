#include "VoxelWorld.h"
#include "Base/FileManager/BaseConfig.h"
#include "Base/FileManager/FileManager.h"
#include "nlohmann/json.hpp"

namespace vxl
{
	WorldBlock::WorldBlock(const BlockType type, const gb::vec2us position, const gb::vec2us size) :
		type(type), 
		position(position), 
		size(size)
	{
	}

	bool WorldBlock::IsTileable(const BlockType type)
	{
		bool tileable = true;
		switch (type)
		{
		case BlockType::Question:
			tileable = false;
			break;
		default:
			tileable = true;
		}
		return tileable;
	}

	WorldData::WorldData() :
		m_worldName("EmptyWorldData"),
		m_backgroundColor(gb::Color::Magenta)
	{
	}

	WorldData::WorldData(const std::string& name, const gb::Color& backgroundColor, std::vector<WorldBlock>&& blocks) :
		m_blocks(blocks),
		m_worldName(name),
		m_backgroundColor(backgroundColor)
	{
	}

	bool WorldData::LoadWorld(const std::string& worldFileName, const std::string& blockTypeFileName)
	{
		gb::BaseConfig worldData, blockData;
		if (gb::GetFileManager()->LoadConfigFile(worldFileName,     worldData) && 
			gb::GetFileManager()->LoadConfigFile(blockTypeFileName, blockData))
		{
			auto worldName = worldData.GetMember<std::string>("WorldName");
			m_worldName = worldName.has_value() ? worldName.value() : worldFileName;

			auto worldSize = gb::BaseConfig::GetVec<2, gb::uint16>(worldData.GetJson(), "WorldSize").value();
			m_blocks.reserve(worldSize.x * worldSize.y);

			auto backgroundColor = worldData.GetVec<3, float>(worldData.GetJson(), "BackgroundColor").value();
			m_backgroundColor.RGB = backgroundColor;

			return true;
		}

		return false;
	}

	World::World()
	{
		
	}

	World::~World()
	{

	}
}