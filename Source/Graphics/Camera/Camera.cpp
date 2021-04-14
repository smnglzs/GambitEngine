#include "Camera.h"

namespace gb
{
	Camera::Camera(const FloatRect& view, const ClipPlanes clipPlanes, const Camera::EProjection projectionType) :
		m_projection(1.0f),
		m_view(view),
		m_clipPlanes(clipPlanes),
		m_projectionDirty(true),
		m_projectionType(projectionType)
	{
		BuildProjection();
	}

	Camera::~Camera()
	{

	}

	void Camera::BuildProjection(const bool forceRebuild /* = false */)
	{
		if (m_projectionDirty || forceRebuild)
		{
			switch (m_projectionType)
			{
			case EProjection::Orthographic:
				m_projection = glm::ortho(m_view.x, m_view.x + m_view.w, m_view.y, m_view.y + m_view.h, m_clipPlanes.near, m_clipPlanes.far);
				m_projectionDirty = false;
				break;
			case EProjection::Perspective:
				m_projection = glm::perspective(m_fieldOfView, m_aspectRatio, m_clipPlanes.near, m_clipPlanes.far);
				m_projectionDirty = false;
				break;
			default:
				assert(false && "Unsupported (custom?) camera projection type.");
			}
		}
	}
}