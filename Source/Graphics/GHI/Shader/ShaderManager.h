#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Base/Utils/StringUtils.h"
#include "Graphics/Export.h"
#include "Graphics/GraphicsModule.h"
#include "Graphics/GHI/GHICommon.h"
#include "Graphics/GHI/Shader/Shader.h"
#include "Graphics/GHI/Shader/ShaderProgram.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API ShaderManager final : public ISingleton
	{
	public:
		ShaderManager();
		~ShaderManager();

		void SetRootLoadPath(const std::string& loadPath);

		bool LoadShader(const std::string& name, const std::string& source, const EShaderStage stage);
		bool LoadShader(const std::string& filePath);
		bool CreateShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName, const std::string& programName);
		
		/* TODO: 
		*	- StringHash refs
		*/

		ShaderProgram& BindShaderProgram(const std::string& name);

	private:
		friend void GraphicsModule::Init();

	private:
		StringHashmap<Unique<Shader>>		 m_shaderMap;
		StringHashmap<Unique<ShaderProgram>> m_shaderProgramMap;
		std::string							 m_rootLoadPath;
		ShaderProgram*						 m_boundShaderProgram;
	};
}

GB_CREATE_SINGLETON_ACCESSOR(ShaderManager, ShaderManager, GAMBIT_GRAPHICS_API);

/* TODO:
	- Implement precompiled shader/program cache.
	- Extract interface that can be shared with TextureManager (e.g. IAssetManager)
	- SetRootLoadPath
	- LoadXXX(data), LoadXXX(filePath)
*/
