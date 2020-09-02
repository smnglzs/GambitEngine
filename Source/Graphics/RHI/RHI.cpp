#include "RHI.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "GL/glew.h"

/*
	TODO: create log channel(s) for RHIObjects and a public RHI method for them to log
		(only if necessary)
		- enable blend mode
*/

namespace GL
{
	void OnDebugMessage(GLenum source, GLenum type, GLuint id, GLenum level, GLsizei length, const GLchar* message, const void* userParam)
	{
		const bool isDebugError = type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "";
		LOG(gb::EChannelComponent::EngineError, "Source: {}\nDebug: {}\nSeverity: {}Message: {}\n", source, isDebugError, level, message);
	}

	/*
		TODO: create "RHIDefinition -> GL constants" mapping and get rid of switch blocks
			e.g. EBufferUsage::StaticRead -> GL_STATIC_READ
	*/
}

namespace gb
{
	RHI::RHI()
	{
		assert(InitLibrary());
		ResetFrameCounters();
	}

	RHI::~RHI()
	{
		
	}

	void RHI::BeginFrame()
	{
		ResetFrameCounters();
	}

	void RHI::EndFrame()
	{
		/*
		uint32 totalPrimCount = 0u;
		for (uint8 i = 0u; i < EPrimitiveMode::Count; ++i)
		{
			totalPrimCount += m_framePrimCount[i];
		}
		*/
	}

	void RHI::ClearRenderTarget()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	uint32 RHI::CreateBuffer(const uint32 size, const void* data, const EBufferType type, const EBufferUsage usage)
	{
		/*
			TODO: EBufferType isn't currently used!
		*/

		GLenum usageHint = 0u;
		switch (usage)
		{
		case EBufferUsage::DynamicCopy: usageHint = GL_DYNAMIC_COPY; break;
		case EBufferUsage::DynamicDraw: usageHint = GL_DYNAMIC_DRAW; break;
		case EBufferUsage::DynamicRead: usageHint = GL_DYNAMIC_READ; break;
		case EBufferUsage::StaticCopy:  usageHint = GL_STATIC_COPY;  break;
		case EBufferUsage::StaticDraw:  usageHint = GL_STATIC_DRAW;  break;
		case EBufferUsage::StaticRead:  usageHint = GL_STATIC_READ;  break;
		case EBufferUsage::StreamCopy:  usageHint = GL_STREAM_COPY;  break;
		case EBufferUsage::StreamDraw:  usageHint = GL_STREAM_DRAW;  break;
		case EBufferUsage::StreamRead:  usageHint = GL_STREAM_READ;  break;
		}

		GLuint bufferId = 0u;
		glCreateBuffers(1, &bufferId);
		glNamedBufferData(bufferId, size, data, usageHint);

		assert(bufferId);
		return bufferId;
	}

	void RHI::UpdateBuffer(const uint32 bufferId, const uint32 offset, const uint32 size, const void* data)
	{
		glNamedBufferSubData(bufferId, offset, size, data);
	}

	void RHI::UpdateTexture(const uint32 textureId, const int32 offsetX, const int32 offsetY, const int32 width, const int32 height, const void* pixelData)
	{
		/*
			We make three assumptions about 2D rendering in Gambit (for now):
				- that single-mip textures will suffice
				- that RGB/A 
		*/
		const GLint  mipLevel		 = 0u; // assuming single-mip textures for now
		const GLenum pixelDataFormat = GL_RGBA;
		const GLenum pixelDataType	 = GL_UNSIGNED_BYTE;

		glTextureSubImage2D(textureId, mipLevel, offsetX, offsetY, width, height, pixelDataFormat, pixelDataType, pixelData);
	}

	void RHI::DeleteBuffer(const uint32 bufferId)
	{
		glDeleteBuffers(1, &bufferId);
	}

	uint32 RHI::CreateShader(const EShaderStage stage)
	{
		if (stage == EShaderStage::Vertex)
		{
			return glCreateShader(GL_VERTEX_SHADER);
		}
		else if (stage == EShaderStage::Fragment)
		{
			return glCreateShader(GL_FRAGMENT_SHADER);
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Shader stage not supported!");
			assert(false);
			return 0u;
		}
	}

	uint32 RHI::CreateShaderProgram()
	{
		return glCreateProgram();
	}

