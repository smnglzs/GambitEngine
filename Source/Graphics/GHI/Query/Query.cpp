#include "Query.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	Query::Query(const EQueryType type) :
		m_type(type),
		m_querying(false)
	{
	}

	Query::~Query()
	{
		Destroy();
	}

	void Query::BeginQuery()
	{
		GHI::BeginQuery(m_handle, m_type);
		m_querying = true;
	}

	void Query::EndQuery()
	{
		GHI::EndQuery(m_type);
		m_querying = false;
	}

	void Query::Destroy()
	{
		// TODO: warn/assert if m_querying?
		GHI::DeleteQuery(m_handle);
		m_handle = 0u;
	}
}