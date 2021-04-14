#pragma once

#include "Base/GambitBasePCH.h"
#include "Base/Common/NonCopyable.h"
#include "Base/Export.h"

#define CREATE_SINGLETON_ACCESSOR(ns, iface, name, API)	\
namespace ns								\
{											\
inline iface* Get##name()					\
{											\
	API extern char g_p##name##Singleton[];	\
	return (iface*)g_p##name##Singleton;	\
}											\
}											\

#define GB_CREATE_SINGLETON_ACCESSOR(iface, name, API)	CREATE_SINGLETON_ACCESSOR(gb, iface, name, API)

namespace gb
{
	class GAMBIT_BASE_API ISingleton : public NonCopyable
	{
	public:
		ISingleton() = default;
		virtual ~ISingleton() = default;

		virtual void Init() {}
		virtual void Start() {}
		virtual void Stop()	{}
		virtual void Uninit() {}
	};
}