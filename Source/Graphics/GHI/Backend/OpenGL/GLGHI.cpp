//====================================================================
//                    OpenGL implementation of GHI
//====================================================================

// TODO: Some definitions could probably be moved to a forced include.

#include "Graphics/GHI/GHI.h"

#if GB_GRAPHICS_GHI_GL
#include "GL/glew.h"
#include "Base/LoggerManager/LoggerManager.h"

#if _DEBUG
#include <locale>
#endif

namespace gb
{
#pragma region Static Variables
	uint32	    GHI::s_frameDrawCount = 0u;
	uint32	    GHI::s_framePrimCount[g_NumPrimitiveModes] = { 0u };
	RenderCaps  GHI::s_renderCaps = { };
	std::string GHI::s_apiName = "OpenGL";
	std::string GHI::s_apiVersion = { };
	std::string GHI::s_gpuName = { };
	std::string GHI::s_gpuVendor = { };
	std::string GHI::s_shadingLanguageVersion = { };
/* Static Variables */ #pragma endregion

#pragma region Handles
	using GLhandle = GLhandleARB;

#undef GHIHandle
#define GHIHandle GLhandle
/* Handles */ #pragma endregion

#pragma region Initialization
	bool GHI::Init()
	{
		bool success = InitGraphicsLibrary();
		// success |= ...
		return success;
	}

