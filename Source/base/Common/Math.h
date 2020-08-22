#pragma once

#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace gb
{
	using int8	 = int8_t;
	using int16  = int16_t;
	using int32	 = int32_t;
	using int64  = int64_t;
	using uint8  = uint8_t;
	using uint16 = uint16_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;

	using vec2d  = glm::dvec2;
	using vec2f  = glm::fvec2;
	using vec2i  = glm::ivec2;
	using vec2u  = glm::uvec2;
	using vec2us = glm::u16vec2;

	using vec3d  = glm::dvec3;
	using vec3f  = glm::fvec3;
	using vec3i  = glm::ivec3;
	using vec3u  = glm::uvec3;
	using vec3us = glm::u16vec3;

	using vec4d  = glm::dvec4;
	using vec4f  = glm::fvec4;
	using vec4i  = glm::ivec4;
	using vec4u  = glm::uvec4;
	using vec4us = glm::u16vec4;

	struct Rect 
	{ 
		uint16 x;
		uint16 y;
		uint16 w;
		uint16 h;
	};
}