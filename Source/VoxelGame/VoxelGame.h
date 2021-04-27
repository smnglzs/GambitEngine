#pragma once
#include "VoxelWorld.h"
#include "Engine/Application/EngineApplication.h"
#include "System/Input/Mouse/MouseEvent.h"

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
		void OnCursorEnterContentArea(gb::MouseEvent mouseEvent);
		void OnCursorMove(gb::MouseEvent mouseEvent);
		void OnKeyEvent(gb::KeyEvent keyEvent);
		void OnFocusChanged(gb::WindowEvent winEvent);
		
		World m_world;
	};
}