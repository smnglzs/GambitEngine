#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/Buffer/VertexArray.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API VertexArrayManager final : public ISingleton
	{
	public:
		VertexArrayManager();
		~VertexArrayManager();

	protected:

	private:
	};
}

GB_CREATE_SINGLETON_ACCESSOR(VertexArrayManager, VertexArrayManager, GAMBIT_GRAPHICS_API);