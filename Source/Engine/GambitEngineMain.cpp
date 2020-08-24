#include "Base/Common/Common.h"
#include "Base/GambitBaseModule.h"

#include "Device/DeviceModule.h"

#include "Graphics/GraphicsModule.h"

#include "Engine/GambitEngine/GambitEngine.h"

#define CONSOLE_PAUSE 1

int main()
{
    gb::GambitEngine engine;
    gb::Unique<gb::IModule> m_baseModule = std::make_unique<gb::ModuleBase>();
    gb::Unique<gb::IModule> m_deviceModule = std::make_unique<gb::DeviceModule>();
    gb::Unique<gb::IModule> m_graphicsModule = std::make_unique<gb::GraphicsModule>();

    engine.AddModule(m_baseModule, gb::EModulePriority::Base, 0);
    engine.AddModule(m_deviceModule, gb::EModulePriority::System, 1);
    engine.AddModule(m_graphicsModule, gb::EModulePriority::System, 0);

    // The whole game start NOW!
    engine.StartEngine();

#if CONSOLE_PAUSE
    system("pause");
#endif

    return 0;
}