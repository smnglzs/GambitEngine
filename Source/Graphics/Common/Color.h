#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"

namespace gb
{
	// A basic color with 3 float components: {R, G, B}.
	struct GAMBIT_GRAPHICS_API Color
	{
		static const Color Black;
		static const Color Blue;
		static const Color Cyan;
		static const Color Green;
		static const Color Magenta;
		static const Color Red;
		static const Color White;
		static const Color Yellow;

		static const Color Falcon;
		static const Color SummerSky;

		Color(const int32 r, const int32 g, const int32 b) : RGB(vec3f(r, g, b) / 255.f) {}
		Color(const float r, const float g, const float b) : RGB(r, g, b) {}
		Color(const vec3f& rgb = Color::Magenta.RGB) : RGB(rgb) {}

		vec3f RGB; // normalized
	};
}