	uint32 RHI::CreateTexture(const ETextureType type, uint16 width, uint16 height, const PixelFormat format, const void* pixelData)
	{
		GLenum textureTarget = 0u;
		switch (type)
		{
		case ETextureType::Texture2D:		textureTarget = GL_TEXTURE_2D;		 break;
		case ETextureType::Texture2DArray:	textureTarget = GL_TEXTURE_2D_ARRAY; // not yet supported so let this fall through
		default:
			LOG(EChannelComponent::EngineError, "Texture type is not yet supported or does not exist!");
			assert(false);
			return 0u;
		}

		GLuint textureId = 0u;
		glCreateTextures(textureTarget, 1, &textureId);
		assert(textureId);

		// TODO: revisit this after adding support for additional texture types and pixel formats
		glTextureStorage2D(textureId, 1, GL_RGBA8, width, height);
		// TODO: replace the below call with a call to UpdateTexture(...), passing in the desired type and format
		glTextureSubImage2D(textureId, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
		
		glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		return textureId;
	}

	uint32 RHI::CreateVertexArray()
	{
		GLuint vertexArrayId = 0u;
		glCreateVertexArrays(1, &vertexArrayId);
		assert(vertexArrayId);
		return vertexArrayId;
	}

	void RHI::AddAttributeToVertexArray(const uint32 vertexArrayId, const VertexAttribute& vertexAttribute)
	{
		GLenum elementType = 0u;
		switch (vertexAttribute.elementType)
		{
		case EElementType::Float: elementType = GL_FLOAT; break;
		case EElementType::Int32: elementType = GL_INT;   break;
		default:
			LOG(EChannelComponent::EngineError, "Vertex attribute element type does not exist!");
			assert(false);
			return;
		}

		glVertexArrayAttribFormat(vertexArrayId, vertexAttribute.location, g_ElementTypeSizes[(uint8)vertexAttribute.elementType], elementType, vertexAttribute.isNormalized, vertexAttribute.offset);
		glVertexArrayAttribBinding(vertexArrayId, vertexAttribute.location, vertexAttribute.location);
		glEnableVertexArrayAttrib(vertexArrayId, vertexAttribute.location);
	}

	void RHI::DeleteVertexArray(const uint32 vertexArrayId)
	{
		glDeleteVertexArrays(1, &vertexArrayId);
	}

	bool RHI::CompileShader(const uint32 shaderId, const char* source)
	{
		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);
		return GetShaderCompileStatus(shaderId);
	}

	void RHI::AttachShaderToProgram(const uint32 shaderId, const uint32 programId)
	{
		glAttachShader(programId, shaderId);
	}

	bool RHI::LinkShaderProgram(const uint32 programId)
	{
		glLinkProgram(programId);
		return GetShaderProgramLinkStatus(programId);
	}

	void RHI::DeleteTexture(const uint32 textureId)
	{
		glDeleteTextures(1, &textureId);
	}

	void RHI::DeleteShader(const uint32 shaderId)
	{
		glDeleteShader(shaderId);
	}

	void RHI::DeleteShaderProgram(const uint32 programId)
	{
		glDeleteProgram(programId);
	}

	int32 RHI::GetUniformLocation(const uint32 programId, const char* name)
	{
		return glGetUniformLocation(programId, name);
	}

	EShaderStage RHI::GetShaderStage(const uint32 shaderId) const
	{
		GLint shaderType = 0;
		glGetShaderiv(shaderId, GL_SHADER_TYPE, &shaderType);
		switch (shaderType)
		{
		case GL_VERTEX_SHADER: 
			return EShaderStage::Vertex;
		case GL_FRAGMENT_SHADER: 
			return EShaderStage::Fragment;
		default:
			LOG(EChannelComponent::EngineError, "Shader stage not supported!");
			assert(false);
			return EShaderStage::Count;
		}
	}

	bool RHI::GetShaderCompileStatus(const uint32 shaderId) const
	{
		GLint compileStatus = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
		return compileStatus == GL_TRUE;
	}

	void RHI::GetShaderInfoLog(const uint32 shaderId, char* log)
	{
		GLint logLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		assert(logLength <= g_ShaderInfoLogSize);
		glGetShaderInfoLog(shaderId, logLength > g_ShaderInfoLogSize ? g_ShaderInfoLogSize : logLength, nullptr, log);
	}

