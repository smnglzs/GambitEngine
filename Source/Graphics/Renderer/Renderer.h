#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Renderer final : public ISingleton
	{
	public:
		Renderer();
		~Renderer();

		void BeginFrame();
		void EndFrame();

	private:
		void DrawScene();

	private:
		class RHI* m_RHI;
	};
}

CREATE_SINGLETON_ACCESSOR(Renderer, Renderer, GAMBIT_GRAPHICS_API);