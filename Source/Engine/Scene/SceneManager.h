#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"

namespace gb
{
	class Scene;
	class SceneManager final : public ISingleton
	{
	public:
		SceneManager();
		~SceneManager();
	};
}

CREATE_SINGLETON_ACCESSOR(SceneManager, SceneManager,);