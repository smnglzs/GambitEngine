#include "VoxelGame.h"
#include "VoxelWorld.h"
#include "System/Input/InputManager.h"
#include "System/Window/WindowManager.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"
#include "Graphics/Rendering/2D/Renderer2D.h"

// TODO: Use for async loads.
#include <future>

#define InputManager   gb::GetInputManager()
#define Renderer2D	   gb::GetRenderer2D()
#define ShaderManager  gb::GetShaderManager()
#define TextureManager gb::GetTextureManager()

namespace vxl
{
	using namespace gb;

	VoxelGame::VoxelGame()
	{

	}

	VoxelGame::~VoxelGame()
	{
		
	}

	void VoxelGame::Init()
	{
		Window* window = GetWindowManager()->GetWindow();
		if (window == nullptr)
		{
			// Window
			WindowSettings winSettings;
			winSettings.fixedAspectRatio = true;

			// GL Context
			GLContextSettings ctxSettings;

			if (window = GetWindowManager()->CreateWindow(winSettings, ctxSettings))
				SetWindow(window);
		}
		else
		{
			SetWindow(window);
		}

		Renderer2D->Init();
	}

	bool VoxelGame::LoadAssets()
	{
		ShaderManager->SetRootLoadPath(m_assetFolder + "Shaders\\");
		TextureManager->SetRootLoadPath(m_assetFolder + "Textures\\");

		bool shaderLoadResult = false;
		if (ShaderManager->LoadShader("VS_Basic.glsl") && ShaderManager->LoadShader("FS_Basic.glsl") &&
			ShaderManager->LoadShader("VS_Grid.glsl")  && ShaderManager->LoadShader("FS_Grid.glsl"))
		{
			shaderLoadResult = ShaderManager->CreateShaderProgram("VS_Basic", "FS_Basic", "SP_Basic") &&
							   ShaderManager->CreateShaderProgram("VS_Grid",  "FS_Grid",  "SP_Grid");
		}
		assert(shaderLoadResult);

		return shaderLoadResult;
	}

	void VoxelGame::Start()
	{
		EngineApplication::Start();

		// KBM event examples
		gbMouseAddListener(MouseEvent::ECode::EnterContentArea, this, VoxelGame::OnCursorEnterContentArea);
		gbMouseAddListener(MouseEvent::ECode::Move, this, VoxelGame::OnCursorMove);
		gbKeyboardAddListener(KeyEvent::ECode::Press, this, VoxelGame::OnKeyEvent);
		gbKeyboardAddListener(KeyEvent::ECode::Release, this, VoxelGame::OnKeyEvent);

		// Window event example
		gbWindowAddListener(m_window, WindowEvent::ECode::FocusChanged, this, VoxelGame::OnFocusChanged);
	}

	void VoxelGame::Update(const float deltaTime)
	{
	
	}

	void VoxelGame::Render()
	{
		Renderer2D->Clear();
		
	}

	void VoxelGame::Stop()
	{

	}

	bool VoxelGame::IsRunning()
	{
		return m_running && m_window && !m_window->ShouldClose();
	}

	//--------------------------------------------------------------
	//	Event examples
	//--------------------------------------------------------------
	void VoxelGame::OnCursorEnterContentArea(MouseEvent mouseEvent)
	{
		Renderer2D->GetCamera().SetClearColor(mouseEvent.enteredContentArea ? Color::Green : Color::Red);
	}

	void VoxelGame::OnCursorMove(MouseEvent mouseEvent)
	{
		Color posAsColor(mouseEvent.position.x / m_window->GetWidth(), mouseEvent.position.y / m_window->GetHeight(), 1.f);
		Renderer2D->GetCamera().SetClearColor(posAsColor);
	}

	void VoxelGame::OnKeyEvent(KeyEvent keyEvent)
	{
		Renderer2D->GetCamera().SetClearColor(keyEvent.code == (uint8)KeyEvent::ECode::Press ? Color::Blue : Color::Yellow);
	}

	void VoxelGame::OnFocusChanged(gb::WindowEvent winEvent)
	{
		printf("Window %s focus\n", winEvent.focused ? "gained" : "lost");
		winEvent.window->SetOpacity(winEvent.focused ? 1.f : 0.5f);
	}
}