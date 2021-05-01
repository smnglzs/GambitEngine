#pragma once
#include "Base/Math/Types.h"

#include "glm/gtc/matrix_transform.hpp"

namespace gb
{
	class Transform final
	{
	public:
		Transform();
		Transform(Transform& other);
		Transform(const Transform& other);
		Transform(Transform&& other);
		
		~Transform() {}

		vec4f GetPosition() const;
		vec4f GetRotation() const;
		vec4f GetScale() const;

		void SetPosition(const vec3f& position);
		void SetPosition(float x, float y, float z);
		void SetRotation(const vec3f& rotation);
		void SetRotation(float x, float y, float z);
		void SetScale(const vec3f& scale);
		void SetScale(float x, float y, float z);

		mat4f& GetMatrix() { return m_matrix; }
		const mat4f& GetMatrix() const { return m_matrix; }

	private:
		mat4f m_matrix = mat4f();
	};
}