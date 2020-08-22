#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIDefinitions.h"
#include "Graphics/RHI/RHIObject.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Buffer : public RHIObject
	{
	public:
		Buffer(const uint32 size, const void* data, const EBufferType type, const EBufferUsage usage);
		virtual ~Buffer();

		void Update(const uint32 offset, const uint32 size, const void* data);

		uint32		 GetSize()  const;
		EBufferType  GetType()  const;
		EBufferUsage GetUsage() const;

	protected:
		virtual void Destroy() override;

	protected:
		uint32		 m_size;
		EBufferType  m_type;
		EBufferUsage m_usage;
	};
}