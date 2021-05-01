#include "Engine.h" 

#include "System/Input/InputManager.h"
#include "System/Window/WindowManager.h"
#include "Engine/Application/EngineApplication.h"

#include <algorithm>
#include <iostream>

namespace gb
{
	Engine::Engine()
	{

	}

	Engine::~Engine()
	{
		StopEngine();
	}

	void Engine::StartEngine()
	{
		// This loads the DLLs and registers the singletons.
		LoadModules();
		InitModules();
		StartModules();
	}

	void Engine::StopEngine()
	{
		StopModules();
		UninitModules();
		UnLoadModules();
	}

	EApplicationExitCode Engine::RunApplication(EngineApplication& app)
	{
		std::cout << "Initializing app...\n";
		app.Init();

		std::cout << "Loading assets required by the app... \n";
		if (!app.LoadAssets())
			return EApplicationExitCode::LoadFailed;

		std::cout << "Starting app...\n";
		app.Start();
		
		// Binds the InputManager to the app's window, setting up KBM callbacks.
		gbInput->Init(app.GetWindow());

		Image icon(app.GetAssetFolder() + "icon.png", false);
		app.GetWindow()->SetIcon(icon);
		
		while (app.IsRunning())
		{
			app.GetWindow()->PollEvents();

			float deltaTime = 0.0f; // TODO
			app.Update(deltaTime);
			app.Render();
			app.Present();
		}

		std::cout << "Stopping app...\n";
		app.Stop();

		return EApplicationExitCode::Success;
	}

	void Engine::LoadModules()
	{
		std::cout << "Loading modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Load();
		}
	}

	void Engine::AddModule(std::unique_ptr<IModule>& module, EModulePriority priority, int32 indexPriority)
	{
		std::cout << "Adding module " << module->GetID() << "...\n";
		assert(!IsModuleAlreadyLoaded(module) && "Module already added!");

		// Add module to engine. 
		m_modules.push_back({ std::move(module), priority, indexPriority });

		SortModules();
	}

	bool Engine::IsModuleAlreadyLoaded(const std::unique_ptr<IModule>& module) const
	{
		auto it = std::find_if(m_modules.begin(), m_modules.end(), [&module](const SModulePair& pair)
		{
			return pair.module == module;
		});

		return it != m_modules.end();
	}

	void Engine::SortModules()
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

	void Engine::UnLoadModules()
	{
		std::cout << "Unloading modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Unload();
		}

		m_modules.clear();
	}

	void Engine::InitModules()
	{
		std::cout << "Initing modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Init();
		}
	}

	void Engine::StartModules()
	{
		std::cout << "Starting modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Start();
		}
	}

	void Engine::StopModules()
	{
		std::cout << "Stopping modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Stop();
		}
	}

	void Engine::UninitModules()
	{
		std::cout << "Uinitting modules...\n";
		for (SModulePair& modulePair : m_modules)
		{
			modulePair.module->Uninit();
		}
	}
}