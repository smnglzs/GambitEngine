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
		ClearMask(bool clearColor = true, bool clearDepth = false, bool clearStencil = false) :
			color(clearColor),
			depth(clearDepth),
			stencil(clearStencil) { }

		GB_FLAG(color,	 1);
		GB_FLAG(depth,	 1);
		GB_FLAG(stencil, 1);
	};

	using MatrixVariant = std::variant<mat4f, std::vector<mat4f>*>;
}