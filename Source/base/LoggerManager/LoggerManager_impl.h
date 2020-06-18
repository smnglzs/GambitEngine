#pragma once
#include <filesystem>
#include <fstream>

namespace gb
{
	template <typename T>
	std::string	LoggerManager::StringifyParameter(T&& parameter)
	{
		return std::to_string(parameter);
	}

	template <typename T, typename ... Args>
	void LoggerManager::Log_Internal(const std::string_view& sv, std::string& output, size_t& currentPosition, T&& parameter, Args ... args)
	{
		if (currentPosition == std::string::npos)
		{
			return;
		}

		size_t delimiterPosition = std::string::npos;

		delimiterPosition = sv.find_first_of(m_delimiter, currentPosition);

		if (delimiterPosition != std::string::npos)
		{
			// Copy everything beforehand.
			output += sv.substr(currentPosition, delimiterPosition - currentPosition);

			// Add Parameter.
			output += StringifyParameter(parameter);

			// Update current position.
			currentPosition = delimiterPosition + m_delimiterSize;

			Log_Internal(sv, output, currentPosition, args...);
		}
		else
		{
			// Copy rest of the string.
			output += sv.substr(currentPosition, delimiterPosition);

			// Set current position to npos.
			currentPosition = delimiterPosition;
		}
	}

	template <typename ... Args>
	void LoggerManager::Log(const std::string& channelName, const std::string_view& sv, Args ... args)
	{
		if (sv.empty())
		{
			// Add a log that explains what failed. (?)
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

		size_t currentPosition = 0u;
		std::string output;

		Log_Internal(sv, output, currentPosition, args...);

		output = AddHeader(output, channel.m_logLevel);

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
			std::cout << "String with delimiters: " << sv << std::endl;
			std::cout << "String transformed: " << output << std::endl;
		}
	}
}