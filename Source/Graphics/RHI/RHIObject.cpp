#include "RHIObject.h"
#include "RHI.h"

namespace gb
{
	RHIObject::RHIObject() :
		m_RHI(GetRHI()),
		m_id(0u)
	{
		// It's very important to not only assert here but to also ensure program termination.
		// The onus is on the programmer to create an RHI context before creating RHI objects.
		assert(m_RHI);
	}

	RHIObject::~RHIObject()
	{

	}

	uint32 RHIObject::GetId() const
	{
		return m_id;
	}
}