	bool RHI::GetShaderProgramLinkStatus(const uint32 programId) const
	{
		GLint linkStatus = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
		return linkStatus == GL_TRUE;
	}

	void RHI::GetShaderProgramInfoLog(const uint32 programId, char* log)
	{
		GLint logLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		assert(logLength <= g_ShaderProgramInfoLogSize);
		glGetProgramInfoLog(programId, logLength > g_ShaderProgramInfoLogSize ? g_ShaderProgramInfoLogSize : logLength, nullptr, log);
	}

	int32 RHI::GetNumActiveUniforms(const uint32 programId)
	{
		GLint numActiveUniforms = 0;
		glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
		return numActiveUniforms;
	}

	void RHI::BindShaderProgram(const uint32 programId)
	{
		glUseProgram(programId);
	}

	void RHI::BindTexture(const uint32 textureId)
	{
		glBindTextureUnit(0, textureId);
	}

	void RHI::SetUniform(const uint32 programId, const int32 location, const float value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform1f(programId, location, value);
		}
	}

	void RHI::SetUniform(const uint32 programId, const int32 location, const int32 value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform1i(programId, location, value);
		}
	}

	void RHI::SetUniform(const uint32 programId, const int32 location, const vec2f& value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform2fv(programId, location, 1, &value[0]);
		}
	}

	void RHI::SetUniform(const uint32 programId, const int32 location, const vec2i& value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform2iv(programId, location, 1, &value[0]);
		}
	}

	void RHI::SetUniform(const uint32 programId, const int32 location, const vec3f& value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform3fv(programId, location, 1, &value[0]);
		}
	}
	
	void RHI::SetUniform(const uint32 programId, const int32 location, const vec3i& value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform3iv(programId, location, 1, &value[0]);
		}		
	}

	void RHI::SetUniform(const uint32 programId, const int32 location, const vec4f& value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform4fv(programId, location, 1, &value[0]);
		}		
	}
	
	void RHI::SetUniform(const uint32 programId, const int32 location, const vec4i& value)
	{
		if (CheckUniformLocation(location))
		{
			glProgramUniform4iv(programId, location, 1, &value[0]);
		}		
	}

	bool RHI::CheckUniformLocation(const int32 location)
	{
		if (location < 0)
		{
			LOG(EChannelComponent::EngineError, "Shader uniform location is invalid!");
			assert(false);
			return false;
		}
		return true;
	}

	void RHI::SetScissorRect(int32 x, int32 y, int32 width, int32 height)
	{
		glScissor(x, y, width, height);
	}

	void RHI::SetViewport(int32 x, int32 y, int32 width, int32 height)
	{
		glViewport(x, y, width, height);
	}

	void RHI::SetClearColor(const vec4f& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RHI::EnableDebugging()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GL::OnDebugMessage, 0);
	}

	bool RHI::InitLibrary()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() == GLEW_OK)
		{
			EnableDebugging();
			LOG(EChannelComponent::EngineInfo, "{}: GLEW initialized.", __func__);
			return true;
		}
		else
		{
			LOG(EChannelComponent::EngineError, "{}: GLEW initialization failed!", __func__);
			assert(false);
			return false;
		}
	}

	void RHI::ResetFrameCounters()
	{
		m_frameDrawCount = 0u;
		std::fill(std::begin(m_framePrimCount), std::end(m_framePrimCount), 0u);
	}

	void RHI::DebugDraw(const EPrimitiveMode mode, const Vertex1P1UV* vertices, const uint32 vertexCount)
	{
		static uint32 vao = 0u;

		if (vao == 0u)
		{
			glGenVertexArrays(1, &vao);
		}
		glBindVertexArray(vao);

		static uint32 vbo = 0u;
		if (vbo == 0u)
		{
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex1P1UV), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray((uint8)EVertexAttributeType::Position);
			glVertexAttribPointer((uint8)EVertexAttributeType::Position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex1P1UV), (void*)0u);
			glEnableVertexAttribArray((uint8)EVertexAttributeType::TexCoord);
			glVertexAttribPointer((uint8)EVertexAttributeType::TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex1P1UV), (void*)(sizeof(float)*2u));
		}

		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}
}