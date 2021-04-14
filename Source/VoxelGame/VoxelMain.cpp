#include "Engine/Engine/Engine.h"

#include "VoxelGame.h"
#include "VoxelWorld.h"

#include <iostream>

#define CONSOLE_PAUSE_BEFORE_CLOSE 1

void run(const char* exePath)
{
    std::string assetPath(exePath);
    size_t newSize = assetPath.rfind('\\') + 1;
    assetPath.resize(newSize);
    assetPath.append("Assets\\");

    vxl::VoxelGame vxlGame;
    vxlGame.SetAssetFolder(assetPath);

    gb::Engine engine;
    gb::Unique<gb::IModule> baseModule = std::make_unique<gb::BaseModule>();
    gb::Unique<gb::IModule> systemModule = std::make_unique<gb::SystemModule>();
    gb::Unique<gb::IModule> graphicsModule = std::make_unique<gb::GraphicsModule>();

    engine.AddModule(baseModule, gb::EModulePriority::Base, 0);
    engine.AddModule(systemModule, gb::EModulePriority::System, 1);
    engine.AddModule(graphicsModule, gb::EModulePriority::System, 0);

    engine.StartEngine();
    // The whole game starts NOW!
    engine.RunApplication(vxlGame);
}

int main(int argc, char* argv[])
{
    std::string exePath(argv[0]);
    run(argv[0]);

#if CONSOLE_PAUSE_BEFORE_CLOSE
    system("pause");
#endif

    return 0;
}