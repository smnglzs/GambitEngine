#pragma once
#include "RHIDefinitions.h"

namespace gb
{
	static const uint8  g_NumElementTypes = (uint8)EElementType::Count;
	static const uint64 g_ElementTypeSizes[g_NumElementTypes] = { sizeof(float), sizeof(int32) };

	static const uint8  g_NumPrimitiveModes = (uint8)EPrimitiveType::Count;
	static const char*  g_PrimitiveModeNames[g_NumPrimitiveModes] = { "Points", "Lines", "LineStrip", "LineLoop", "Triangles", "TriangleStrip", "Polygon" };

	namespace VertexAttributes
	{
		static const VertexAttribute Invalid  = { EVertexAttributeType::Invalid,  EElementType::Count, 0u, 0u, 0u, false };
		static const VertexAttribute Position = { EVertexAttributeType::Position, EElementType::Float, 2u, 0u, 0u, false };
		static const VertexAttribute TexCoord = { EVertexAttributeType::TexCoord, EElementType::Float, 2u, 1u, 0u, false };

		static const uint8 NumAttributeTypes = (uint8)EVertexAttributeType::Count;
		static const char* AttributeNames[NumAttributeTypes] = { "Position", "TexCoord" };

		static constexpr uint64	GetAttributeSize(const VertexAttribute& attribute)
		{
			return g_ElementTypeSizes[(uint8)attribute.elementType] * attribute.numElements;
		}

		static constexpr const VertexAttribute& GetAttributeByType(const EVertexAttributeType type)
		{
			switch (type)
			{
			case EVertexAttributeType::Position: return Position;
			case EVertexAttributeType::TexCoord: return TexCoord;
			default:
				assert(false && "Invalid vertex attribute!");
				return Invalid;
			}
		}
	}

	namespace ShaderConstants
	{
		static const uint8	NumShaderStages = (uint8)EShaderStage::Count;
		static const char*  StageNames[NumShaderStages] = { "Vertex", "Fragment" };
		static const char*  FileExtensions[NumShaderStages] = { ".vs", ".fs" };
		static const uint32	InfoLogSize = 512u;
		static const uint32	ProgramInfoLogSize = 512u;
	}
}