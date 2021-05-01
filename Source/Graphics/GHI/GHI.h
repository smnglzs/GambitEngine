#pragma once
#include "GHICommon.h"

#define GB_GRAPHICS_GHI_GL 1 // Use OpenGL backend.
#if 0 // Unsupported.
#define GB_GRAPHICS_GHI_VK 0 // Use Vulkan backend.
#endif
namespace gb
{
	//=====================================================================
	//						Graphics Hardware Interface
	//=====================================================================
	class GHI final
	{
	public:
		static bool			Init();
		static void			BeginFrame();
		static void			EndFrame();
		static void			ClearRenderTarget(const ClearMask clearMask);

	#pragma region Buffers
		GHI_HANDLE_NODISC	CreateBuffer(const void* data, const uint64 size,  const EBufferUsage usage, const EBufferType type);
		template<typename V> GHI_HANDLE_NODISC CreateVertexBuffer(const void* data, const uint32 count, const EBufferUsage usage = EBufferUsage::StaticDraw);
		template<typename V> GHI_HANDLE_NODISC CreateAndBindVertexBuffer(const void* data, const uint32 count, const EBufferUsage usage);
		static void			BindBuffer(const GHIHandle bufferId, const uint32 bufferTarget);
		static void			UpdateBuffer(const GHIHandle bufferId, const void* data, const uint64 offset, const uint64 size);
		static void			DeleteBuffer(const GHIHandle bufferId);
	#pragma endregion

	#pragma region Drawing
		static void			Draw(const EPrimitiveType primitive, const int32 startVertex, const int32 numVertices);
		static void			DrawInstanced(const EPrimitiveType primitive, const int32 startVertex, const int32 numVertices, const int32 numInstances);
		static void			DrawIndexed(const EPrimitiveType primitive, const int32 numIndices, const EIndexFormat indexFormat, const void* indexOffset);
		static void			DrawIndexedInstanced(const EPrimitiveType primitive, const int32 numIndices, const EIndexFormat indexFormat, const void* indexOffset, const int32 numInstances);
	#pragma endregion

	#pragma region Queries
		GHI_HANDLE_NODISC	CreateQuery();
		static void			DeleteQuery(const GHIHandle queryId);
		static void			BeginQuery(const GHIHandle queryId, const EQueryType queryType);
		static void			EndQuery(const EQueryType queryType);
		static int64		GetTimeStamp();
	#pragma endregion

	#pragma region Renderer Capabilities
		static void			SetClearColor(const vec3f& color);
		static void			SetBlendFunc(const EBlendFunc srcBlend, const EBlendFunc dstBlend);
		static void			SetDepthFunc(const EComparisonFunc depthFunc);
		static void			SetRenderCapEnabled(const RenderCaps::ERenderCap cap, const bool enable);
		static void			SetScissorRect(int32 x, int32 y, int32 w, int32 h);
		static void			SetViewport(int32 x, int32 y, int32 w, int32 h);
		static void			SetViewport(const IntRect& view);
		static void			SetViewport(const FloatRect& view);
		static void			SetPolygonRasterMode(const EPolygonRasterMode mode, const EFace face = EFace::FrontAndBack);

		static bool			IsRenderCapEnabled(const RenderCaps::ERenderCap cap);
	#pragma endregion

	#pragma region Shaders & Programs
		GHI_HANDLE_NODISC	CreateShader(const EShaderStage stage);
		static void			DeleteShader(const GHIHandle shaderId);
		static bool			CompileShader(const GHIHandle shaderId, const char* source);
		static bool			CompileShader(const GHIHandle shaderId, const std::string& source);
		static bool			GetShaderCompileStatus(const GHIHandle shaderId);
		static void			GetShaderInfoLog(const GHIHandle shaderId, char* log);
		static EShaderStage GetShaderStage(const GHIHandle shaderId);

		GHI_HANDLE_NODISC	CreateShaderProgram();
		static void			DeleteShaderProgram(const GHIHandle programId);
		static void			AttachShaderToProgram(const GHIHandle shaderId, const GHIHandle programId);
		static void			DetachShaderFromProgram(const GHIHandle shaderId, const GHIHandle programId);
		static bool			LinkShaderProgram(const GHIHandle programId);
		static void			BindShaderProgram(const GHIHandle programId);
		static bool			GetShaderProgramLinkStatus(const GHIHandle programId);
		static void			GetShaderProgramInfoLog(const GHIHandle programId, char* log);
		static void			GetActiveUniforms(const GHIHandle programId, uint32* uniformIndices);
		static int32		GetLongestUniformNameLength(const GHIHandle programId);
		static int32		GetNumActiveUniforms(const GHIHandle programId);
		static int32		GetUniformLocation(const GHIHandle programId, const char* name);
		static void			GetUniformLocations(const GHIHandle programId, const int32 numUniforms, const char** names, uint32* locations);
		static bool			CheckUniformLocation(const int32 location);

