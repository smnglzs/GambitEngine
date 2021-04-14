#if 0

#pragma once

#include "Ray.h"

namespace gb
{
	class Primitive
	{
	public:
		Primitive();
		~Primitive();

		virtual bool Intersect(const Ray& aRay, float& aDistance) const = 0;
	};

#pragma region Sphere
	class Sphere : public Primitive
	{
	public:
		Sphere(glm::vec3 aCenter, float aRadius);
		~Sphere();

		glm::vec3	center;
		float		radius;

		bool Intersect(const Ray& aRay, float& t) const override;
		bool IntersectAABB(const AABB& aAABB)const;
	};
#pragma endregion

#pragma region AABB
	class AABB final : public Primitive
	{
	public:
		AABB();
		~AABB();

		glm::vec3	pointMin;
		glm::vec3	pointMax;
		glm::vec3	center;

		glm::vec3	originalPointMin;
		glm::vec3	originalPointMax;

		bool Intersect(const Ray& aRay, float& t) const;
		void Update(const glm::mat4& aGlobalMatrix);
	};
#pragma endregion

#pragma region Triangle
	class Triangle final : public Primitive
	{
	public:
		Triangle();
		Triangle(const glm::vec3& p1,
			const glm::vec3& p2,
			const glm::vec3& p3,
			bool aCalcNormal = false);
		~Triangle();

		bool			Intersect(const Ray& aRay, float& t) const;
		inline void		CalculateNormal()
		{
			normal = glm::cross(points[1] - points[0], points[2] - points[0]);
		}

		glm::vec3	points[3];
		glm::vec3	normal;
	};
#pragma endregion

#pragma region Utility
	glm::vec3	closestPoint(const glm::vec3& aPoint, const AABB& aAABB);
	float		checkAxis(const float& aPoint, const float& aMin, const float& aMax);
	float		ShortestDistance(const glm::vec3& aPoint, const AABB& aAABB);
#pragma endregion
}

#endif