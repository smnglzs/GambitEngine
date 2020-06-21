#include "DisplayManager.h"

namespace gb
{
	DisplayManager::DisplayManager() :
		m_primaryWindow(nullptr)
	{

	}

	DisplayManager::~DisplayManager()
	{

	}

	bool DisplayManager::CreatePrimaryWindow(const WindowSettings& winSettings)
	{
		if (m_primaryWindow)
		{
			assert(false && "The primary window has already been created!");
		}
		else
		{
			m_primaryWindow = new Window(winSettings);
		}

		return m_primaryWindow && m_primaryWindow->IsValid();
	}
}