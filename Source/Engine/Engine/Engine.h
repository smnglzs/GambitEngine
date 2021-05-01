#pragma once 
#include <map> 

#include "Base/GambitBasePCH.h" 
#include "Base/Module/Module.h" 
#include "Engine/Export.h"
#include "Engine/Modules.h"

namespace gb
{
	enum class EModulePriority : uint8
	{
		Base = 0,
		System,
		Runtime,
		Gameplay
	};

	enum class EApplicationExitCode : uint8
	{
		Success, // Must be first
		// InitFailed,
		LoadFailed
	};

	class Engine final
	{
	public:
		GAMBIT_ENGINE_API Engine();
		GAMBIT_ENGINE_API ~Engine();

		/// <summary>
		/// Adds a module to load and manage.
		/// </summary>
		/// <param name="module">The module to load.</param>
		/// <param name="priority">The level priority of the DLL. The lower it is, the earlier it will load. (Base -> System -> Runtime -> Gameplay)</param>
		/// <param name="indexPriority">The higher the priority the earlier it will be loaded.</param>
		GAMBIT_ENGINE_API void AddModule(std::unique_ptr<IModule>& module, EModulePriority priority, int32 indexPriority);
		GAMBIT_ENGINE_API void StartEngine();
		GAMBIT_ENGINE_API EApplicationExitCode RunApplication(class EngineApplication& application);

	private:
		struct SModulePair
		{
			std::unique_ptr<IModule> module;
			EModulePriority priority;
			int32 m_samePriorityIndex = 0;
		};

		void StopEngine();

		bool IsModuleAlreadyLoaded(const std::unique_ptr<IModule>& module) const;

		void LoadModules();
		void UnLoadModules();
		void InitModules();
		void StartModules();
		void StopModules();
		void UninitModules();

		void SortModules();

		std::vector<SModulePair> m_modules;
	};

}