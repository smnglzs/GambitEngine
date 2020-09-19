#pragma once 
#include <map> 

#include "Base/Common/Common.h" 
#include "Base/Module/Module.h" 

namespace gb
{
	enum class EModulePriority : uint8
	{
		Base = 0,
		System,
		Runtime,
		Gameplay
	};

	class GambitEngine final
	{
	public:
		GambitEngine() = default;
		~GambitEngine() = default;

		/// <summary>
		/// Adds a module to load and manage.
		/// </summary>
		/// <param name="module">The module to load.</param>
		/// <param name="priority">The level priority of the DLL. The lower it is, the earlier it will load. (Base -> System -> Runtime -> Gameplay)</param>
		/// <param name="indexPriority">The higher the priority the earlier it will be loaded.</param>
		void AddModule(std::unique_ptr<IModule>& module, EModulePriority priority, int32 indexPriority);
		void StartEngine();

	private:
		struct SModulePair
		{
			std::unique_ptr<IModule> module;
			EModulePriority priority;
			int32 m_samePriorityIndex = 0;
		};

		bool IsModuleAlreadyLoaded(const std::unique_ptr<IModule>& module) const;

		void LoadModules();
		void UnLoadModules();
		void InitModules();
		void StartModules();
		void StopModules();
		void UninitModules();

		void SortModules();

		void MainLoop();
		bool IsRunning() const;

		std::vector<SModulePair> m_modules;
	};
}