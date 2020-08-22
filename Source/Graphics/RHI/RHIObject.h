#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"

namespace gb
{
	/* TODO: 
		- IMPORTANT: implement or delete copy and move ctors and operators in each child
		- Consider adding a name & GetName pair here.
	*/
	class GAMBIT_GRAPHICS_API RHIObject
	{
	public:
		RHIObject();
		virtual ~RHIObject();

		uint32 GetId() const;

	protected:
		virtual void Destroy() = 0;

	protected:
		class RHI*	m_RHI;
		uint32		m_id;
	};
}