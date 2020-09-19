#include "GambitEngine.h" 

#include <algorithm>
#include <iostream>

#include "Device/Window/WindowManager.h"
#include "Graphics/Renderer/Renderer.h"

namespace gb
{
	void GambitEngine::StartEngine()
	{
		// This loads the DLLs and register the singletons.
		LoadModules();
		MainLoop();
	}

	void GambitEngine::LoadModules()
	{
		std::cout << "Loading modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Load();
		}
	}

	void GambitEngine::AddModule(std::unique_ptr<IModule>& module, EModulePriority priority, int32 indexPriority)
	{
		std::cout << "Adding module " << module->GetID() << "...\n";
		assert(!IsModuleAlreadyLoaded(module) && "Module already added!");

		// Add module to engine. 
		m_modules.push_back({ std::move(module), priority, indexPriority });

		SortModules();
	}

	bool GambitEngine::IsModuleAlreadyLoaded(const std::unique_ptr<IModule>& module) const
	{
		auto it = std::find_if(m_modules.begin(), m_modules.end(), [&module](const SModulePair& pair)
		{
			return pair.module == module;
		});

		return it != m_modules.end();
	}

	void GambitEngine::SortModules()
	{
		std::sort(m_modules.begin(), m_modules.end(), [](const SModulePair& lhs, const SModulePair& rhs)
		{
			if (lhs.priority < rhs.priority)
			{
				return true;
			}
			if (rhs.priority < lhs.priority)
			{
				return false;
			}

			if (lhs.m_samePriorityIndex > rhs.m_samePriorityIndex)
			{
				return true;
			}

			return false;
		});
	}

	void GambitEngine::MainLoop()
	{
		InitModules();
		StartModules();

		auto* winManager = GetWindowManager();
		auto* renderer = GetRenderer();
		while (IsRunning())
		{
			winManager->PollEvents();
			renderer->BeginFrame();
			// iterate over scene, transforming nodes and accumulating RenderBatch-es
			renderer->EndFrame();
			winManager->SwapBuffers();
		}

		StopModules();
		UninitModules();
	}

	bool GambitEngine::IsRunning() const
	{
		return !GetWindowManager()->ShouldClose();
	}

	void GambitEngine::UnLoadModules()
	{
		std::cout << "Unloading modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Unload();
		}

		m_modules.clear();
	}

	void GambitEngine::InitModules()
	{
		std::cout << "Initing modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Init();
		}
	}

	void GambitEngine::StartModules()
	{
		std::cout << "Starting modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Start();
		}
	}

	void GambitEngine::StopModules()
	{
		std::cout << "Stopping modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Stop();
		}
	}

	void GambitEngine::UninitModules()
	{
		std::cout << "Uinitting modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Uninit();
		}
	}
}