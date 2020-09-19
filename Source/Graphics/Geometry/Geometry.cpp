#include "Geometry.h"

namespace gb
{
	Geometry::Geometry() :
		m_primitiveType(EPrimitiveType::Count)
	{

	}

	Geometry::~Geometry()
	{

	}

	EPrimitiveType Geometry::GetPrimitiveType() const
	{
		return m_primitiveType;
	}
}