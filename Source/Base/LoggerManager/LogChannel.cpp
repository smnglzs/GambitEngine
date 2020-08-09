#include "LogChannel.h"

namespace gb
{
	LogChannel::LogChannel()
		: m_outputType(EOutputType::Console)
		, m_logLevel(ELogLevel::Info)
	{

	}

	LogChannel::LogChannel(EOutputType output, ELogLevel level)
		: m_outputType(output)
		, m_logLevel(level)
	{

	}

	LogChannel::LogChannel(EOutputType output, ELogLevel level, const std::filesystem::path& path)
		: m_outputType(output)
		, m_logLevel(level)
		, m_path(path)
	{

	}

	LogChannel::LogChannel(EOutputType output, ELogLevel level, const std::string& path)
		: m_outputType(output)
		, m_logLevel(level)
		, m_path(path)
	{

	}

	LogChannel::LogChannel(EOutputType output, ELogLevel level, const char* const path)
		: m_outputType(output)
		, m_logLevel(level)
		, m_path(path)
	{

	}
}