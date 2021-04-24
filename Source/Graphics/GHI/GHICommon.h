#pragma once
#include "Graphics/Common/Common.h"
#include "Graphics/Export.h"

#define GHIHandle uint32
#define GHI_HANDLE_NODISC _NODISCARD static GHIHandle 

namespace gb
{
	enum class EPixelDataFormat : uint8
	{
		RGBA
	};

	enum class EPixelDataType : uint8
	{
		Uint8
	};

	struct PixelFormat
	{
		EPixelDataFormat format;
		EPixelDataType	 type;
	};

	enum class EBufferType : uint8
	{
		Vertex,
		Index,
		ShaderStorage,
		Uniform
	};

	enum class EBufferUsage : uint8
	{
		DynamicCopy,
		DynamicDraw,
		DynamicRead,

		StaticCopy,
		StaticDraw,
		StaticRead,

		StreamCopy,
		StreamDraw,
		StreamRead
	};

	enum class EBlendFunc : uint8
	{
		Zero,
		One,
		SrcColor,
		OneMinusSrc,
		DstColor,
		OneMinusDstColor,
		SrcAlpha,
		OneMinusSrcAlpha,
		DstAlpha,
		OneMinusDstAlpha,
		ConstColor,
		OneMinusConstColor,
		ConstAlpha,
		OneMinusConstAlpha
	};

	enum class EDepthFunc : uint8
	{
		Always,
		Equal,
		Greater,
		GreaterEqual,
		Less,
		LessEqual,
		Never,
		NotEqual
	};

#pragma region Render Capabilties
	struct RenderCaps
	{
		enum ERenderCap : uint8
		{
			AlphaTest,
			Blend,
			Culling,
			DebugOutput,
			DepthTest,
			ScissorTest,
			StencilTest,

			Count
		};
		static const uint8 g_NumRenderCaps = ToUnderlyingType(RenderCaps::ERenderCap::Count);

		RenderCaps() :
			alphaTest(false),
			blend(false),
			culling(false),
			debugOutput(false),
			depthTest(false),
			scissorTest(false),
			stencilTest(false)
		{
		}

		bool alphaTest	 : 1;
		bool blend		 : 1;
		bool culling	 : 1;
		bool debugOutput : 1;
		bool depthTest	 : 1;
		bool scissorTest : 1;
		bool stencilTest : 1;
	};
	static const char* g_RenderCapNames[] =
	{
		"AlphaTest",
		"Blend",
		"DebugOutput",
		"DepthTest"
		"ScissorTest",
		"StencilTest"
	};
#pragma endregion

	enum class EPrimitiveType : uint8
	{
		Points,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		Polygon,
		Count,
		Invalid
	};
	static const uint8 g_NumPrimitiveModes = ToUnderlyingType(EPrimitiveType::Count);
	static const char* g_PrimitiveModeNames[g_NumPrimitiveModes] =
	{
		"Points",
		"Lines",
		"LineStrip",
		"LineLoop",
		"Triangles",
		"TriangleStrip",
		"Polygon"
	};

	enum class ETextureWrappingMode : uint8
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder
	};

	enum class ETextureParameter : uint8
	{
		// https://www.khronos.org/opengl/wiki/GLAPI/glTexParameter
		BorderColor
	};

	enum class ETextureType : uint8
	{
		Texture2D,
		Texture2DArray
	};

	enum class EShaderStage : uint8
	{
		Vertex,
		Fragment,
		Count,
		Invalid
	};

	enum class EWindingOrder : uint8
	{
		Clockwise,
		Counterclockwise
	};

	enum class EFace : uint8
	{
		Front,
		Back,
		FrontAndBack
	};

	enum class EIndexFormat : uint8
	{
		Uint8,
		Uint16,
		Uint32,
		Count,
		Invalid
	};
	static const uint8  g_NumIndexTypes = ToUnderlyingType(EIndexFormat::Count);
	static const uint64 g_IndexTypeSizes[g_NumIndexTypes] = { sizeof(uint8), sizeof(uint16), sizeof(uint32) };

	static constexpr uint64 GetIndexSize(const EIndexFormat indexType)
	{
		return g_IndexTypeSizes[static_cast<uint8>(indexType)];
	}

	#pragma region Vertex Types
	struct Vertex2D
	{
		vec2f position;
		vec2f texCoord;
	};

	struct Vertex3D
	{
		vec3f position;
		vec2f texCoord;
	};
	#pragma endregion

