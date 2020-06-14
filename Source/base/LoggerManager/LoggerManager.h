#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

#include "Base/Singleton/Singleton.h"

namespace gb
{
	class GAMBIT_API LoggerManager : public ISingleton
	{
	public:
		LoggerManager() = default;
		~LoggerManager() = default;

		/// <summary>
		/// Log information in a predefined channel.
		/// Use the delimiters{} to insert a value into the string.
		/// </summary>
		/// <typeparam name="...Args">The information you want to add to the string. Must be a type that fits the std::to_string requirements.</typeparam>
		/// <param name="sv">The string you want to parse.</param>
		/// <param name="...args">Data that will be replaced into the string.</param>
		/// <returns>Boolean - Returns if the log operation was successful.</returns>
		template <typename ... Args>
		bool Log(std::string_view sv, Args ... args);

	//private:
		template <typename T>
		std::string  StringifyParameter(T parameter);
	};

	template <typename T>
	std::string	LoggerManager::StringifyParameter(T parameter)
	{
		return std::to_string(parameter);
	}

	template <typename ... Args>
	bool LoggerManager::Log(std::string_view sv, Args ... args)
	{
		if (sv.empty())
		{
			// Add a log that explains what failed. (?)
			return false;
		}

		constexpr const size_t delimiterSize = 2u;
		size_t currentPosition = 0u;
		size_t delimiterPosition = 0u;
		std::string output;

		while (currentPosition != std::string_view::npos)
		{
			delimiterPosition = sv.find_first_of("{}", currentPosition);

			// Delimiter Found.
			if (delimiterPosition != std::string_view::npos)
			{
				// Copy everything beforehand.
				output += sv.substr(currentPosition, delimiterPosition - currentPosition);

				// Add Parameter.
				output += std::to_string(42);

				// Update current position.
				currentPosition = delimiterPosition + delimiterSize;
			}
			else
			{
				// Copy rest of the string.
				output += sv.substr(currentPosition, delimiterPosition);

				// Set current position to npos.
				currentPosition = delimiterPosition;
			}
		}

		std::cout << "String with delimiters: " << sv << std::endl;
		std::cout << "String transformed: " << output << std::endl;

		return true;
	}
}