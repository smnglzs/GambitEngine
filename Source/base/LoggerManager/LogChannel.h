#pragma once
#include <filesystem>

#include "Base/Common/Common.h"

namespace gb
{
	enum class GAMBIT_API EOutputType : uint8_t
	{
		File	= (1 << 0),
		Console = (1 << 1),
		Both = File | Console
	};
	ENABLE_BITMASK_OPERATORS(EOutputType);

	enum class GAMBIT_API ELogLevel : uint8_t
	{
		Info	= (1 << 0),
		Warning	= (1 << 1),
		Error	= (1 << 2),
		Assert  = (1 << 3)
	};
	ENABLE_BITMASK_OPERATORS(ELogLevel);

	struct GAMBIT_API LogChannel
	{
		LogChannel();
		LogChannel(const char* const name, EOutputType output, ELogLevel level);
		LogChannel(const std::string& name, EOutputType output, ELogLevel level);
		LogChannel(const std::string& name, EOutputType output, ELogLevel level, const std::filesystem::path& path);
		LogChannel(const std::string& name, EOutputType output, ELogLevel level, const std::string& path);
		LogChannel(const char* const name, EOutputType output, ELogLevel level, const char* const path);

		ELogLevel m_logLevel = ELogLevel::Info;
		EOutputType m_outputType = EOutputType::Console;
		std::string m_name = "Undefined";
		std::filesystem::path m_path;
	};
}