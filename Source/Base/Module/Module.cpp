#include "Module.h"

namespace gb
{
	IModule::IModule()
	{

	}

	IModule::~IModule()
	{

	}

	void IModule::Load()
	{
		RegisterSingletons();
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
	}

	void IModule::RegisterSingletons()
	{

	}
}