		static void			SetUniform(const GHIHandle programId, const int32 location, const int32  i);
		static void			SetUniform(const GHIHandle programId, const int32 location, const uint32 u);
		static void			SetUniform(const GHIHandle programId, const int32 location, const float  f);
		static void			SetUniform(const GHIHandle programId, const int32 location, const double d);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec2f& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec2i& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec2u& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec3f& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec3i& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec3u& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec4f& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec4i& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const vec4u& v);
		static void			SetUniform(const GHIHandle programId, const int32 location, const mat2f& m, const bool xpose);
		static void			SetUniform(const GHIHandle programId, const int32 location, const mat3f& m, const bool xpose);
		static void			SetUniform(const GHIHandle programId, const int32 location, const mat4f& m, const bool xpose);
	#pragma endregion

	#pragma region Framebuffers & Textures
		GHI_HANDLE_NODISC	CreateFramebuffer();


		GHI_HANDLE_NODISC	CreateTexture(const ETextureType type, uint16 width, uint16 height, const PixelFormat format, const void* pixelData);
		static void			DeleteTexture(const GHIHandle textureId);
		static void			BindTexture(const GHIHandle textureId);
		static void			UpdateTexture(const GHIHandle textureId, const int32 offsetX, const int32 offsetY, const int32 width, const int32 height, const void* pixelData);
		static bool			IsTexture(const GHIHandle textureId);
	#pragma endregion

	#pragma region Vertex Arrays
		GHI_HANDLE_NODISC	CreateVertexArray();
		static void			DeleteVertexArray(const GHIHandle vertexArrayID);
		static void			AddAttributeToVertexArray(const GHIHandle vertexArrayID, const VertexAttribute& attrib);
		static void			BindVertexArray(const GHIHandle vertexArrayID);
		static bool			IsVertexArray(const GHIHandle resourceID);
	#pragma endregion 

	#pragma region Debugging
		static void			EnableDebugging();
		static void			PrintApiAndGpuInfo();
		static void			PrintApiLimits();
		static void			PrintViewportInfo();

		static const std::string& GetApiVersion();
		static const std::string& GetGpuName();
		static const std::string& GetGpuVendor();
		static const std::string& GetShadingLanguageVersion();
	#pragma endregion

	private:
		GHI() = delete;
		~GHI() = delete;

		static bool			InitGraphicsLibrary();
		static void			ResetFrameCounters();

	private:
		static std::string s_apiName;
		static std::string s_apiVersion;
		static std::string s_gpuName;
		static std::string s_gpuVendor;
		static std::string s_shadingLanguageVersion;
		static uint32	   s_frameDrawCount;
		static uint32	   s_framePrimCount[g_NumPrimitiveModes];
		static RenderCaps  s_renderCaps;
	};
}

/*  
	Anything in the .cpp that strictly uses the GHI (i.e. no direct use of the graphics API) should 
	be moved out of the API-specific impl file to a source file at the API-agnostic level.

TODO:
	- https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGet.xhtml
	- Framebuffer operations:
		- Blitting
	- ShaderParameterType ?
	- Query Objects (GHIQuery)
		- Begin in ctor, end in dtor
	- DebugOutput
	- Rasterizer State
		- Fill Mode
		- Cull Mode
		- Winding Mode
		- Alpha State
			- Enabled
			- Func
		- Scissor
			- Enabled
			- Regions
		- Depth State
			- Bias
			- Other bias?
			- Range
			- Mask
			- Clamp
		- Stencil State
			- Enabled
			- Write mask
			- Read mask
			- Reference value
			- Stencil func
			- Stencil op
				- Stencil fail
				- Depth fail
				- Stencil + depth pass
		- Multisample State
			- Enabled
			- 
	- Output Merger:
		- Blend State
			- Blend factor
			- Sample mask
			- Alpha to coverage ?
			- Independent blend ?
		- Depth State
				- Enabled
				- Write/read
				- Func

-----------------------------------------

	ColorLogicOp
	DebugOutputSync
	PrimitiveRestart
*/