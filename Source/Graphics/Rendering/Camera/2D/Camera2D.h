#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Rendering/Camera/Camera.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Camera2D : public Camera
	{
	public:
		Camera2D(const FloatRect& view, const ClipPlanes clipPlanes);
		virtual ~Camera2D();
	};
}
