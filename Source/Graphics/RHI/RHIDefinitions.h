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

	enum class EPrimitiveType : uint8
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
		Count,
		Invalid
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

	struct Vertex2P
	{
		gb::vec2f position;
	};

	struct Vertex2PT
	{
		gb::vec2f position;
		gb::vec2f texCoord;
	};

	
}
	