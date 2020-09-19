#include "RHIObject.h"
#include "RHI.h"

namespace gb
{
	uint32 RHIObject::s_numCreated	= 0u;
	uint32 RHIObject::s_numExisting = 0u;

	RHIObject::RHIObject() :
		m_RHI(GetRHI()),
		m_id(0u)
	{
		// It's very important to not only assert here but to also ensure program termination.
		// The onus is on the programmer to create an RHI context before creating RHI objects.
		assert(m_RHI);

		++s_numCreated;
		++s_numExisting;
	}

	RHIObject::~RHIObject()
	{
		--s_numExisting;
	}

	uint32 RHIObject::GetId() const
	{
		return m_id;
	}

	uint32 RHIObject::GetNumCreated()
	{
		return s_numCreated;
	}

	uint32 RHIObject::GetNumExisting()
	{
		return s_numExisting;
	}
}