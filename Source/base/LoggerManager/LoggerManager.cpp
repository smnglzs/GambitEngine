#include "LoggerManager.h"

#include <assert.h>

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

	void LoggerManager::AddChannel(const std::string& name, const LogChannel& channel)
	{
		const std::lock_guard<std::mutex> lock(m_channelMutex);
		if (m_channels.contains(name))
		{
			assert(false);
			return;
		}

		m_channels.insert({ name, channel });
	}

	std::optional<LogChannel> LoggerManager::GetChannelFromName(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(m_channelMutex);
		if (!m_channels.contains(name))
		{
			return std::nullopt;
		}

		return m_channels.at(name);
	}
}