#pragma once
#include <filesystem>
#include <fstream>

#include "Base/Utils/StringUtils.h"

namespace gb
{
	template <typename ... Args>
	void LoggerManager::Log(EChannelComponent component, const std::string_view& sv, Args ... args)
	{
		if (sv.empty())
		{
			return;
		}

		LogChannel channel;

		{
			const std::lock_guard<std::mutex> lock(m_channelMutex);
			if (!m_channels.contains(component))
			{
				return;
			}

			channel = m_channels.at(component);
		}

		std::string output { "[{}] - " };
		output.append(sv);
		output = utils::Format(output, GetHeader(channel.m_logLevel), args...);

		if (Bitmask::Contains(channel.m_outputType, EOutputType::File))
		{
			std::filesystem::path finalPath{ DEFAULT_LOG_PATH };

			std::filesystem::create_directories(finalPath);
			finalPath /= channel.m_path;

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