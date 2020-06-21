#pragma once
#include <iostream>
#include <mutex>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>

#include "Base/LoggerManager/LogChannel.h"
#include "Base/Singleton/Singleton.h"

namespace gb
{
	class GAMBIT_API LoggerManager : public ISingleton
	{
	public:
		LoggerManager();
		~LoggerManager();

		template <typename ... Args>
		void Log(const std::string& channelName, const std::string_view& sv, Args ... args);

		void AddChannel(const std::string& name, const LogChannel& channel);

		std::optional<LogChannel> GetChannelFromName(const std::string& name);

	private:
		std::string GetHeader(ELogLevel logLevel) const;

		constexpr static const size_t m_delimiterSize = 2u;
		const char* const m_delimiter = "{}";
		const char* DEFAULT_LOG_PATH = "Logs/";

		std::mutex m_channelMutex;
		std::unordered_map<std::string, LogChannel> m_channels;
	};
}

#include "LoggerManager_impl.h"