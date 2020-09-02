#pragma once
#include "Base/Common/Common.h"

namespace gb
{
	/*
		TODO:
			- Pixel specification: more formats and types as needed
				- Map formats and types to number and size of channels
			- Vertex specification: formats
	*/

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
		Attribute,
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

	enum class EPrimitiveMode : uint8
	{
		Points,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		Polygon,
		Count
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
		Count
	};

	enum class EVertexAttributeType : uint8
	{
		Position,
		TexCoord,
		Count
	};

	enum class EElementType : uint8
	{
		Float,
		Int32,
		Count
	};

	struct VertexAttribute
	{
		EVertexAttributeType type;
		EElementType		 elementType;
		uint32				 numElements;
		uint32				 location;
		uint32				 offset;
		bool				 isNormalized;
	};

	struct Vertex1P1UV
	{
		gb::vec2f position;
		gb::vec2f texCoords;
	};

	static const uint8  g_NumPrimitiveModes								  = (uint8)EPrimitiveMode::Count;
	static const char*  g_PrimitiveModeNames[g_NumPrimitiveModes]		  = { "Points", "Lines", "LineStrip", "LineLoop", "Triangles", "TriangleStrip", "Polygon" };
	
	static const uint8  g_NumVertexAttributeTypes						  = (uint8)EVertexAttributeType::Count;
	static const char*  g_VertexAttributeNames[g_NumVertexAttributeTypes] = { "Position", "TexCoord" };
	static const uint8  g_NumElementTypes								  = (uint8)EPrimitiveMode::Count;
	static const uint32 g_ElementTypeSizes[g_NumElementTypes]			  = { sizeof(float), sizeof(int32) };

	static constexpr VertexAttribute g_VertexAttributes[g_NumVertexAttributeTypes] =
	{
		{ EVertexAttributeType::Position, EElementType::Float, 2u, 0u, 0u, false },
		{ EVertexAttributeType::TexCoord, EElementType::Int32, 2u, 1u, 0u, false }
	};

	static constexpr uint32	GetVertexAttributeSize(const VertexAttribute& attribute)
	{
		return g_ElementTypeSizes[(uint8)attribute.elementType] * attribute.numElements;
	}

	static const uint8	g_NumShaderStages						  = (uint8)EShaderStage::Count;
	static const char*	g_ShaderStageNames[g_NumShaderStages]	  = { "Vertex", "Fragment" };
	static const char*  g_ShaderFileExtensions[g_NumShaderStages] = { ".vs", ".fs" };
	static const uint32	g_ShaderInfoLogSize						  = 512u;
	static const uint32	g_ShaderProgramInfoLogSize				  = 512u;
}
	