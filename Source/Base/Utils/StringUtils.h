#pragma once
#include <type_traits>

#include "Base/Common/Common.h"

namespace gb
{
	namespace utils
	{
		namespace details
		{
			static constexpr const size_t g_delimiterSize = 2u;
			static constexpr const char* const g_delimiter = "{}";

			template <typename T>
			std::string StringifyParameter(T&& parameter)
			{
				if constexpr (std::is_same<std::remove_reference_t<std::remove_const_t<T>>, std::string>::value) 
				{
					return parameter;
				}
				else if constexpr (std::is_same<std::remove_reference_t<std::remove_const_t<T>>, const char*>::value)
				{
					return parameter;
				}
				else
				{
					return std::to_string(std::forward<T>(parameter));
				}
			}

			inline void Format_Internal(const std::string_view& sv, std::string& output, size_t& currentPosition)
			{
				if (currentPosition == std::string::npos)
				{
					return;
				}

				output += sv.substr(currentPosition);
			}

			template <typename T, typename ... Args>
			void Format_Internal(const std::string_view& sv, std::string& output, size_t& currentPosition, T&& parameter, Args&&... args)
			{
				if (currentPosition == std::string::npos)
				{
					return;
				}

				size_t delimiterPosition = std::string::npos;

				delimiterPosition = sv.find_first_of(g_delimiter, currentPosition);

				if (delimiterPosition != std::string::npos)
				{
					// Copy everything beforehand.
					output += sv.substr(currentPosition, delimiterPosition - currentPosition);

					// Add Parameter.
					output += StringifyParameter(std::forward<T>(parameter));

					// Update current position.
					currentPosition = delimiterPosition + g_delimiterSize;

					Format_Internal(sv, output, currentPosition, std::forward<Args>(args)...);
				}
				else
				{
					// Copy rest of the string.
					output += sv.substr(currentPosition, delimiterPosition);

					// Set current position to npos.
					currentPosition = delimiterPosition;
				}
			}
		}

		template <typename ...Args>
		std::string Format(const std::string_view& fmt, Args&&... args)
		{
			if (fmt.empty())
			{
				return std::string();
			}

			size_t currentPosition = 0u;
			std::string output;

			details::Format_Internal(fmt, output, currentPosition, std::forward<Args>(args)...);

			return output;
		}

		class GAMBIT_BASE_API HashedString
		{
		public:
			using Hash = uint64_t;

			HashedString();
			HashedString(const std::string& str);

			void SetString(const std::string& str);
			const std::string& GetString() const;
			uint64_t GetHash() const;

		private:
			Hash HashString(const std::string& str) const;

			std::string m_str;
			Hash		m_hash;
		};
	}
}