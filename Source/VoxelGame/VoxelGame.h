#pragma once
#include "VoxelWorld.h"
#include "Engine/Application/EngineApplication.h"

namespace vxl
{
	class VoxelGame final : public gb::EngineApplication
	{
	public:
		VoxelGame();
		~VoxelGame();

		virtual	void Init()					override;
		virtual	bool LoadAssets()			override;
		virtual	void Start()				override;
		virtual void Update(const float dt) override;
		virtual void Render()				override;
		virtual void Stop()					override;
		virtual bool IsRunning()			override;

	private:
		World m_world;
	};
}