#pragma once

#include "glm/fwd.hpp"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "glm/mat2x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat4x4.hpp"

#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace gb
{
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

    using mat2f  = glm::fmat2;
    using mat3f  = glm::fmat3;
    using mat4f  = glm::fmat4;

    template<typename T>
    struct Rect
    {
        T x, y;
        T w, h;
    };

    using IntRect   = typename Rect<int32>;
    using FloatRect = typename Rect<float>;
}