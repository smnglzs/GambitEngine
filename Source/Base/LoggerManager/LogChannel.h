#pragma once
#include <filesystem>

#include "Base/Common/Common.h"
#include "Base/Export.h"

namespace gb
{
	enum class GAMBIT_BASE_API EOutputType : uint8
	{
		File	= (1 << 0),
		Console = (1 << 1),
		Both = File | Console
	};
	ENABLE_BITMASK_OPERATORS(EOutputType);

	enum class GAMBIT_BASE_API ELogLevel : uint8
	{
		Info	= (1 << 0),
		Warning	= (1 << 1),
		Error	= (1 << 2),
		Assert  = (1 << 3)
	};
	ENABLE_BITMASK_OPERATORS(ELogLevel); 

	enum class GAMBIT_BASE_API EChannelComponent : uint16
	{
		EngineInfo,
		EngineWarning,
		EngineError
	};

	struct GAMBIT_BASE_API LogChannel
	{
		LogChannel();
		LogChannel(EOutputType output, ELogLevel level);
		LogChannel(EOutputType output, ELogLevel level, const std::filesystem::path& path);
		LogChannel(EOutputType output, ELogLevel level, const std::string& path);
		LogChannel(EOutputType output, ELogLevel level, const char* const path);

		ELogLevel m_logLevel = ELogLevel::Info;
		EOutputType m_outputType = EOutputType::Console;
		std::filesystem::path m_path;
	};
}