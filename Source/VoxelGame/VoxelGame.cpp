#include "VoxelGame.h"
#include "VoxelWorld.h"
#include "System/Window/Window.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"
#include "Graphics/Rendering/2D/Renderer2D.h"

// TODO: Use for async loads.
#include <future>

#define ShaderManager  gb::GetShaderManager()
#define TextureManager gb::GetTextureManager()
#define Renderer2D	   gb::GetRenderer2D()

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
			if (window = GetWindowManager()->CreateWindow(WindowSettings{}, GLContextSettings{}))
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

		bool textureLoadResult = TextureManager->LoadTexture("QuestionBlock", "T_QuestionBlock.jfif");
		assert(textureLoadResult);
		
		return shaderLoadResult && textureLoadResult;
	}

	void VoxelGame::Start()
	{

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
		return m_window && !m_window->ShouldClose();
	}
}