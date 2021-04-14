#pragma once
#include "Base/GambitBasePCH.h"

#include <filesystem>

#include "Base/Export.h"
#include "Base/FileManager/BaseConfig.h"
#include "Base/Singleton/Singleton.h"

namespace gb
{
	class GAMBIT_BASE_API FileManager : public ISingleton
	{
	public:
		FileManager() = default;
		virtual ~FileManager() override = default;

		bool SaveConfigFile(const std::filesystem::path& path, const BaseConfig& config);
		bool LoadConfigFile(const std::filesystem::path& path, BaseConfig& config);
		bool WriteToFile(const std::filesystem::path& path, const std::string& str);
		bool ReadFromFile(const std::filesystem::path& path, std::string& str);

	private:
		bool CreateDirectories(const std::filesystem::path& path);
	};
}

GB_CREATE_SINGLETON_ACCESSOR(FileManager, FileManager, GAMBIT_BASE_API);