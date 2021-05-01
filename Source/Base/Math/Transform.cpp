#include "Transform.h"

#include "glm/gtx/matrix_decompose.hpp"

namespace gb 
{
	Transform::Transform()
	{

	}

	Transform::Transform(Transform& other)
		: m_matrix(other.m_matrix)
	{

	}

	Transform::Transform(const Transform& other)
		: m_matrix(other.m_matrix)
	{

	}

	Transform::Transform(Transform&& other)
		: m_matrix(other.m_matrix)
	{
		
	}

	vec4f Transform::GetPosition() const
	{
		glm::vec3 scale;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::quat rotation;

		glm::decompose(m_matrix, scale, rotation, translation, skew, perspective);

		return vec4f(translation, 1.f);
	}

	// Returned as radians.
	vec4f Transform::GetRotation() const
	{
		glm::vec3 scale;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::quat rotation;

		glm::decompose(m_matrix, scale, rotation, translation, skew, perspective);

		return vec4f(glm::eulerAngles(rotation), 1.f);
	}

	vec4f Transform::GetScale() const
	{
		glm::vec3 scale;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::quat rotation;

		glm::decompose(m_matrix, scale, rotation, translation, skew, perspective);

		return vec4f(scale, 1.f);
	}

	void Transform::SetPosition(const vec3f& position)
	{
		m_matrix = glm::translate(m_matrix, position);
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition(vec3f(x, y, z));
	}

	void Transform::SetRotation(const vec3f& rotation)
	{
		m_matrix = glm::rotate(m_matrix, rotation.x, vec3f(1.f, 0.f, 0.f));
		m_matrix = glm::rotate(m_matrix, rotation.y, vec3f(0.f, 1.f, 0.f));
		m_matrix = glm::rotate(m_matrix, rotation.z, vec3f(0.f, 0.f, 1.f));
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		SetRotation(vec3f(x, y, z));
	}

	void Transform::SetScale(const vec3f& scale)
	{
		m_matrix = glm::scale(m_matrix, scale);
	}

	void Transform::SetScale(float x, float y, float z)
	{
		SetScale(vec3f(x, y, z));
	}
}