#pragma region Vertex Attributes
	enum class EVertexAttributeType : uint8
	{
		Position2D,
		Position3D,
		TexCoord,
		Normal,
		Color,
		Count,
		Invalid
	};

	enum class EVertexDrawMode : uint8
	{
		NonIndexed,
		NonIndexedInstanced,
		Indexed,
		IndexedInstanced,
		Count,
		Invalid
	};

	enum class EVertexElementType : uint8
	{
		Float,
		Int32,
		Count,
		Invalid
	};

	struct VertexAttribute
	{
		EVertexAttributeType type;
		EVertexElementType   elementType;
		uint32				 numElements;
		uint32				 location;
		uint32				 offset;
		bool				 isNormalized;
	};

	static const VertexAttribute VAtrrib_Invalid	= { EVertexAttributeType::Invalid,    EVertexElementType::Invalid, 0u, 0u, 0u, false };
	static const VertexAttribute VAtrrib_Position2D = { EVertexAttributeType::Position2D, EVertexElementType::Float,   2u, 0u, 0u, false };
	static const VertexAttribute VAtrrib_Position3D = { EVertexAttributeType::Position3D, EVertexElementType::Float,   3u, 0u, 0u, false };
	static const VertexAttribute VAtrrib_TexCoord	= { EVertexAttributeType::TexCoord,   EVertexElementType::Float,   2u, 1u, 0u, false };
	static const VertexAttribute VAtrrib_Normal		= { EVertexAttributeType::Normal,     EVertexElementType::Float,   2u, 1u, 0u, false };
	static const VertexAttribute VAtrrib_Color		= { EVertexAttributeType::Color,	  EVertexElementType::Float,   2u, 1u, 0u, false };

	static const uint8 NumAttributeTypes = ToUnderlyingType(EVertexAttributeType::Count);
	static const char* AttributeNames[NumAttributeTypes] = { "Position2D", "Position3D", "TexCoord" };

	static const uint8 NumElementTypes = ToUnderlyingType(EVertexElementType::Count);
	static const uint64 ElementTypeSizes[NumElementTypes] = { sizeof(float), sizeof(int32) };

	static constexpr const VertexAttribute& GetAttributeByType(const EVertexAttributeType type)
	{
		switch (type)
		{
		case EVertexAttributeType::Position2D: return VAtrrib_Position2D;
		case EVertexAttributeType::Position3D: return VAtrrib_Position3D;
		case EVertexAttributeType::TexCoord:   return VAtrrib_TexCoord;
		default:
			assert(false && "Invalid vertex attribute!");
			return VAtrrib_Invalid;
		}
	}

	static constexpr uint64	GetAttributeSize(const VertexAttribute& attribute)
	{
		return ElementTypeSizes[ToUnderlyingType(attribute.elementType)] * attribute.numElements;
	}
	#pragma endregion

	enum class EQueryType : uint8
	{
		ClippingPrimsIn,
		ClippingPrimsOut,
		InvocationsGS,
		InvocationsVS,
		InvocationsFS,
		InvocationsCS,
		SubmittedVerts,
		SubmittedPrims,
		TimeElapsed,

		Count
	};
	static const uint8 g_NumQueryTypes = ToUnderlyingType(EQueryType::Count);
	static const char* g_QueryNames[g_NumQueryTypes] =
	{
		"TimeElapsed"
	};

	namespace ShaderGlobals
	{
		static const uint32	ShaderInfoLogSize			  = 2048u;
		static const uint32	ProgramInfoLogSize			  = 2048u;
		static const uint8	NumShaderStages				  = ToUnderlyingType(EShaderStage::Count);
		static const char*  StageNames  [NumShaderStages] = { "Vertex", "Fragment" };
		static const char*  FilePrefixes[NumShaderStages] = { "VS_"	  , "FS_"	   };
		static const char*  FileExtension				  = ".glsl";
		static const uint8	FilePrefixLength			  = 3;

		static constexpr EShaderStage GetStageFromFilePrefix(const std::string& prefix)
		{
			for (uint8 stageIdx = 0; stageIdx < NumShaderStages; ++stageIdx)
				if (prefix == FilePrefixes[stageIdx])
					return static_cast<EShaderStage>(stageIdx);

			assert(false);
			return EShaderStage::Invalid;
		}
	}

	class GAMBIT_GRAPHICS_API GHIResource
	{
	public:
		GHIResource() = default;
		virtual ~GHIResource() = default;

		inline GHIHandle GetHandle() const { return m_handle; }
		virtual bool IsValid() const { return m_handle > 0u; }

	protected:
		virtual void Destroy() = 0;

	protected:
		GHIHandle m_handle = 0u;
	};
}