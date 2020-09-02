#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"
#include "RHIDefinitions.h"

namespace gb
{
	class RHI final : public ISingleton
	{
	public:
		RHI();
		~RHI();
		
		void		 BeginFrame();
		void		 EndFrame();
		void		 ClearRenderTarget();
			 
		uint32		 CreateBuffer(const uint32 size, const void* data, const EBufferType type, const EBufferUsage usage);
		uint32		 CreateShader(const EShaderStage stage);
		uint32		 CreateShaderProgram();
		uint32		 CreateTexture(const ETextureType type, uint16 width, uint16 height, const PixelFormat format, const void* pixelData);
		uint32		 CreateVertexArray();
		void		 AddAttributeToVertexArray(const uint32 vertexArrayId, const VertexAttribute& vertexAttrib);

		void		 DeleteBuffer(const uint32 bufferId);
		void		 DeleteShader(const uint32 shaderId);
		void		 DeleteShaderProgram(const uint32 shaderId);
		void		 DeleteTexture(const uint32 textureId);
		void		 DeleteVertexArray(const uint32 vertexArrayId);

		void		 UpdateBuffer(const uint32 bufferId, const uint32 offset, const uint32 size, const void* data);
		void		 UpdateTexture(const uint32 textureId, const int32 offsetX, const int32 offsetY, const int32 width, const int32 height, const void* pixelData);

		bool		 CompileShader(const uint32 shaderId, const char* source);
		bool		 GetShaderCompileStatus(const uint32 shaderId) const;
		void		 GetShaderInfoLog(const uint32 shaderId, char* log);
		EShaderStage GetShaderStage(const uint32 shaderId) const;

		void		 AttachShaderToProgram(const uint32 shaderId, const uint32 programId);
		bool		 LinkShaderProgram(const uint32 programId);
		void		 BindShaderProgram(const uint32 programId);
		void		 BindTexture(const uint32 textureId);
		int32		 GetNumActiveUniforms(const uint32 programId);
		int32		 GetUniformLocation(const uint32 programId, const char* name);
		bool		 GetShaderProgramLinkStatus(const uint32 programId) const;
		void		 GetShaderProgramInfoLog(const uint32 programId, char* log);
		void		 SetUniform(const uint32 programId, const int32 location, const float value);
		void		 SetUniform(const uint32 programId, const int32 location, const int32 value);
		void		 SetUniform(const uint32 programId, const int32 location, const vec2f& value);
		void		 SetUniform(const uint32 programId, const int32 location, const vec2i& value);
		void		 SetUniform(const uint32 programId, const int32 location, const vec3f& value);
		void		 SetUniform(const uint32 programId, const int32 location, const vec3i& value);
		void		 SetUniform(const uint32 programId, const int32 location, const vec4f& value);
		void		 SetUniform(const uint32 programId, const int32 location, const vec4i& value);
					 
		void		 SetClearColor(const vec4f& color);
		void		 SetScissorRect(int32 x, int32 y, int32 width, int32 height);
		void		 SetViewport(int32 x, int32 y, int32 width, int32 height);
					 
		void		 DebugDraw(const EPrimitiveMode mode, const Vertex1P1UV* vertices, const uint32 vertexCount);
					 
	private:		 
		void		 EnableDebugging();
		bool		 InitLibrary();
		void		 ResetFrameCounters();
		bool		 CheckUniformLocation(const int32 location);

	private:
		uint32		 m_frameDrawCount;
		uint32		 m_framePrimCount[g_NumPrimitiveModes];
	};
}

CREATE_SINGLETON_ACCESSOR(RHI, RHI, GAMBIT_GRAPHICS_API);