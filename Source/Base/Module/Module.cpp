#include "Module.h"
#include "Base/GambitBasePCH.h"

namespace gb
{
	IModule::IModule() :
		m_loaded(false)
	{

	}

	IModule::~IModule()
	{
		// Check that Unload has been called by now
		assert(!m_loaded);
	}

	void IModule::Load()
	{
		RegisterSingletons();
		m_loaded = true;
	}

	void IModule::Init()
	{
		for (ISingleton* const singleton : m_singletons)
		{
			singleton->Init();
		}
	}

	void IModule::Start()
	{
		for (ISingleton* const singleton : m_singletons)
		{
			singleton->Start();
		}
	}

	void IModule::Stop()
	{
		for (ISingleton* const singleton : m_singletons)
		{
			singleton->Stop();
		}
	}

	void IModule::Uninit()
	{
		for (ISingleton* const singleton : m_singletons)
		{
			singleton->Uninit();
		}
	}

	void IModule::Unload()
	{
		m_singletons.clear();
		m_loaded = false;
	}

	void IModule::RegisterSingletons()
	{

	}
}