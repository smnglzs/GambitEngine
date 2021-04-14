#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Common/Color.h"

namespace vxl
{
	struct WorldBlock
	{
		enum BlockType : gb::uint16
		{
			Ground,
			Question,
			Bush,
			Pipe
		};

		WorldBlock(const BlockType type, const gb::vec2us position, const gb::vec2us size = { 1, 1 });
		virtual ~WorldBlock() = default;

		static bool IsTileable(const BlockType type);

		gb::vec2us position;
		gb::vec2us size;
		BlockType  type;
	};

	class WorldData final
	{
	public:
		WorldData();
		WorldData(const std::string& name, const gb::Color& backgroundColor, std::vector<WorldBlock>&& blocks);

		bool LoadWorld(const std::string& worldFileName, const std::string& blockTypeFileName);

	private:

	private:
		std::vector<WorldBlock> m_blocks;
		std::string				m_worldName;
		gb::Color				m_backgroundColor;
	};

	class World final : public gb::ISingleton
	{
	public:
		World();
		~World();

	private:
		WorldData m_worldData;
	};
}