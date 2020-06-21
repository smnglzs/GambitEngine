#pragma once

#include "Base/Common/Common.h"
#include "Base/Common/Export.h"
#include "Base/Common/NonCopyable.h"

#define CREATE_SINGLETON_ACCESSOR(iface, name)	\
namespace gb									\
{												\
inline iface* Get##name()						\
{												\
	extern char g_p##name##Singleton[];			\
	return (iface*)g_p##name##Singleton;		\
}												\
}												\

namespace gb
{
	class GAMBIT_API ISingleton : public NonCopyable
	{
	public:
		ISingleton() = default;
		virtual ~ISingleton() = default;
	};
}