#include "Base/GambitBasePCH.h"

namespace gb
{
	namespace utils
	{
		HashedString::HashedString() :
			m_str(""),
			m_hash(0u)
		{
		}

		HashedString::HashedString(const std::string& str) :
			m_str(str),
			m_hash(HashString(m_str))
		{
		}

		void HashedString::SetString(const std::string& str)
		{
			m_str  = str;
			m_hash = HashString(m_str);
		}
		
		const std::string& HashedString::GetString()						const { return m_str; }
		HashedString::Hash HashedString::GetHash()							const { return m_hash; }
		HashedString::Hash HashedString::HashString(const std::string& str) const { return std::hash<std::string>{}(str); }
	}
}