#include "Camera2D.h"

namespace gb
{
	Camera2D::Camera2D(const FloatRect& view, const ClipPlanes clipPlanes) :
		Camera(view, clipPlanes, EProjection::Orthographic)
	{

	}

	Camera2D::~Camera2D()
	{

	}
}