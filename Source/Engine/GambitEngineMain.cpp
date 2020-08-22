#include <iostream>

#include "Base/GambitBaseModule.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Base/FileManager/FileManager.h"
#include "Base/FileManager/BaseConfig.h"

#include "Device/DeviceModule.h"
#include "Device/Window/WindowManager.h"

int main()
{
    // ========================================================= //
    //                          Base Module                      //
    // ========================================================= //
    std::cout << "Attempting to call GambitBase API...\n";
    gb::ModuleBase gbMod;

    std::cout << "Attempting to StartUp GambitBase API...\n";
    gbMod.StartUp();

    std::cout << "Attempting to RegisterSingletons of GambitBase API...\n";
    gbMod.RegisterSingletons();

    std::cout << "Adding Log Channel EngineInfo to Engine...\n";
    CREATE_LOG_CHANNEL(gb::EChannelComponent::EngineInfo, gb::EOutputType::Both, gb::ELogLevel::Info, "Engine.txt");

    std::cout << "Attempting to log in EngineInfo channel...\n";
    LOG(gb::EChannelComponent::EngineInfo, "Test EngineInfo channel.");

    LOG(gb::EChannelComponent::EngineInfo, "Attempting to Shutdown GambitBase API...");
    gbMod.ShutDown();

    // ========================================================= //
    //                          Device Module                    //
    // ========================================================= //
    std::cout << "Attempting to call GambitDevice API...\n";
    gb::DeviceModule gbDevice;

    gbDevice.StartUp();
    gbDevice.RegisterSingletons();

    auto wm = gb::GetWindowManager();
    gb::WindowSettings ws;
    ws.size = { 1900, 1080 };
    ws.title = "Gambit Engine";

    wm->CreateWindow(ws);

    gbDevice.ShutDown();

    system("pause");
    return 0;
}