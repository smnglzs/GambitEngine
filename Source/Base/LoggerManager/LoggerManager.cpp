#include "LoggerManager.h"
#include "Base/GambitBasePCH.h"

namespace gb
{
	LoggerManager::LoggerManager()
	{

	}

	LoggerManager::~LoggerManager()
	{
		m_channels.clear();
	}

	std::string LoggerManager::GetHeader(ELogLevel logLevel) const
	{
		std::string header = "Undefined";

		switch (logLevel)
		{
		case ELogLevel::Info:
			header = "Info";
			break;
		case ELogLevel::Warning:
			header = "Warning";
			break;
		case ELogLevel::Error:
			header = "Error";
			break;
		case ELogLevel::Assert:
			header = "Assert";
			break;
		}

		return header;
	}

	void LoggerManager::AddChannel(EChannelComponent component, const LogChannel& channel)
	{
		const std::lock_guard<std::mutex> lock(m_channelMutex);
		if (m_channels.contains(component))
		{
			assert(false);
			return;
		}

		m_channels.insert({ component, channel });
	}

	void LoggerManager::AddChannel(EChannelComponent component, EOutputType output, ELogLevel level, const std::filesystem::path& path)
	{
		AddChannel(component, { output, level, path });
	}

	void LoggerManager::AddChannel(EChannelComponent component, EOutputType output, ELogLevel level, const std::string& path)
	{
		AddChannel(component, output, level, std::filesystem::path(path));
	}

	void LoggerManager::AddChannel(EChannelComponent component, EOutputType output, ELogLevel level, const char* path)
	{
		AddChannel(component, output, level, std::string(path));
	}

	std::optional<LogChannel> LoggerManager::GetChannel(EChannelComponent component)
	{
		std::lock_guard<std::mutex> lock(m_channelMutex);
		if (!m_channels.contains(component))
		{
			return std::nullopt;
		}

		return m_channels.at(component);
	}
}