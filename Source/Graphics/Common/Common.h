#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Common/Color.h"

namespace gb
{
	struct ClipPlanes
	{
		float near;
		float far;

		inline bool operator==(const ClipPlanes& other) const { return near == other.near && far == other.far; }
	};

	struct ClearMask
	{
		uint8 color : 1;
		uint8 depth : 1;
		uint8 stencil : 1;
	};

	using MatrixVariant = std::variant<mat4f, std::vector<mat4f>*>;
}