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

#define CREATE_LOG_CHANNEL(channelComponent, output, level, path) \
gb::GetLoggerManager()->AddChannel(channelComponent, output, level, path);

#define LOG(channelName, fmt, ...) \
gb::GetLoggerManager()->Log(channelName, fmt, __VA_ARGS__);

namespace gb
{
	class GAMBIT_BASE_API LoggerManager final : public ISingleton
	{
	public:
		LoggerManager();
		virtual ~LoggerManager() override;

		template <typename ... Args>
		void Log(EChannelComponent component, const std::string_view& sv, Args ... args);

		void AddChannel(EChannelComponent component, const LogChannel& channel);
		void AddChannel(EChannelComponent component, EOutputType output, ELogLevel level, const std::filesystem::path& path);
		void AddChannel(EChannelComponent component, EOutputType output, ELogLevel level, const std::string& path);
		void AddChannel(EChannelComponent component, EOutputType output, ELogLevel level, const char* path);

		std::optional<LogChannel> GetChannel(EChannelComponent component);

	private:
		std::string GetHeader(ELogLevel logLevel) const;

		constexpr static const size_t m_delimiterSize = 2u;
		const char* const m_delimiter = "{}";
		const char* DEFAULT_LOG_PATH = "Logs/";

		std::mutex m_channelMutex;
		std::unordered_map<EChannelComponent, LogChannel, EnumClassHash> m_channels;
	};
}

CREATE_SINGLETON_ACCESSOR(LoggerManager, LoggerManager, GAMBIT_BASE_API);

#include "LoggerManager_impl.h"