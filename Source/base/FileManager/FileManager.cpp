#include "FileManager.h"

#include <fstream>
#include <sstream>

#include "Base/LoggerManager/LoggerManager.h"

namespace gb
{
	bool FileManager::SaveConfigFile(const std::filesystem::path& path, const BaseConfig& config)
	{
		if (!CreateDirectories(path.parent_path()))
		{
			LOG(gb::EChannelComponent::EngineError, "{} - Can't create directories for path: [{}]", __func__, path.string());
			return false;
		}

		return WriteToFile(path, config.GetJson().dump(1));
	}

	bool FileManager::LoadConfigFile(const std::filesystem::path& path, BaseConfig& config)
	{
		if (path.empty())
		{
			return false;
		}

		std::string fileStr;
		if (!ReadFromFile(path, fileStr))
		{
			return false;
		}

		config.SetJson(nlohmann::json::parse(fileStr));

		return true;
	}

	bool FileManager::CreateDirectories(const std::filesystem::path& path)
	{
		if (path.empty())
		{
			return false;
		}

		if (!std::filesystem::exists(path))
		{
			return std::filesystem::create_directories(path);
		}

		return true;
	}

	bool FileManager::WriteToFile(const std::filesystem::path& path, const std::string& str)
	{
		if(path.empty())
		{
			return false;
		}

		std::ofstream ofs(path);
		if (!ofs.is_open())
		{
			LOG(gb::EChannelComponent::EngineError, "{} - Can't open file at path: [{}]", __func__, path.string());
			return false;
		}

		ofs << str;
		ofs.close();

		return true;
	}

	bool FileManager::ReadFromFile(const std::filesystem::path& path, std::string& str)
	{
		if (path.empty())
		{
			return false;
		}

		std::ifstream ifs(path);
		if (!ifs.is_open())
		{
			LOG(gb::EChannelComponent::EngineError, "{} - Can't open file at path: [{}]", __func__, path.string());
			return false;
		}

		std::stringstream buffer;
		buffer << ifs.rdbuf();

		str = buffer.str();
		ifs.close();

		return true;
	}
}