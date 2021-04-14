#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Common/Common.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Camera
	{
	public:
		enum class EProjection : uint8
		{
			Orthographic,
			Perspective
		};

	public:
		Camera(const FloatRect& view, const ClipPlanes clipPlanes, const Camera::EProjection projectionType);
		virtual ~Camera();

	public:
		inline const mat4f& GetProjection()
		{
			BuildProjection();
			return m_projection;
		}

	#pragma region Getters
		inline		 Color		 GetClearColor()	 const { return m_clearColor;	  }
		inline		 ClearMask	 GetClearMask()		 const { return m_clearMask;	  }
		inline const ClipPlanes& GetClipPlanes()	 const { return m_clipPlanes;	  }
		inline		 EProjection GetProjectionType() const { return m_projectionType; }
		inline const FloatRect&	 GetView()		     const { return m_view;			  }
	#pragma endregion
		
		inline void SetClearColor(const Color& clearColor) { m_clearColor = clearColor; }

		inline void	SetClipPlanes(const ClipPlanes& clipPlanes)
		{
			if (clipPlanes != m_clipPlanes)
			{
				m_clipPlanes = clipPlanes;
				m_projectionDirty = true;
			}
		}

		// Set the Camera's field of view in degrees.
		inline void SetFieldOfView(const float fieldOfView)
		{
			if (fieldOfView != m_fieldOfView)
			{
				m_fieldOfView = fieldOfView;
				m_projectionDirty = true;
			}
		}

	protected:
		void BuildProjection(const bool forceRebuild = false);

	protected:
		// TODO: Add Render Texture Reference?
		mat4f	      m_projection;
		FloatRect	  m_view;
		ClipPlanes	  m_clipPlanes;
		ClearMask	  m_clearMask;
		Color		  m_clearColor;
		glm::vec3	  m_target;
		glm::vec3	  m_upVector;
		glm::vec3	  m_position;
		union
		{
			float	  m_fieldOfView;
			float	  m_height;
			
		};
		float		  m_aspectRatio;
		bool	      m_projectionDirty;
		EProjection   m_projectionType;
	};
}