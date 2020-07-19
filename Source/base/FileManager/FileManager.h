#pragma once
#include <filesystem>
#include <unordered_map>

#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"

namespace gb
{
	class FileManager : public ISingleton
	{
	public:
		FileManager() = default;
		virtual ~FileManager() override = default;

		void LoadConfigFile(const std::filesystem::path& path, std::unordered_map<std::string, std::string>& configs);
		void SaveConfigFile(const std::filesystem::path& path);

	private:

	};
}

CREATE_SINGLETON_ACCESSOR(FileManager, FileManager);