	bool GHI::InitGraphicsLibrary()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() == GLEW_OK)
		{
		#if _DEBUG
			EnableDebugging();
			// PrintApiAndGpuInfo();
			// PrintApiLimits();
			// PrintViewportInfo();
		#endif
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
/* Initialization */ #pragma endregion

#pragma region Type Conversions
	inline static constexpr GLenum ConvertPrimitiveType(const EPrimitiveType primitive)
	{
		switch (primitive)
		{
		case EPrimitiveType::Triangles:		return GL_TRIANGLES;
		case EPrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
		default:
			LOG(gb::EChannelComponent::EngineError, "Primitive type is not yet supported or does not exist!");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertIndexFormat(const EIndexFormat indexType)
	{
		switch (indexType)
		{
		case EIndexFormat::Uint8:  return GL_UNSIGNED_BYTE;
		case EIndexFormat::Uint16: return GL_UNSIGNED_SHORT;
		case EIndexFormat::Uint32: return GL_UNSIGNED_INT;
		default:
			LOG(gb::EChannelComponent::EngineError, "Index type must be one of: uint8, uint16, or uint32");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertBufferUsage(const EBufferUsage bufferUsage)
	{
		switch (bufferUsage)
		{
		case EBufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
		case EBufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
		case EBufferUsage::DynamicRead: return GL_DYNAMIC_READ;
		case EBufferUsage::StaticCopy:  return GL_STATIC_COPY;
		case EBufferUsage::StaticDraw:  return GL_STATIC_DRAW;
		case EBufferUsage::StaticRead:  return GL_STATIC_READ;
		case EBufferUsage::StreamCopy:  return GL_STREAM_COPY;
		case EBufferUsage::StreamDraw:  return GL_STREAM_DRAW;
		case EBufferUsage::StreamRead:  return GL_STREAM_READ;
		default:
			LOG(gb::EChannelComponent::EngineError, "Buffer usage not recognized!");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertShaderStage(const EShaderStage shaderStage)
	{
		switch (shaderStage)
		{
		case EShaderStage::Vertex:	 return GL_VERTEX_SHADER;
		case EShaderStage::Fragment: return GL_FRAGMENT_SHADER;
		default:
			LOG(gb::EChannelComponent::EngineError, "Shader stage not recognized!");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertDepthFunc(const EDepthFunc depthFunc)
	{
		switch (depthFunc)
		{
		case EDepthFunc::Always:	   return GL_ALWAYS;
		case EDepthFunc::Equal:		   return GL_EQUAL;
		case EDepthFunc::Greater:	   return GL_GREATER;
		case EDepthFunc::GreaterEqual: return GL_GEQUAL;
		case EDepthFunc::Less:		   return GL_LESS;
		case EDepthFunc::LessEqual:    return GL_LEQUAL;
		case EDepthFunc::Never:		   return GL_NEVER;
		case EDepthFunc::NotEqual:	   return GL_NOTEQUAL;
		default:
			LOG(gb::EChannelComponent::EngineError, "Depth function not recognized!");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertBlendFunc(const EBlendFunc blendFunc)
	{
		switch (blendFunc)
		{
		case EBlendFunc::Zero:				 return GL_ZERO;
		case EBlendFunc::One:				 return GL_ONE;
		case EBlendFunc::SrcColor:			 return GL_SRC_COLOR;
		case EBlendFunc::OneMinusSrc:	     return GL_ONE_MINUS_SRC_COLOR;
		case EBlendFunc::DstColor:			 return GL_DST_COLOR;
		case EBlendFunc::OneMinusDstColor:	 return GL_ONE_MINUS_DST_COLOR;
		case EBlendFunc::SrcAlpha:			 return GL_SRC_ALPHA;
		case EBlendFunc::OneMinusSrcAlpha:	 return GL_ONE_MINUS_SRC_ALPHA;
		case EBlendFunc::DstAlpha:			 return GL_DST_ALPHA;
		case EBlendFunc::OneMinusDstAlpha:	 return GL_ONE_MINUS_DST_ALPHA;
		case EBlendFunc::ConstColor:	     return GL_CONSTANT_COLOR;
		case EBlendFunc::OneMinusConstColor: return GL_ONE_MINUS_CONSTANT_COLOR;
		case EBlendFunc::ConstAlpha:	     return GL_CONSTANT_ALPHA;
		case EBlendFunc::OneMinusConstAlpha: return GL_ONE_MINUS_CONSTANT_ALPHA;
		default:
			LOG(gb::EChannelComponent::EngineError, "Blend function not recognized!");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertQueryTarget(const EQueryType queryType)
	{
		switch (queryType)
		{
		case EQueryType::ClippingPrimsIn:  return GL_CLIPPING_INPUT_PRIMITIVES;
		case EQueryType::ClippingPrimsOut: return GL_CLIPPING_OUTPUT_PRIMITIVES;
		case EQueryType::InvocationsGS:    return GL_GEOMETRY_SHADER_INVOCATIONS;
		case EQueryType::InvocationsVS:    return GL_VERTEX_SHADER_INVOCATIONS;
		case EQueryType::InvocationsFS:    return GL_FRAGMENT_SHADER_INVOCATIONS;
		case EQueryType::InvocationsCS:    return GL_COMPUTE_SHADER_INVOCATIONS;
		case EQueryType::SubmittedVerts:   return GL_VERTICES_SUBMITTED;
		case EQueryType::SubmittedPrims:   return GL_PRIMITIVES_SUBMITTED;
		case EQueryType::TimeElapsed:      return GL_TIME_ELAPSED;
		default:
			LOG(gb::EChannelComponent::EngineError, "EQueryType not recognized!");
			assert(false);
			return GL_NONE;
		}
	}

	inline static constexpr GLenum ConvertRenderCap(const RenderCaps::ERenderCap cap)
	{
		switch (cap)
		{
		case RenderCaps::ERenderCap::AlphaTest:	  return GL_ALPHA_TEST;
		case RenderCaps::ERenderCap::Blend:		  return GL_BLEND;
		case RenderCaps::ERenderCap::DebugOutput: return GL_DEBUG_OUTPUT;
		case RenderCaps::ERenderCap::DepthTest:   return GL_DEPTH_TEST;
		case RenderCaps::ERenderCap::ScissorTest: return GL_SCISSOR_TEST;
		case RenderCaps::ERenderCap::StencilTest: return GL_STENCIL_TEST;
		default:
			LOG(gb::EChannelComponent::EngineError, "ERenderCap not recognized!");
			assert(false);
			return GL_NONE;
		}
	}
/* Type Conversions */ #pragma endregion

#pragma region Buffers and VertexArrays
	GLhandle GHI::CreateBuffer(const void* data, const uint64 size, const EBufferUsage usage, const EBufferType type)
	{
		GLhandle bufferId = 0u;
		if (data)
		{
			glCreateBuffers(1, &bufferId);
			if (bufferId > 0u)
			{
				glNamedBufferData(bufferId, size, data, ConvertBufferUsage(usage));
			}
			else
			{
				LOG(gb::EChannelComponent::EngineError, "glCreateBuffers failed!");
				assert(false);
			}
		}
		else
		{
			LOG(gb::EChannelComponent::EngineError, "CreateBuffer failed! Data pointer is null.");
			assert(false);
		}
		return bufferId;
	}

	template<typename V>
	GLhandle GHI::CreateVertexBuffer(const void* data, const uint32 count, const EBufferUsage usage)
	{
		const GLhandle vbo = CreateBuffer(data, count * sizeof(V), EBufferUsage::StaticDraw, EBufferType::Vertex);
		if (vbo > 0u)
			UpdateBuffer(vbo, data, 0u, count * sizeof(V));
		return vbo;
	}

	template<typename V>
	GLhandle GHI::CreateAndBindVertexBuffer(const void* data, const uint32 count, const EBufferUsage usage)
	{
		const GLhandle vbo = CreateVertexBuffer<V>(data, count, usage);
		BindBuffer(vbo, GL_ARRAY_BUFFER);
		return vbo;
	}

	GLhandle GHI::CreateVertexArray()
	{
		GLhandle vertexArrayId = 0u;
		glCreateVertexArrays(1, &vertexArrayId);
		assert(vertexArrayId);
		return vertexArrayId;
	}

	bool GHI::IsVertexArray(const GHIHandle programId)
	{
		return glIsVertexArray(programId) == GL_TRUE;
	}

	void GHI::BindVertexArray(const GHIHandle programId)
	{
		glBindVertexArray(programId);
	}

	void GHI::BindBuffer(const GHIHandle bufferId, const uint32 bufferTarget)
	{
		glBindBuffer(bufferTarget, bufferId);
	}

	void GHI::AddAttributeToVertexArray(const GHIHandle vertexArrayId, const VertexAttribute& attrib)
	{
		GLenum elementType = 0u;
		switch (attrib.elementType) // move to  ?
		{
		case EVertexElementType::Float: elementType = GL_FLOAT; break;
		case EVertexElementType::Int32: elementType = GL_INT;   break;
		default:
			LOG(EChannelComponent::EngineError, "Vertex attribute element type does not exist!");
			assert(false);
			return;
		}

		glEnableVertexArrayAttrib(vertexArrayId, attrib.location);
		glVertexAttribPointer(attrib.location, attrib.numElements, elementType, attrib.isNormalized, sizeof(Vertex2D), (void*)(attrib.location * GetAttributeSize(attrib)));
	}

	void GHI::DeleteVertexArray(const GHIHandle vertexArrayId)
	{
		glDeleteVertexArrays(1, &vertexArrayId);
	}

	void GHI::UpdateBuffer(const GHIHandle bufferId, const void* data, const uint64 offset, const uint64 size)
	{
		glNamedBufferSubData(bufferId, offset, size, data);
	}

	void GHI::DeleteBuffer(const GHIHandle bufferId)
	{
		glDeleteBuffers(1, &bufferId);
	}
/* Buffers & VertexArrays */ #pragma endregion

#pragma region Framebuffers & Textures
	GLhandle GHI::CreateFramebuffer()
	{
		GLhandle fbo = 0u;
		glCreateFramebuffers(1, &fbo);
		assert(fbo);
		return fbo;
	}

	GLhandle GHI::CreateTexture(const ETextureType type, uint16 width, uint16 height, const PixelFormat format, const void* pixelData)
	{
		GLenum textureTarget = 0u;
		switch (type)
		{
		case ETextureType::Texture2D:		textureTarget = GL_TEXTURE_2D;		 break;
		case ETextureType::Texture2DArray:	textureTarget = GL_TEXTURE_2D_ARRAY; // not yet supported, let this fall through
		default:
			LOG(EChannelComponent::EngineError, "Texture type is not yet supported or does not exist!"); // TODO: invalid argument
			assert(false);
			return GL_NONE;
		}

		GLhandle textureId = 0u;
		glCreateTextures(textureTarget, 1, &textureId);
		assert(textureId);

		// TODO: Revisit this after adding support for additional texture types and pixel formats.
		glTextureStorage2D(textureId, 1, GL_RGBA8, width, height);

		UpdateTexture(textureId, 0, 0, width, height, pixelData);

		// TODO: Make texture parameters accessible.
		glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(textureId, GL_TEXTURE_WRAP_S,	  GL_CLAMP_TO_EDGE);
		glTextureParameteri(textureId, GL_TEXTURE_WRAP_T,	  GL_CLAMP_TO_EDGE);

		return textureId;
	}

	bool GHI::IsTexture(const GHIHandle textureId)
	{
		return glIsTexture(textureId) == GL_TRUE;
	}

	void GHI::UpdateTexture(const GHIHandle textureId, const int32 offsetX, const int32 offsetY, const int32 width, const int32 height, const void* pixelData)
	{
		// TODO: Early out if last pixel.
		gbCheckRange(offsetX <= width);
		gbCheckRange(offsetY <= height);

		// TODO: Other formats and types. Assuming LOD0 for now.
		const GLint  mipLevel		 = 0u;
		const GLenum pixelDataFormat = GL_RGBA;
		const GLenum pixelDataType	 = GL_UNSIGNED_BYTE;

		glTextureSubImage2D(textureId, mipLevel, offsetX, offsetY, width, height, pixelDataFormat, pixelDataType, pixelData);
	}

	void GHI::BindTexture(const GHIHandle textureId)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTextureUnit(0, textureId);
	}

	void GHI::DeleteTexture(const GHIHandle textureId)
	{
		glDeleteTextures(1, &textureId);
	}
/* Framebuffers & Textures */ #pragma endregion

#pragma region Shaders and ShaderPrograms
	GLhandle GHI::CreateShader(const EShaderStage stage)
	{
		const GLenum glStage = ConvertShaderStage(stage);
		if (glStage != GL_NONE)
		{
			return glCreateShader(glStage);
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Shader stage not supported!");
			throw Exceptions::NotImplemented();
			return GL_NONE;
		}
	}

	_NODISCARD GLhandle GHI::CreateShaderProgram()
	{
		return glCreateProgram();
	}

	bool GHI::CompileShader(const GHIHandle shaderId, const char* source)
	{
		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);
		return GetShaderCompileStatus(shaderId);
	}

	bool GHI::CompileShader(const GHIHandle shaderId, const std::string& source)
	{
		const GLchar* source_c = source.c_str();
		return CompileShader(shaderId, source_c);
	}


	void GHI::AttachShaderToProgram(const GHIHandle shaderId, const GHIHandle programId)
	{
		glAttachShader(programId, shaderId);
	}

	bool GHI::LinkShaderProgram(const GHIHandle programId)
	{
		glLinkProgram(programId);
		return GetShaderProgramLinkStatus(programId);
	}

	void GHI::DetachShaderFromProgram(const GHIHandle shaderId, const GHIHandle programId)
	{
		glDetachShader(programId, shaderId);
	}

	void GHI::DeleteShader(const GHIHandle shaderId)
	{
		glDeleteShader(shaderId);
	}

	void GHI::DeleteShaderProgram(const GHIHandle programId)
	{
		glDeleteProgram(programId);
	}

	EShaderStage GHI::GetShaderStage(const GHIHandle shaderId)
	{
		GLint shaderType = 0;
		glGetShaderiv(shaderId, GL_SHADER_TYPE, &shaderType);
		switch (shaderType)
		{
		case GL_VERTEX_SHADER:	 return EShaderStage::Vertex;
		case GL_FRAGMENT_SHADER: return EShaderStage::Fragment;
		default:
			LOG(EChannelComponent::EngineError, "Shader stage not supported!");
			assert(false);
			return EShaderStage::Invalid;
		}
	}

	bool GHI::GetShaderCompileStatus(const GHIHandle shaderId)
	{
		GLint compileStatus = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
		return compileStatus == GL_TRUE;
	}

	void GHI::GetShaderInfoLog(const GHIHandle shaderId, char* log)
	{
		GLint logLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		assert(logLength <= ShaderGlobals::ShaderInfoLogSize);
		glGetShaderInfoLog(shaderId, logLength > ShaderGlobals::ShaderInfoLogSize ? ShaderGlobals::ShaderInfoLogSize : logLength, nullptr, log);
	}

	bool GHI::GetShaderProgramLinkStatus(const GHIHandle programId)
	{
		GLint linkStatus = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
		return linkStatus == GL_TRUE;
	}

	void GHI::GetShaderProgramInfoLog(const GHIHandle programId, char* log)
	{
		GLint logLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		assert(logLength <= ShaderGlobals::ProgramInfoLogSize);
		glGetProgramInfoLog(programId, logLength > ShaderGlobals::ProgramInfoLogSize ? ShaderGlobals::ProgramInfoLogSize : logLength, nullptr, log);
	}

	void GHI::BindShaderProgram(const GHIHandle programId)
	{
		glUseProgram(programId);
	}

	void GHI::GetActiveUniforms(const GHIHandle programId, uint32* uniformIndices)
	{
		throw gb::Exceptions::NotImplemented();
		//glGetActiveUniformsiv(programId, GetNumActiveUniforms(programId), uniformIndices, pname, params);
	}

	GLint GHI::GetLongestUniformNameLength(const GHIHandle programId)
	{
		GLint maxLength = 0;
		glGetProgramiv(programId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
		return maxLength;
	}

	GLint GHI::GetNumActiveUniforms(const GHIHandle programId)
	{
		GLint numActiveUniforms = 0;
		glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
		return numActiveUniforms;
	}

	GLint GHI::GetUniformLocation(const GHIHandle programId, const char* name)
	{
		return glGetUniformLocation(programId, name);
	}

	void GHI::GetUniformLocations(const GHIHandle programId, const int32 numUniforms, const char** names, uint32* locations)
	{
		glGetUniformIndices(programId, numUniforms, names, locations);
	}

	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const double   d)				   { glProgramUniform1d        ( pid, loc,			 d		    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const float    f)				   { glProgramUniform1f        ( pid, loc,			 f		    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const int32	  i)				   { glProgramUniform1i        ( pid, loc,			 i		    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const uint32   u)				   { glProgramUniform1ui	   ( pid, loc,			 u		    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec2f& v2f)				   { glProgramUniform2fv	   ( pid, loc, 1,		 &v2f[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec2i& v2i)				   { glProgramUniform2iv	   ( pid, loc, 1,		 &v2i[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec2u& v2u)				   { glProgramUniform2uiv	   ( pid, loc, 1,		 &v2u[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec3f& v3f)				   { glProgramUniform3fv	   ( pid, loc, 1,		 &v3f[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec3i& v3i)				   { glProgramUniform3iv	   ( pid, loc, 1,		 &v3i[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec3u& v3u)				   { glProgramUniform3uiv	   ( pid, loc, 1,		 &v3u[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec4f& v4f)				   { glProgramUniform4fv	   ( pid, loc, 1,		 &v4f[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec4i& v4i)				   { glProgramUniform4iv	   ( pid, loc, 1,		 &v4i[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const vec4u& v4u)				   { glProgramUniform4uiv	   ( pid, loc, 1,		 &v4u[0]    ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const mat2f& m2f, const bool xpose) { glProgramUniformMatrix2fv ( pid, loc, 1, xpose, &m2f[0][0] ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const mat3f& m3f, const bool xpose) { glProgramUniformMatrix3fv ( pid, loc, 1, xpose, &m3f[0][0] ); }
	void GHI::SetUniform(const GHIHandle pid, const int32 loc, const mat4f& m4f, const bool xpose) { glProgramUniformMatrix4fv ( pid, loc, 1, xpose, &m4f[0][0] ); }

	bool GHI::CheckUniformLocation(const int32 location)
	{
		if (location < 0)
		{
			LOG(EChannelComponent::EngineError, "Shader uniform location {} is invalid!", location);
			assert(false);
			return false;
		}
		return true;
	}
/* Shaders & ShaderPrograms */ #pragma endregion

#pragma region Queries
	GLhandle GHI::CreateQuery()
	{
		GLhandle queryId = 0u;
		glGenQueries(1, &queryId);
		return queryId;
	}

	void GHI::BeginQuery(const GHIHandle queryId, const EQueryType queryType)
	{
		glBeginQuery(ConvertQueryTarget(queryType), queryId);
	}

	void GHI::EndQuery(const EQueryType queryType)
	{
		glEndQuery(ConvertQueryTarget(queryType));
	}

	void GHI::DeleteQuery(const GHIHandle queryId)
	{
		glDeleteQueries(1, &queryId);
	}

	GLint64 GHI::GetTimeStamp()
	{
		GLint64 timestamp = 0;
		glGetInteger64v(GL_TIMESTAMP, &timestamp);
		return timestamp;
	}
/* Queries*/ #pragma endregion

#pragma region Misc.
	inline void EnableRenderCap(const RenderCaps::ERenderCap cap)
	{
		if (GLenum rc = ConvertRenderCap(cap))
			glEnable(rc);
	}

	inline void DisableRenderCap(const RenderCaps::ERenderCap cap)
	{
		if (GLenum rc = ConvertRenderCap(cap))
			glDisable(rc);
	}

	inline bool IsEnabled(const RenderCaps::ERenderCap cap)
	{
		const GLenum rc = ConvertRenderCap(cap);
		return rc == GL_NONE ? false : glIsEnabled(rc) == GL_TRUE;
	}

	void GHI::ResetFrameCounters()
	{
		s_frameDrawCount = 0u;
		std::fill(std::begin(s_framePrimCount), std::end(s_framePrimCount), 0u);
	}

	void GHI::BeginFrame()
	{
		ResetFrameCounters();
	}

	void GHI::EndFrame()
	{
		// count draws...
		//LOG(gb::EChannelComponent::EngineInfo, "Draws in last frame: {}\n", s_frameDrawCount);
	}

	void GHI::ClearRenderTarget(const ClearMask clearMask)
	{
		GLbitfield mask = 0u;
		if (clearMask.color)   mask |= GL_COLOR_BUFFER_BIT;
		if (clearMask.depth)   mask |= GL_DEPTH_BUFFER_BIT;
		if (clearMask.stencil) mask |= GL_STENCIL_BUFFER_BIT;
		glClear(mask);
	}

	void GHI::SetScissorRect(int32 x, int32 y, int32 width, int32 height)
	{
		// TODO: bounds check
		glScissor(x, y, width, height);
	}

	void GHI::SetViewport(int32 x, int32 y, int32 w, int32 h)
	{
		// TODO: bounds check
		glViewport(x, y, w, h);
	}

	void GHI::SetViewport(const IntRect& view)
	{
		// TODO: bounds check
		glViewport(view.x, view.y, view.w, view.h);
	}

	void GHI::SetViewport(const FloatRect& view)
	{
		// TODO: bounds check
		glViewport(int32(view.x), int32(view.y), int32(view.w), int32(view.h));
	}

	void GHI::SetWireframe(const bool enable)
	{
		// TODO: Use EFace.
		if (enable) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void GHI::SetClearColor(const vec3f& color)
	{
		glClearColor(color.r, color.g, color.b, 255.0f); // TODO: Add alpha value to color mask.
	}

	void GHI::SetBlendFunc(const EBlendFunc srcBlend, const EBlendFunc dstBlend)
	{
		glBlendFunc(ConvertBlendFunc(srcBlend), ConvertBlendFunc(dstBlend));
	}

	void GHI::SetDepthFunc(const EDepthFunc depthFunc)
	{
		glDepthFunc(ConvertDepthFunc(depthFunc));
	}
/* Misc. */ #pragma endregion // TODO: Rename

#pragma region Rendering Capabilities
	void GHI::SetRenderCapEnabled(const RenderCaps::ERenderCap cap, const bool enable)
	{
		bool dirty = false;
		switch (cap)
		{
		case RenderCaps::ERenderCap::AlphaTest: 
			if (dirty = s_renderCaps.alphaTest != enable)
				s_renderCaps.alphaTest = enable;
			break;
		case RenderCaps::ERenderCap::Blend:		  
			if (dirty = s_renderCaps.blend != enable)
				s_renderCaps.blend = enable;
			break;
		case RenderCaps::ERenderCap::DebugOutput: 
			if (dirty = s_renderCaps.debugOutput != enable)
				s_renderCaps.debugOutput = enable;
			break;
		case RenderCaps::ERenderCap::DepthTest:   
			if (dirty = s_renderCaps.depthTest != enable)
				s_renderCaps.depthTest = enable;
			break;
		case RenderCaps::ERenderCap::ScissorTest: 
			if (dirty = s_renderCaps.scissorTest != enable)
				s_renderCaps.scissorTest = enable;
			break;
		case RenderCaps::ERenderCap::StencilTest: 
			if (dirty = s_renderCaps.stencilTest != enable)
				s_renderCaps.stencilTest = enable;
			break;
		default:
			LOG(EChannelComponent::EngineWarning, "{} failed! Unrecognized ERenderCap.", __func__);
			return;
		}

		if (enable)
		{
			EnableRenderCap(cap);
			LOG(EChannelComponent::EngineInfo, "{} {}", "Enabled", g_RenderCapNames[ToUnderlyingType(cap)]);
		}
		else 
		{
			DisableRenderCap(cap);
			LOG(EChannelComponent::EngineInfo, "{} {}", "Disabled", g_RenderCapNames[ToUnderlyingType(cap)]);
		}
	}

	bool GHI::IsRenderCapEnabled(const RenderCaps::ERenderCap cap)
	{
		return glIsEnabled(ConvertRenderCap(cap) == GL_TRUE);
	}
/* Rendering Capabilities */ #pragma endregion

#pragma region Drawing
	void GHI::Draw(const EPrimitiveType primitive, const int32 startVertex, const int32 numVertices)
	{
		gbCheckRange(startVertex < numVertices);
		glDrawArrays(ConvertPrimitiveType(primitive), startVertex, numVertices);
	}

	void GHI::DrawInstanced(const EPrimitiveType primitive, const int32 startVertex, const int32 numVertices, const int32 numInstances)
	{
		gbCheckRange(startVertex < numVertices);
		glDrawArraysInstanced(ConvertPrimitiveType(primitive), startVertex, numVertices, numInstances);
	}

	void GHI::DrawIndexed(const EPrimitiveType primitive, const int32 numIndices, const EIndexFormat indexFormat, const void* indexOffset)
	{
		// TODO: check numIndices & indexOffset
		glDrawElements(ConvertPrimitiveType(primitive), numIndices, ConvertIndexFormat(indexFormat), indexOffset);
	}

	void GHI::DrawIndexedInstanced(const EPrimitiveType primitive, const int32 numIndices, const EIndexFormat indexFormat, const void* indexOffset, const int32 numInstances)
	{
		// TODO: check numIndices, indexOffset & numInstances
		glDrawElementsInstanced(ConvertPrimitiveType(primitive), numIndices, ConvertIndexFormat(indexFormat), indexOffset, numInstances);
	}
/* Drawing */ #pragma endregion

#pragma region Debugging
	static void OnDebugMessage(GLenum source, GLenum type, GLuint id, GLenum level, GLsizei length, const GLchar* message, const void* userParam)
	{
		const bool isDebugError = type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "";
		LOG(gb::EChannelComponent::EngineError, "Source: {}\nDebug: {}\nSeverity: {}Message: {}\n", source, isDebugError, level, message);
	}

	void GHI::EnableDebugging()
	{
		EnableRenderCap(RenderCaps::ERenderCap::DebugOutput);
		glDebugMessageCallback(OnDebugMessage, 0);
	}

	#define GHIGL_GETSTRING(ghiStr, glStr) if (ghiStr.empty()) ghiStr = (char*)glGetString(glStr)
	#define GHIGL_GETSTRING_IMPL(ghiStr, ghiStrVar, glStr) const std::string& GHI::Get##ghiStr##() { return ghiStrVar.empty() ? (ghiStrVar = (char*)glGetString(glStr)) : ghiStrVar; }
	GHIGL_GETSTRING_IMPL(GpuName,				 s_gpuName,				   GL_RENDERER)
	GHIGL_GETSTRING_IMPL(GpuVendor,				 s_gpuVendor,			   GL_VENDOR)
	GHIGL_GETSTRING_IMPL(ShadingLanguageVersion, s_shadingLanguageVersion, GL_SHADING_LANGUAGE_VERSION)

	const std::string& GHI::GetApiVersion()
	{
		if (s_apiVersion.empty())
		{
			s_apiVersion = (char*)glGetString(GL_VERSION);
			GHIGL_GETSTRING(s_apiVersion, GL_VERSION);
			const size_t contextStrPos = s_apiVersion.rfind("Context");
			if (contextStrPos != s_apiVersion.length())
				s_apiVersion.resize(contextStrPos);
		}
		return s_apiVersion;
	}

	void GHI::PrintApiAndGpuInfo()
	{
		static const char* topBar = "----[API/GPU Info]---------------------\n";
		static const char* botBar = "---------------------------------------\n";
		printf("%s API   : %s %s\n GLSL  : %s\n GPU   : %s\n Vendor: %s\n%s",
			topBar,
			s_apiName.c_str(), GetApiVersion().c_str(), GetShadingLanguageVersion().c_str(), GetGpuName().c_str(), GetGpuVendor().c_str(),
			botBar);
	}

	void GHI::PrintApiLimits()
	{
		static const char* topBar = "----[API Limits]-----------------------\n";
		static const char* botBar = "---------------------------------------\n";

		static GLint maxVerts, maxIndices;
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVerts);
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES,  &maxIndices);
		// TODO: add commas to numbers?
		//glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS,  &maxIndices);
		//glGetIntegerv(GL_MAX_TEXTURE_UNITS,  &maxIndices);
		//glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE,  &maxIndices);
		//glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS,  &maxIndices);
		//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,  &maxIndices);
		//glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS,  &maxIndices);
		//glGetIntegerv(GL_MAX_VERTEX_ATTRIB_STRIDE,  &maxIndices);
		//glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS,  &maxIndices);

		std::cout.imbue(std::locale(""));
		std::cout << topBar << " Max vertices: " << maxVerts << "\n Max indices : " << maxIndices << '\n' << botBar;
		//printf("%s Max vertices: %d\n Max indices : %d\n%s", topBar, maxVerts, maxIndices, botBar);
	}

	void GHI::PrintViewportInfo()
	{
		// TODO: take in viewport index
		// TODO: print all active viewports?
		static const char* topBar = "----[Viewport]-------------------------\n";
		static const char* botBar = "---------------------------------------\n";
		static GLint vpinfo[4];
		glGetIntegerv(GL_VIEWPORT, vpinfo);
		printf("%s Pos: (%d; %d)\n Dim: %d x %d\n%s", topBar, vpinfo[0], vpinfo[1], vpinfo[2], vpinfo[3], botBar);
	}
/* Debugging */ #pragma endregion
}

#endif /* GB_GRAPHICS_GHI_GL */

/* TODO:
	- Create static "GHIDefinition -> GL constants" mapping and get rid of switch blocks (e.g. EBufferUsage::StaticRead -> GL_STATIC_READ).
	- Create templated GHI<->API conversion functions.
	- Build info panels procedurally (PrintApiAndGpuInfo/PrintApiLimits/PrintViewportInfo)
		+ Lift glGetInteger calls out of PrintXXX
	- Add asserts in DrawXXX functions (startVertex < numVertices)?
*/
