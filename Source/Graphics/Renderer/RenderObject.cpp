#include "RenderObject.h"

namespace gb
{
	uint32 RenderObject::s_numCreated	= 0u;
	uint32 RenderObject::s_numExisting	= 0u;

	RenderObject::RenderObject(const std::string& name = "") :
		m_name(),
		m_mesh({}),
		m_texture(nullptr),
		m_shaderProgram(nullptr)
	{
		++s_numCreated;
		++s_numExisting;
		m_name = name.empty() ? "RenderObject_" + std::to_string(s_numCreated) : name;
	}

	RenderObject::~RenderObject()
	{
		--s_numExisting;
	}

	const std::string& RenderObject::GetName() const
	{
		return m_name;
	}

	uint32 RenderObject::GetNumCreated()
	{
		return s_numCreated;
	}

	uint32 RenderObject::GetNumExisting()
	{
		return s_numExisting;
	}
}