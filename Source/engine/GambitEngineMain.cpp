#include <iostream>
#include "Base/GambitBaseModule.h"
#include "Base/LoggerManager/LoggerManager.h"

CREATE_LOG_CHANNEL(EngineInfo, "EngineInfo", gb::EOutputType::Both, gb::ELogLevel::Info, "Engine.txt");

int main()
{
    std::cout << "Attempting to call GambitBase API...\n";
    gb::ModuleBase gbMod;

    gbMod.StartUp();
    gbMod.RegisterSingletons();

    ADD_LOG_CHANNEL(EngineInfo, "EngineInfo");

    LOG("EngineInfo", "This is the engine main.\n");

    gbMod.ShutDown();

    system("pause");
    return 0;
}