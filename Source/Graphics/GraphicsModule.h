#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Module/Module.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API GraphicsModule final : public IModule
	{
	public:
		GraphicsModule();
		virtual ~GraphicsModule()		  override;

		virtual void RegisterSingletons() override;
		virtual void Init()				  override;
		virtual void Load()				  override;
		virtual void Unload()			  override;

		virtual std::string GetID() const override { return "Graphics"; }
	};

	/*
	class TextureManager;
	class ShaderManager;
	class GAMBIT_GRAPHICS_API GraphicsResources final
	{
	public:
		GraphicsResources() = delete;

		static void Init();

		static void SetManager(TextureManager* tm);
		static void SetManager(ShaderManager* sm);

		static inline TextureManager& Textures() { return *m_tm; } // TODO: check for null service
		static inline ShaderManager&  Shaders()  { return *m_sm; }

	private:
		static TextureManager* m_tm;
		static ShaderManager*  m_sm;
		// TODO: add null services here and in other systems
	};
	*/
}
