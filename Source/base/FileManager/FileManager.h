#pragma once
#include <any>
#include <filesystem>
#include <unordered_map>

#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"

namespace gb
{
	class GAMBIT_BASE_API FileManager : public ISingleton
	{
	public:
		FileManager() = default;
		virtual ~FileManager() override = default;

		void LoadConfigFile(const std::filesystem::path& path);
		void SaveConfigFile(const std::filesystem::path& path);

	private:

	};
}

CREATE_SINGLETON_ACCESSOR(FileManager, FileManager, GAMBIT_BASE_API);