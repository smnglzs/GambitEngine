#pragma once

#include "Base/Common/Common.h"
#include "Base/Common/NonCopyable.h"
#include "Base/Export.h"

#define CREATE_SINGLETON_ACCESSOR(iface, name, API)	\
namespace gb										\
{													\
inline iface* Get##name()							\
{													\
	API extern char g_p##name##Singleton[];			\
	return (iface*)g_p##name##Singleton;			\
}													\
}													\

namespace gb
{
	class GAMBIT_BASE_API ISingleton : public NonCopyable
	{
	public:
		ISingleton() = default;
		virtual ~ISingleton() = default;
	};
}