#pragma once
#include <filesystem>
#include <fstream>

#include "Base/Utils/StringUtils.h"

namespace gb
{
	template <typename ... Args>
	void LoggerManager::Log(const std::string& channelName, const std::string_view& sv, Args ... args)
	{
		if (sv.empty())
		{
			return;
		}

		LogChannel channel;

		{
			const std::lock_guard<std::mutex> lock(m_channelMutex);
			if (!m_channels.contains(channelName))
			{
				return;
			}

			channel = m_channels.at(channelName);
		}

		std::string output { "[{}] - {} - " };
		output.append(sv);
		output = utils::Format(output, GetHeader(channel.m_logLevel), channel.m_name, args...);

		if (Bitmask::Contains(channel.m_outputType, EOutputType::File))
		{
			std::filesystem::path finalPath{ DEFAULT_LOG_PATH };

			std::filesystem::create_directories(finalPath);
			finalPath /= channel.m_path;

			auto testPath = std::filesystem::current_path();

			std::ofstream ofs(finalPath);
			ofs << output;
			ofs.close();
		}

		if (Bitmask::Contains(channel.m_outputType, EOutputType::Console))
		{
			std::cout << output << std::endl;
		}
	}
}