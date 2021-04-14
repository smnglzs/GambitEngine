#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"

#define DEFINE_SINGLETON(cls, name, API)						\
alignas(cls) API char g_p##name##Singleton[sizeof(cls)] = {0};	\

#define REGISTER_SINGLETON(cls, name)				\
new(g_p##name##Singleton) cls;						\
m_singletons.push_back((cls*)g_p##name##Singleton);	\

namespace gb
{
	class GAMBIT_BASE_API IModule
	{
	public:
		IModule();
		virtual ~IModule();

		virtual void Load();
		virtual void Init();
		virtual void Start();
		virtual void Stop();
		virtual void Uninit();
		virtual void Unload();

		/// <summary>
		/// This is where the singletons get added to the module (with the help of Macros)
		///	See REGISTER_SINGLETON for more info.
		/// </summary>
		virtual void RegisterSingletons();

		virtual std::string GetID() const = 0;

	protected:
		std::vector<ISingleton*> m_singletons;
		bool m_loaded;
	};
}