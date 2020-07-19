#include "LogChannel.h"

namespace gb
{
	LogChannel::LogChannel()
		: m_outputType(EOutputType::Console)
		, m_logLevel(ELogLevel::Info)
		, m_name("Undefined")
	{

	}

	LogChannel::LogChannel(const char* const name, EOutputType output, ELogLevel level)
		: m_outputType(output)
		, m_logLevel(level)
		, m_name(name)
	{

	}

	LogChannel::LogChannel(const std::string& name, EOutputType output, ELogLevel level)
		: m_outputType(output)
		, m_logLevel(level)
		, m_name(name)
	{

	}

	LogChannel::LogChannel(const std::string& name, EOutputType output, ELogLevel level, const std::filesystem::path& path)
		: m_outputType(output)
		, m_name(name)
		, m_logLevel(level)
		, m_path(path)
	{

	}

	LogChannel::LogChannel(const std::string& name, EOutputType output, ELogLevel level, const std::string& path)
		: m_outputType(output)
		, m_name(name)
		, m_logLevel(level)
		, m_path(path)
	{

	}

	LogChannel::LogChannel(const char* const name, EOutputType output, ELogLevel level, const char* const path)
		: m_outputType(output)
		, m_name(name)
		, m_logLevel(level)
		, m_path(path)
	{

	}
}